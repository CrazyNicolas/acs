//���Ͻṹ�� �Լ� ������Ϊ��λ����غ���
#ifndef _ANT_H
#define _ANT_H
#include "config.h"
typedef struct{
	int visited[MAXN]; //���ʹ��ĳ���
	int order[MAXN+1]; //���ʳ��е�˳��   
	int curr; //��ǰλ��
	double accu_dis; //ĿǰΪֹ�ۼƵ��г��� 
	int step; //��¼��ǰ�Ѿ��ǵڼ��������� ����һ��ʼ��ǰ���ǵ�һ�������� 
}Ant;

Ant* init();
int next(Ant *, double *);

#endif 
