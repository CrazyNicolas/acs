//蚂蚁相关函数定义
#include "ant.h"
#include<stdio.h>
//对蚂蚁进行的初始化  
Ant* init(){
	Ant *a = (Ant*)malloc(sizeof(Ant));
	a->step = 1; //随机化选择初始位置以后 就相当于已经走了一步 
	a->accu_dis = 0;  //虽然走了一步 但是当前还没累计距离 
	//用一个for循环将 访问过城市 访问顺序表置为默认值-1 
	for(int i = 0 ; i < MAXN; i++){
		a->visited[i] = -1;
	}
	for(int k = 0 ; k < MAXN +1 ;k++){
		a->order[k] = -1;
	}
	//随机选出一个起始位置
	a->curr = rand()%MAXN; 
	
	//在访问过的城市中相应的位置上置1
	a->visited[a->curr] = 1;
	//在访问顺序数组中当前位置 
	a->order[0] = a->curr;
	
	return a;
} 

int next(Ant *ant, double *p){
	if(ant->step == (MAXN - 1)){//还剩一个城市可以选 
		//找出那个城市
		for(int i = 0 ; i < MAXN ; i++){
			if(ant->visited[i] == -1){
				return i;
			}
		} 
	}else if(ant->step == MAXN){//已经不剩下可以选的城市了 这个时候直接从当前位置回到第一个城市 
		return ant->order[0]; 
	}else if(ant->step == (MAXN + 1)){
		//这表示行程真的走到尽头了
		return -1; 
	}else{//如果说以上三种情况 都不成立  那么也就意味着 现在还剩下至少两个城市可以访问  那么需要构建概率来进行一个选择
		//z在进行概率选择的时候 也分情况
//		if(q < Q0){
//			
//		}else{
//			
//		} 
		
	}
}
