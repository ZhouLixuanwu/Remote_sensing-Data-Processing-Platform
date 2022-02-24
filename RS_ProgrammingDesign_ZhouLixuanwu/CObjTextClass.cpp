#include "pch.h"
#include "CObjTextClass.h"

//------------------------------------------------
//定义 注释类操作
//------------------------------------------------
CObjTextClass::CObjTextClass()
{
}

CObjTextClass::~CObjTextClass()
{
}

//------------------------------------------------
//链表操作
//------------------------------------------------
//向链表中增加一个新节点
TEXT *  CObjTextClass::AddOneText(float X0, float Y0, char * msg)
{
	int    len = strlen(msg);		//len记录字符串长度
	if (len < 1)					//安全检查
	{
		AfxMessageBox("未检查到有效字符串输入！");
		return NULL;
	}

	char  *pstr = new char[len + 1];	//开辟字符串空间指针变量pstr
	if (!pstr)					//安全检查
	{
		AfxMessageBox("开辟字符串空间 Error！");
		return NULL;
	}
	memset(pstr, 0, (len + 1) * sizeof(char));		//初始化内存空间
	strcpy(pstr, msg);		//将msg字符信息拷贝到pstr中

	TEXT *ctext = new TEXT[1];		//开辟一个新链表节点ctext
	if (!ctext)			//安全检查
	{
		AfxMessageBox("开辟新链表节点ctext Error！");
		delete pstr;	//删除信息，安全
		return NULL;
	}
	memset(ctext, 0, sizeof(TEXT));	//初始化新链表节点

	if (!HeadText)		//若输入的是第一个点，则置其为链表头
	{
		HeadText = ctext;
	}
	else				//若输入的不是第一个点，则添加到当前链表结尾的下一个
	{
		EndText->next = ctext;
	}

	EndText = ctext;	//用新加入的点更新最后一个点
	ctext->X0 = X0;		//为新节点X赋值
	ctext->Y0 = Y0;		//为新节点Y赋值
	ctext->CharNum = len;	//为新节点字符串长度CharNum赋值
	ctext->textAdr = pstr;	//为新节点字符串内容赋值
	TextNum++;			//更新节点数目
	return ctext;		//返回新增的节点地址
}


//-----------------
//删除链表中所有节点
//-----------------

void CObjTextClass::DeleteTextFunc()
{
	char  *pstr;	//定义空字符串指针pstr
	TEXT *ctext;	//定义一个空节点
	TEXT *dtext = NULL;	//定义临时空节点

	ForLoop(ctext, HeadText)	//宏定义：遍历链表
	{
		pstr = ctext->textAdr;	//获取当前节点存储的注释字符串

		if (pstr)		//若存在注释，则删除注释内容
		{
			delete[]pstr;
		}

		if (dtext)		//若dtext不为空，删除该节点
		{
			delete[]dtext;
		}

		dtext = ctext;	//dtext存储上一个节点地址，这样可以避免把endtext节点删掉
	}
	if (dtext) delete[]dtext;

	TextNum = 0;	//节点数重置为0
	HeadText = NULL;	//重置头结点
	EndText = NULL;	//重置尾节点
}

//------------------------------------------------
//输入输出
//------------------------------------------------
//输入
bool  CObjTextClass::LoadTextFunc(const char *filename)
{
	FILE *fio = fopen(filename, "rb");		//定义文件指针fio，调用打开文件函数fopen，根据文件名“filename”以二进制的方式读取文件“rb”
	if (!fio)
	{
		AfxMessageBox("打开文件 Error！");
		return false;		//返回false，说明读取文件 Error
	}

	short  nn;				//保存注释长度
	float  x_new, y_new;			//保存坐标信息
	x_new = 1;
	y_new = 1;
	float  x_old, y_old;		//用来比对的坐标
	x_old = 0;
	y_old = 0;
	char   RecoCode[50];	//保存注释信息，老师是在MyFunc.h文件用了extern关键字表明这个变量是在其他文件中分配的，我直接写在这里
	while (!feof(fio))		//feof是C语言标准库函数，其原型在stdio.h中，其功能是检测流上的文件结束符，文件结束：返回非0值；文件未结束：返回0值
							//这里是如果文件未结束，则执行下列语句
	{
		fread(&nn, sizeof(short), 1, fio);		//从给定的文件流fio中读取1个长度为short的对象到&nn中，根据结构定义和下面的输出方式，第一个数据存储的是注释长度
		if (nn <= 0) continue;					//如果注释长度<=0，那么说明可以跳过后面的步骤进行下一个循环（我们默认每个点都有注释）
		fread(&x_new, sizeof(float), 1, fio);		//提取x坐标到x_new
		fread(&y_new, sizeof(float), 1, fio);		//提取y坐标到y_new
		fread(RecoCode, sizeof(char), nn + 1, fio);		//提取注释文本到RecoCode

		if (x_old != x_new || y_old != y_new)
		{
			x_old = x_new;		//更新老坐标
			y_old = y_new;
			AddOneText(x_new, y_new, RecoCode);			//将这个节点加入到链表中去
		}


	}
	fclose(fio);		//关闭读文件句柄
	return true;		//返回true，说明读取文件 Done
}


//-----------------
//输出
//-----------------
void  CObjTextClass::SaveTextFunc(const char *filename)
{

	FILE  *wfo = fopen(filename, "wb");			//定义文件指针wfo
	if (!wfo)		{
		AfxMessageBox("保存文件 Error！");
		return;
	}
	short  nn;					//保存注释长度
	float  x0, y0;				//保存坐标信息
	TEXT *ctext;

	ForLoop(ctext, HeadText){	//遍历链表
		x0 = ctext->X0;			//获得当前节点x值
		y0 = ctext->Y0;			//获得当前节点y值
		nn = ctext->CharNum; if (nn <= 0) continue;		//获得长度
		fwrite(&nn, sizeof(short), 1, wfo);				//写入长度
		fwrite(&x0, sizeof(float), 1, wfo);				//横坐标
		fwrite(&y0, sizeof(float), 1, wfo);				//纵坐标
		fwrite(ctext->textAdr, sizeof(char), nn + 1, wfo);	//写入注释内容
	}
	fclose(wfo);	//关闭文件
}