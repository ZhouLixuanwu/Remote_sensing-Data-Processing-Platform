#include "pch.h"
#include "CObjLineClass.h"

CObjLineClass::CObjLineClass()
{
}

CObjLineClass::~CObjLineClass()
{
}

MyLine * CObjLineClass::Add_OneLine(int x_start, int y_start, int x_end, int y_end)
{

	//新建一个节点存储信息
	MyLine *Line = new MyLine[1];					//新建一个链表节点Line
	if (Line == NULL)								//内存分配 Error，返回
	{
		AfxMessageBox("添加节点时为新节点分配内存 Error！");
		return nullptr;
	}
	memset(Line, 0, sizeof(MyLine));				//初始化，清零


	//确定新加入的节点的位置
	if (Head_Line == nullptr)						//头结点为空
	{
		Head_Line = Line;							//新节点变为头结点
	}
	else											//头结点不为空
	{
		End_Line->next = Line;						//新节点加在老的尾巴后面（这里尾巴存的是上次的节点）
	}

	End_Line = Line;								//更新尾巴

	//为新节点赋值，注意赋值一定要在后面做，避免打乱尾巴的值（老尾巴存的是上次的节点）
	Line->x_start = x_start;
	Line->x_end = x_end;
	Line->y_start = y_start;
	Line->y_end = y_end;

	LineNum++;										//曲线条数增加

	return Line;									//返回节点地址

}

bool CObjLineClass::Delete_AllLine()
{
	MyLine *Line;						//建立新节点
	MyLine *temp_Line = NULL;				//建立新节点

	for (Line = Head_Line; Line != nullptr; Line = Line->next)	//遍历链表
	{
		//删除节点
		if (temp_Line)						//temp_Line存在值,第一次进来不删，因为第一次进来的是头结点Head_Line
			delete[]temp_Line;				//删除temp_Line

		temp_Line = Line;					//temp_Line 为 当前遍历到的节点
	}

	if (temp_Line) delete[]temp_Line;			//删除最后一个节点

	LineNum = 0;						//重置线数目
	Head_Line = nullptr;					//重置头结点
	End_Line = nullptr;					//重置尾节点

	return true;					// Done删除则返回true
}

bool CObjLineClass::Load_LineFile(const char *filename)
{

	FILE *fio = fopen(filename, "rb");		//以二进制方式读取文件
	if (!fio)
	{
		AfxMessageBox("打开文件：获取文件指针 Error！");
		return false;					//读取 Error则返回FALSE
	}

	int x_start, y_start, x_end, y_end;
	x_start = y_start = x_end = y_end = 0;
	int x0, y0, x1, y1;		//用于比较前后差异，防止出现重复读取的 Error
	x0 = y0 = x1 = y1 = 1;

	while (!feof(fio))		//文件未结束，则循环读入信息
	{

		//读取数据
		fread(&x_start, sizeof(int), 1, fio);					//x_start为起点x坐标
		fread(&y_start, sizeof(int), 1, fio);					//y_start为起点y坐标
		fread(&x_end, sizeof(int), 1, fio);					//x_end为终点x坐标
		fread(&y_end, sizeof(int), 1, fio);					//y_end为起点y坐标

		if (x0 != x_start || y0 != y_start || x1 != x_end || y1 != y_end)		//只要有一个不一样，就认为是不同的线，可以读进来
		{
			//添加到新的节点里
			Add_OneLine(x_start, y_start, x_end, y_end);

			//更新比较量
			x0 = x_start;
			x1 = x_end;
			y0 = y_start;
			y1 = y_end;

		}

	}
	fclose(fio);		//关闭文件

	return true;		// Done执行，返回true

}

bool CObjLineClass::Save_LineFile(const char *filename)
{
	FILE *wfo = fopen(filename, "wb");
	if (!wfo)
	{
		AfxMessageBox("保存文件：获取文件指针 Error！");
		return false;					//读取 Error则返回FALSE
	}

	int x_start, y_start, x_end, y_end;
	x_start = y_start = x_end = y_end = 0;
	MyLine *Line;		//新建一个空节点

	for (Line = Head_Line; Line != nullptr; Line = Line->next)	//遍历链表
	{
		x_start = Line->x_start;
		y_start = Line->y_start;
		x_end = Line->x_end;
		y_end = Line->y_end;

		fwrite(&x_start, sizeof(int), 1, wfo);
		fwrite(&y_start, sizeof(int), 1, wfo);
		fwrite(&x_end, sizeof(int), 1, wfo);
		fwrite(&y_end, sizeof(int), 1, wfo);
	}
	fclose(wfo);
	return false;
}
