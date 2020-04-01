//蚁群结构体 以及相应函数头文件 
#ifndef _ACS_H
#define _ACS_H
#include "config.h"
#include "ant.h"

typedef struct {
	Ant* ants[MAXN];
	double *D; //蚁群所面对的地图 独立矩阵
	double *F; //蚁群控制的信息素矩阵
	double *DF; //蚁群的综合信息素-距离水平矩阵
	Ant bestone; //最优的一只蚂蚁 
}ACS;

//根据MAXN指定的蚁群大小来对蚁群初始化 是通过调用每一只蚂蚁的初始化函数做到的 
ACS* init_ACS(double *d, double *f, double *df);
//删除动态分配的蚁群指针 
void del_ACS(ACS *);

//acs开始运行运行 
void run(ACS* acs); 
	

#endif
