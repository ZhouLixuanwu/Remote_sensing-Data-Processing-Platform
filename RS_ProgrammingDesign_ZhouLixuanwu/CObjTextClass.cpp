#include "pch.h"
#include "CObjTextClass.h"

//------------------------------------------------
//���� ע�������
//------------------------------------------------
CObjTextClass::CObjTextClass()
{
}

CObjTextClass::~CObjTextClass()
{
}

//------------------------------------------------
//�������
//------------------------------------------------
//������������һ���½ڵ�
TEXT *  CObjTextClass::AddOneText(float X0, float Y0, char * msg)
{
	int    len = strlen(msg);		//len��¼�ַ�������
	if (len < 1)					//��ȫ���
	{
		AfxMessageBox("δ��鵽��Ч�ַ������룡");
		return NULL;
	}

	char  *pstr = new char[len + 1];	//�����ַ����ռ�ָ�����pstr
	if (!pstr)					//��ȫ���
	{
		AfxMessageBox("�����ַ����ռ� Error��");
		return NULL;
	}
	memset(pstr, 0, (len + 1) * sizeof(char));		//��ʼ���ڴ�ռ�
	strcpy(pstr, msg);		//��msg�ַ���Ϣ������pstr��

	TEXT *ctext = new TEXT[1];		//����һ��������ڵ�ctext
	if (!ctext)			//��ȫ���
	{
		AfxMessageBox("����������ڵ�ctext Error��");
		delete pstr;	//ɾ����Ϣ����ȫ
		return NULL;
	}
	memset(ctext, 0, sizeof(TEXT));	//��ʼ��������ڵ�

	if (!HeadText)		//��������ǵ�һ���㣬������Ϊ����ͷ
	{
		HeadText = ctext;
	}
	else				//������Ĳ��ǵ�һ���㣬����ӵ���ǰ�����β����һ��
	{
		EndText->next = ctext;
	}

	EndText = ctext;	//���¼���ĵ�������һ����
	ctext->X0 = X0;		//Ϊ�½ڵ�X��ֵ
	ctext->Y0 = Y0;		//Ϊ�½ڵ�Y��ֵ
	ctext->CharNum = len;	//Ϊ�½ڵ��ַ�������CharNum��ֵ
	ctext->textAdr = pstr;	//Ϊ�½ڵ��ַ������ݸ�ֵ
	TextNum++;			//���½ڵ���Ŀ
	return ctext;		//���������Ľڵ��ַ
}


//-----------------
//ɾ�����������нڵ�
//-----------------

void CObjTextClass::DeleteTextFunc()
{
	char  *pstr;	//������ַ���ָ��pstr
	TEXT *ctext;	//����һ���սڵ�
	TEXT *dtext = NULL;	//������ʱ�սڵ�

	ForLoop(ctext, HeadText)	//�궨�壺��������
	{
		pstr = ctext->textAdr;	//��ȡ��ǰ�ڵ�洢��ע���ַ���

		if (pstr)		//������ע�ͣ���ɾ��ע������
		{
			delete[]pstr;
		}

		if (dtext)		//��dtext��Ϊ�գ�ɾ���ýڵ�
		{
			delete[]dtext;
		}

		dtext = ctext;	//dtext�洢��һ���ڵ��ַ���������Ա����endtext�ڵ�ɾ��
	}
	if (dtext) delete[]dtext;

	TextNum = 0;	//�ڵ�������Ϊ0
	HeadText = NULL;	//����ͷ���
	EndText = NULL;	//����β�ڵ�
}

//------------------------------------------------
//�������
//------------------------------------------------
//����
bool  CObjTextClass::LoadTextFunc(const char *filename)
{
	FILE *fio = fopen(filename, "rb");		//�����ļ�ָ��fio�����ô��ļ�����fopen�������ļ�����filename���Զ����Ƶķ�ʽ��ȡ�ļ���rb��
	if (!fio)
	{
		AfxMessageBox("���ļ� Error��");
		return false;		//����false��˵����ȡ�ļ� Error
	}

	short  nn;				//����ע�ͳ���
	float  x_new, y_new;			//����������Ϣ
	x_new = 1;
	y_new = 1;
	float  x_old, y_old;		//�����ȶԵ�����
	x_old = 0;
	y_old = 0;
	char   RecoCode[50];	//����ע����Ϣ����ʦ����MyFunc.h�ļ�����extern�ؼ��ֱ�������������������ļ��з���ģ���ֱ��д������
	while (!feof(fio))		//feof��C���Ա�׼�⺯������ԭ����stdio.h�У��书���Ǽ�����ϵ��ļ����������ļ����������ط�0ֵ���ļ�δ����������0ֵ
							//����������ļ�δ��������ִ���������
	{
		fread(&nn, sizeof(short), 1, fio);		//�Ӹ������ļ���fio�ж�ȡ1������Ϊshort�Ķ���&nn�У����ݽṹ���������������ʽ����һ�����ݴ洢����ע�ͳ���
		if (nn <= 0) continue;					//���ע�ͳ���<=0����ô˵��������������Ĳ��������һ��ѭ��������Ĭ��ÿ���㶼��ע�ͣ�
		fread(&x_new, sizeof(float), 1, fio);		//��ȡx���굽x_new
		fread(&y_new, sizeof(float), 1, fio);		//��ȡy���굽y_new
		fread(RecoCode, sizeof(char), nn + 1, fio);		//��ȡע���ı���RecoCode

		if (x_old != x_new || y_old != y_new)
		{
			x_old = x_new;		//����������
			y_old = y_new;
			AddOneText(x_new, y_new, RecoCode);			//������ڵ���뵽������ȥ
		}


	}
	fclose(fio);		//�رն��ļ����
	return true;		//����true��˵����ȡ�ļ� Done
}


//-----------------
//���
//-----------------
void  CObjTextClass::SaveTextFunc(const char *filename)
{

	FILE  *wfo = fopen(filename, "wb");			//�����ļ�ָ��wfo
	if (!wfo)		{
		AfxMessageBox("�����ļ� Error��");
		return;
	}
	short  nn;					//����ע�ͳ���
	float  x0, y0;				//����������Ϣ
	TEXT *ctext;

	ForLoop(ctext, HeadText){	//��������
		x0 = ctext->X0;			//��õ�ǰ�ڵ�xֵ
		y0 = ctext->Y0;			//��õ�ǰ�ڵ�yֵ
		nn = ctext->CharNum; if (nn <= 0) continue;		//��ó���
		fwrite(&nn, sizeof(short), 1, wfo);				//д�볤��
		fwrite(&x0, sizeof(float), 1, wfo);				//������
		fwrite(&y0, sizeof(float), 1, wfo);				//������
		fwrite(ctext->textAdr, sizeof(char), nn + 1, wfo);	//д��ע������
	}
	fclose(wfo);	//�ر��ļ�
}