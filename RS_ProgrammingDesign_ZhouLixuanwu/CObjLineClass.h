//----------------------------------------------------------------------------------------------------------------------------------------

//�ļ�����CObjLinelass.h		C-Object-Line-Class

//���ܣ�����CObjLinelass��,����߽ṹ�洢�Ĺ���

//��������ã�

//----------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------
//0���궨��
//------------------------------------------------
//#define   ForLoop(p,b)            for(p=b;p!=NULL;p=p->next)		//Ϊ�˷�������������궨��
#define   MaxPointNum    1000;		//�������1000����

//1���������ݽṹ��
//------------------------------------------------
//���� ���� ���� �ṹ
//------------------------------------------------

typedef struct    tag_Line_Struct MyLine;

struct  tag_Line_Struct
{
	int            x_start, y_start;            //�������
	int            x_end, y_end;                //�յ�����
	MyLine         *next;					   //��һ�߿�ʼ��ַ
};


typedef struct    tag_Point_Struct MyPoint;

struct  tag_Point_Struct
{
	int            x, y;            //�������
	MyPoint         *next;			//��һ�߿�ʼ��ַ
};


#pragma once
class CObjLineClass
{
public:
	CObjLineClass();	//���캯��
	~CObjLineClass();	//��������

public:
	//�������
	MyLine* Add_OneLine(int x_start, int y_start, int x_end, int y_end);		//���һ���ߵ�������,������������������յ����꣬����ֵ����ӵ��Ǹ��ڵ�ĵ�ַ
	bool Delete_AllLine();		//ɾ�����������еĽڵ�

	//�ļ�����
	bool Load_LineFile(const char *filename);		//�������ļ�
	bool Save_LineFile(const char *filename);		//�������ļ�

public:
	//����������������ͷ��ȫ�ֱ�����
	int                LineNum = 0;				//��ͼԪ��¼�ṹ��
	MyLine             *Head_Line = nullptr;      //��ͼԪ�ṹͷ
	MyLine             *End_Line = nullptr;      //��ͼԪ�ṹβ

};

