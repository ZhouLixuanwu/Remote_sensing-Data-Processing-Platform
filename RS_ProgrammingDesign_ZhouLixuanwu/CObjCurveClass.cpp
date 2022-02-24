#include "pch.h"
#include "CObjCurveClass.h"

CObjCurveClass::CObjCurveClass()
{
}

CObjCurveClass::~CObjCurveClass()
{
}

CURVE * CObjCurveClass::AddOneCurve(int np, float * cooradr)	//np为曲线点数，cooradr为曲线坐标地址
{

	if (np < 2) return NULL;						//np为曲线点数，若曲线点数小于2，说明不构成线，退出

	float *pcoor = new float[np * 2];				//pcoor为曲线坐标
	if (!pcoor) return NULL;						//内存分配 Error，返回
	memset(pcoor, 0, (np * 2) * sizeof(float));		//初始化，清零

	CURVE *curve = new CURVE[1];					//新建一个链表节点
	if (!curve) { delete pcoor; return NULL; }		//内存分配 Error，返回
	memset(curve, 0, sizeof(CURVE));				//初始化，清零

	if (!HeadCurve)									//头结点为空
		HeadCurve = curve;							//新的空节点变为头结点
	else											//头结点不为空
		EndCurve->next = curve;						//新的空节点变为尾节点的下一个节点

	EndCurve = curve;								//新的空节点变为尾节点
	curve->NodeNum = np;							//记录曲线点数
	curve->CoorAdr = pcoor;							//记录曲线坐标
	memcpy(pcoor, cooradr, np * 2 * sizeof(float));	//为曲线坐标赋值
	CurveNum++;										//曲线条数增加

	return curve;									//返回节点地址

}

void CObjCurveClass::Delete_CurveFunc()
{
	CURVE *curve;						//建立新节点
	CURVE *dcurv = NULL;				//建立新节点
	ForLoop(curve, HeadCurve)			//遍历链表
	{
		//删除值
		if (curve->CoorAdr)				//曲线存在坐标
			delete curve->CoorAdr;		//删除坐标
		curve->CoorAdr = NULL;			//值为空

		//删除节点
		if (dcurv)						//dcurv存在值
			delete[]dcurv;				//删除dcurv
		dcurv = curve;					//dcurv 为 当前遍历到的节点
	}

	if (dcurv) delete[]dcurv;			//删除最后一个节点

	CurveNum = 0;						//重置线数目
	HeadCurve = NULL;					//重置头结点
	EndCurve = NULL;					//重置尾节点
	return;
}


bool CObjCurveClass::LoadCurveFunc(const char * filename)
{
	FILE *fio = fopen(filename, "rb");		//以二进制方式读取文件
	if (!fio) return false;					//读取 Error则返回FALSE

	short  nn;
	float  x0, y0;
	//	float  TablCoorAdr[2 * MAXIPOINNUM];
	while (!feof(fio))		//文件未结束，则循环读入信息
	{
		fread(&nn, sizeof(short), 1, fio);					//nn为曲线点的数目 
		if (nn <= 0) continue;
		//		fread(TablCoorAdr, sizeof(float), nn * 2, fio);		//TablCoorAdr为曲线坐标
		//		AddOneCurve(nn, TablCoorAdr);
	}
	fclose(fio);
	return true;
}

void CObjCurveClass::Save_CurveFunc(const char * filename)
{
	FILE *wfo = fopen(filename, "wb");
	if (!wfo) return;

	short  nn;
	float  x0, y0;
	CURVE *curve;
	ForLoop(curve, HeadCurve)
	{
		nn = curve->NodeNum;
		if (nn <= 0) continue;
		fwrite(&nn, sizeof(short), 1, wfo);
		fwrite(curve->CoorAdr, sizeof(float), nn * 2, wfo);
	}
	fclose(wfo);
	return;
}
