//������غ�������
#include "ant.h"
#include<stdio.h>
//�����Ͻ��еĳ�ʼ��  
Ant* init(){
	Ant *a = (Ant*)malloc(sizeof(Ant));
	a->step = 1; //�����ѡ���ʼλ���Ժ� ���൱���Ѿ�����һ�� 
	a->accu_dis = 0;  //��Ȼ����һ�� ���ǵ�ǰ��û�ۼƾ��� 
	//��һ��forѭ���� ���ʹ����� ����˳�����ΪĬ��ֵ-1 
	for(int i = 0 ; i < MAXN; i++){
		a->visited[i] = -1;
	}
	for(int k = 0 ; k < MAXN +1 ;k++){
		a->order[k] = -1;
	}
	//���ѡ��һ����ʼλ��
	a->curr = rand()%MAXN; 
	
	//�ڷ��ʹ��ĳ�������Ӧ��λ������1
	a->visited[a->curr] = 1;
	//�ڷ���˳�������е�ǰλ�� 
	a->order[0] = a->curr;
	
	return a;
} 

int next(Ant *ant, double *p){
	if(ant->step == (MAXN - 1)){//��ʣһ�����п���ѡ 
		//�ҳ��Ǹ�����
		for(int i = 0 ; i < MAXN ; i++){
			if(ant->visited[i] == -1){
				return i;
			}
		} 
	}else if(ant->step == MAXN){//�Ѿ���ʣ�¿���ѡ�ĳ����� ���ʱ��ֱ�Ӵӵ�ǰλ�ûص���һ������ 
		return ant->order[0]; 
	}else if(ant->step == (MAXN + 1)){
		//���ʾ�г�����ߵ���ͷ��
		return -1; 
	}else{//���˵����������� ��������  ��ôҲ����ζ�� ���ڻ�ʣ�������������п��Է���  ��ô��Ҫ��������������һ��ѡ��
		//z�ڽ��и���ѡ���ʱ�� Ҳ�����
//		if(q < Q0){
//			
//		}else{
//			
//		} 
		
	}
}
