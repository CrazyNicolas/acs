//��Ⱥ�ṹ�� �Լ���Ӧ����ͷ�ļ� 
#ifndef _ACS_H
#define _ACS_H
#include "config.h"
#include "ant.h"

typedef struct {
	Ant* ants[MAXN];
	double *D; //��Ⱥ����Եĵ�ͼ ��������
	double *F; //��Ⱥ���Ƶ���Ϣ�ؾ���
	double *DF; //��Ⱥ���ۺ���Ϣ��-����ˮƽ����
	Ant bestone; //���ŵ�һֻ���� 
}ACS;

//����MAXNָ������Ⱥ��С������Ⱥ��ʼ�� ��ͨ������ÿһֻ���ϵĳ�ʼ������������ 
inline void init_ACS(); 

//acs��ʼ�������� 
void run(ACS* acs); 
	

#endif
