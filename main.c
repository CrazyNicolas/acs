//main�������
#include "utils.h"
#include "acs.h" 


//global����  D--·���������    F--·����Ϣ�ؾ���   DF---·����Ϣ�ؾ����ۺϾ��� 
double D[MAXN][MAXN];
double F[MAXN][MAXN];
double DF[MAXN][MAXN];
int main(int argc, char* argv[]){
	//��ʼ���������ݾ��� 
	prepare_data("kroA100.tsp","EUC",D[0],F[0],DF[0]);
	
	//��ʼ����Ⱥ
	ACS *acs = init_ACS(D[0],F[0],DF[0]);
	//������ҵ���߼�  �ȹ滮���´����У�1.����Ҫ�����������Ⱥ����  2.����Ҫ���ʽ��ӡ����Ⱥ·������Ӧ�����仯���� 
	
	//ÿһ�ε�������ʱ Ҫ��acs freeһ�� �����ڴ�й¶
	del_ACS(acs); 
	//ÿһ�ε��� ���Ҫ�ǵý�F��DF�����ʼ�� �����Ҫ 
	reset_dff(D[0],F[0],DF[0]); 
	return 0;
	
} 
