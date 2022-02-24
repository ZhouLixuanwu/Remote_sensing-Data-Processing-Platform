//----------------------------------------------------------------------------------------------------------------------------------------

//�ļ�����CObjCurveClass.h		C-Object-Curve-Class

//���ܣ�����CObjCurveClass��,������߽ṹ�洢�Ĺ���

//��������ã�

//----------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------
//0���궨��
//------------------------------------------------
#define   ForLoop(p,b)            for(p=b;p!=NULL;p=p->next)		//Ϊ�˷�������������궨��
#define   MAXIPOINNUM    1000;		//�������1000��

//1���������ݽṹ��
//------------------------------------------------
//���� ���� ���� �ṹ
//------------------------------------------------

typedef struct    tagCurveStruct CURVE;

struct  tagCurveStruct
{
	short            NodeNum;                //���ߵ���
	float           *CoorAdr;                //��������
	CURVE           *next;
};                 //��һ�����߿�ʼ��ַ


#pragma once
class CObjCurveClass
{
public:
	CObjCurveClass();
	~CObjCurveClass();
public:
	//�������
	CURVE*    AddOneCurve(int  np, float *cooradr);
	void      Delete_CurveFunc();
	//�������
	bool      LoadCurveFunc(const char *filename);
	void      Save_CurveFunc(const char *filename);

public:
	//����������������ͷ��ȫ�ֱ�����
	int                CurveNum = 0;         //����ͼԪ��¼�ṹ��
	CURVE             *HeadCurve = NULL;      //����ͼԪ�ṹͷ
	CURVE             *EndCurve = NULL;      //����ͼԪ�ṹβ
};

