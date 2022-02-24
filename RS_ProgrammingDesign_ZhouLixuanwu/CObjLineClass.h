//----------------------------------------------------------------------------------------------------------------------------------------

//文件名：CObjLinelass.h		C-Object-Line-Class

//功能：声明CObjLinelass类,完成线结构存储的功能

//该类的作用：

//----------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------
//0）宏定义
//------------------------------------------------
//#define   ForLoop(p,b)            for(p=b;p!=NULL;p=p->next)		//为了方便遍历链表作宏定义
#define   MaxPointNum    1000;		//最多输入1000个点

//1）曲线数据结构：
//------------------------------------------------
//定义 曲线 链表 结构
//------------------------------------------------

typedef struct    tag_Line_Struct MyLine;

struct  tag_Line_Struct
{
	int            x_start, y_start;            //起点坐标
	int            x_end, y_end;                //终点坐标
	MyLine         *next;					   //下一线开始地址
};


typedef struct    tag_Point_Struct MyPoint;

struct  tag_Point_Struct
{
	int            x, y;            //起点坐标
	MyPoint         *next;			//下一线开始地址
};


#pragma once
class CObjLineClass
{
public:
	CObjLineClass();	//构造函数
	~CObjLineClass();	//析构函数

public:
	//链表操作
	MyLine* Add_OneLine(int x_start, int y_start, int x_end, int y_end);		//添加一条线到链表中,输入参数是起点坐标和终点坐标，返回值是添加的那个节点的地址
	bool Delete_AllLine();		//删除链表中所有的节点

	//文件操作
	bool Load_LineFile(const char *filename);		//读入线文件
	bool Save_LineFile(const char *filename);		//保存线文件

public:
	//采用线性链表，链表头用全局变量：
	int                LineNum = 0;				//线图元记录结构数
	MyLine             *Head_Line = nullptr;      //线图元结构头
	MyLine             *End_Line = nullptr;      //线图元结构尾

};

