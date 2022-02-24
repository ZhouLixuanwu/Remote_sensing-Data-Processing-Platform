#include "pch.h"
#include "CObjCurveClass.h"

CObjCurveClass::CObjCurveClass()
{
}

CObjCurveClass::~CObjCurveClass()
{
}

CURVE * CObjCurveClass::AddOneCurve(int np, float * cooradr)	//npΪ���ߵ�����cooradrΪ���������ַ
{

	if (np < 2) return NULL;						//npΪ���ߵ����������ߵ���С��2��˵���������ߣ��˳�

	float *pcoor = new float[np * 2];				//pcoorΪ��������
	if (!pcoor) return NULL;						//�ڴ���� Error������
	memset(pcoor, 0, (np * 2) * sizeof(float));		//��ʼ��������

	CURVE *curve = new CURVE[1];					//�½�һ������ڵ�
	if (!curve) { delete pcoor; return NULL; }		//�ڴ���� Error������
	memset(curve, 0, sizeof(CURVE));				//��ʼ��������

	if (!HeadCurve)									//ͷ���Ϊ��
		HeadCurve = curve;							//�µĿսڵ��Ϊͷ���
	else											//ͷ��㲻Ϊ��
		EndCurve->next = curve;						//�µĿսڵ��Ϊβ�ڵ����һ���ڵ�

	EndCurve = curve;								//�µĿսڵ��Ϊβ�ڵ�
	curve->NodeNum = np;							//��¼���ߵ���
	curve->CoorAdr = pcoor;							//��¼��������
	memcpy(pcoor, cooradr, np * 2 * sizeof(float));	//Ϊ�������긳ֵ
	CurveNum++;										//������������

	return curve;									//���ؽڵ��ַ

}

void CObjCurveClass::Delete_CurveFunc()
{
	CURVE *curve;						//�����½ڵ�
	CURVE *dcurv = NULL;				//�����½ڵ�
	ForLoop(curve, HeadCurve)			//��������
	{
		//ɾ��ֵ
		if (curve->CoorAdr)				//���ߴ�������
			delete curve->CoorAdr;		//ɾ������
		curve->CoorAdr = NULL;			//ֵΪ��

		//ɾ���ڵ�
		if (dcurv)						//dcurv����ֵ
			delete[]dcurv;				//ɾ��dcurv
		dcurv = curve;					//dcurv Ϊ ��ǰ�������Ľڵ�
	}

	if (dcurv) delete[]dcurv;			//ɾ�����һ���ڵ�

	CurveNum = 0;						//��������Ŀ
	HeadCurve = NULL;					//����ͷ���
	EndCurve = NULL;					//����β�ڵ�
	return;
}


bool CObjCurveClass::LoadCurveFunc(const char * filename)
{
	FILE *fio = fopen(filename, "rb");		//�Զ����Ʒ�ʽ��ȡ�ļ�
	if (!fio) return false;					//��ȡ Error�򷵻�FALSE

	short  nn;
	float  x0, y0;
	//	float  TablCoorAdr[2 * MAXIPOINNUM];
	while (!feof(fio))		//�ļ�δ��������ѭ��������Ϣ
	{
		fread(&nn, sizeof(short), 1, fio);					//nnΪ���ߵ����Ŀ 
		if (nn <= 0) continue;
		//		fread(TablCoorAdr, sizeof(float), nn * 2, fio);		//TablCoorAdrΪ��������
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
