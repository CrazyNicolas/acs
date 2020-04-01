//蚂蚁结构体 以及 以蚂蚁为单位的相关函数
#ifndef _ANT_H
#define _ANT_H
#include "config.h"
typedef struct{
	int visited[MAXN]; //访问过的城市
	int order[MAXN+1]; //访问城市的顺序   
	int curr; //当前位置
	double accu_dis; //目前为止累计的行程数 
	int step; //记录当前已经是第几个城市了 比如一开始当前就是第一个城市了 
}Ant;

Ant* init();
int next(Ant *, double *);

#endif 
