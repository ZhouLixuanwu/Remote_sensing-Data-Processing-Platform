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

	//�½�һ���ڵ�洢��Ϣ
	MyLine *Line = new MyLine[1];					//�½�һ������ڵ�Line
	if (Line == NULL)								//�ڴ���� Error������
	{
		AfxMessageBox("��ӽڵ�ʱΪ�½ڵ�����ڴ� Error��");
		return nullptr;
	}
	memset(Line, 0, sizeof(MyLine));				//��ʼ��������


	//ȷ���¼���Ľڵ��λ��
	if (Head_Line == nullptr)						//ͷ���Ϊ��
	{
		Head_Line = Line;							//�½ڵ��Ϊͷ���
	}
	else											//ͷ��㲻Ϊ��
	{
		End_Line->next = Line;						//�½ڵ�����ϵ�β�ͺ��棨����β�ʹ�����ϴεĽڵ㣩
	}

	End_Line = Line;								//����β��

	//Ϊ�½ڵ㸳ֵ��ע�⸳ֵһ��Ҫ�ں��������������β�͵�ֵ����β�ʹ�����ϴεĽڵ㣩
	Line->x_start = x_start;
	Line->x_end = x_end;
	Line->y_start = y_start;
	Line->y_end = y_end;

	LineNum++;										//������������

	return Line;									//���ؽڵ��ַ

}

bool CObjLineClass::Delete_AllLine()
{
	MyLine *Line;						//�����½ڵ�
	MyLine *temp_Line = NULL;				//�����½ڵ�

	for (Line = Head_Line; Line != nullptr; Line = Line->next)	//��������
	{
		//ɾ���ڵ�
		if (temp_Line)						//temp_Line����ֵ,��һ�ν�����ɾ����Ϊ��һ�ν�������ͷ���Head_Line
			delete[]temp_Line;				//ɾ��temp_Line

		temp_Line = Line;					//temp_Line Ϊ ��ǰ�������Ľڵ�
	}

	if (temp_Line) delete[]temp_Line;			//ɾ�����һ���ڵ�

	LineNum = 0;						//��������Ŀ
	Head_Line = nullptr;					//����ͷ���
	End_Line = nullptr;					//����β�ڵ�

	return true;					// Doneɾ���򷵻�true
}

bool CObjLineClass::Load_LineFile(const char *filename)
{

	FILE *fio = fopen(filename, "rb");		//�Զ����Ʒ�ʽ��ȡ�ļ�
	if (!fio)
	{
		AfxMessageBox("���ļ�����ȡ�ļ�ָ�� Error��");
		return false;					//��ȡ Error�򷵻�FALSE
	}

	int x_start, y_start, x_end, y_end;
	x_start = y_start = x_end = y_end = 0;
	int x0, y0, x1, y1;		//���ڱȽ�ǰ����죬��ֹ�����ظ���ȡ�� Error
	x0 = y0 = x1 = y1 = 1;

	while (!feof(fio))		//�ļ�δ��������ѭ��������Ϣ
	{

		//��ȡ����
		fread(&x_start, sizeof(int), 1, fio);					//x_startΪ���x����
		fread(&y_start, sizeof(int), 1, fio);					//y_startΪ���y����
		fread(&x_end, sizeof(int), 1, fio);					//x_endΪ�յ�x����
		fread(&y_end, sizeof(int), 1, fio);					//y_endΪ���y����

		if (x0 != x_start || y0 != y_start || x1 != x_end || y1 != y_end)		//ֻҪ��һ����һ��������Ϊ�ǲ�ͬ���ߣ����Զ�����
		{
			//��ӵ��µĽڵ���
			Add_OneLine(x_start, y_start, x_end, y_end);

			//���±Ƚ���
			x0 = x_start;
			x1 = x_end;
			y0 = y_start;
			y1 = y_end;

		}

	}
	fclose(fio);		//�ر��ļ�

	return true;		// Doneִ�У�����true

}

bool CObjLineClass::Save_LineFile(const char *filename)
{
	FILE *wfo = fopen(filename, "wb");
	if (!wfo)
	{
		AfxMessageBox("�����ļ�����ȡ�ļ�ָ�� Error��");
		return false;					//��ȡ Error�򷵻�FALSE
	}

	int x_start, y_start, x_end, y_end;
	x_start = y_start = x_end = y_end = 0;
	MyLine *Line;		//�½�һ���սڵ�

	for (Line = Head_Line; Line != nullptr; Line = Line->next)	//��������
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
