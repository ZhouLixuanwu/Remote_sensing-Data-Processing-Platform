//----------------------------------------------------------------------------------------------------------------------------------------

//文件名：CObjCurveClass.h		C-Object-Curve-Class

//功能：声明CObjCurveClass类,完成曲线结构存储的功能

//该类的作用：

//----------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------
//0）宏定义
//------------------------------------------------
#define   ForLoop(p,b)            for(p=b;p!=NULL;p=p->next)		//为了方便遍历链表作宏定义
#define   MAXIPOINNUM    1000;		//最多输入1000个

//1）曲线数据结构：
//------------------------------------------------
//定义 曲线 链表 结构
//------------------------------------------------

typedef struct    tagCurveStruct CURVE;

struct  tagCurveStruct
{
	short            NodeNum;                //曲线点数
	float           *CoorAdr;                //曲线坐标
	CURVE           *next;
};                 //下一个曲线开始地址


#pragma once
class CObjCurveClass
{
public:
	CObjCurveClass();
	~CObjCurveClass();
public:
	//链表操作
	CURVE*    AddOneCurve(int  np, float *cooradr);
	void      Delete_CurveFunc();
	//输入输出
	bool      LoadCurveFunc(const char *filename);
	void      Save_CurveFunc(const char *filename);

public:
	//采用线性链表，链表头用全局变量：
	int                CurveNum = 0;         //曲线图元记录结构数
	CURVE             *HeadCurve = NULL;      //曲线图元结构头
	CURVE             *EndCurve = NULL;      //曲线图元结构尾
};

