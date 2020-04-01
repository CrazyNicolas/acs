//constants configuration
#ifndef CONFIG_H_
#define CONFIG_H_
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include<math.h>
#define MAXN 100  //城市数量  表明从测试数据文件中读入多少行 
#define PI 3.141592 // Pi的定义 
#define RRR 6378.388 // 地球半径 
#define Q0 0.7//概率阈值
#define T0  5e-7// （MAXN * 最优总花费）^-1 
#define NUM_ANTS 20//蚁群规模 
#define BETA 2.0 // 距离和信息素综合乘积中距离倒数的次幂 
#define ALPHA 0.3 
#define RHO 0.3 // 挥发率 
#define PATH "" //选择当前文件下的数据文件作为读入文件
#endif

