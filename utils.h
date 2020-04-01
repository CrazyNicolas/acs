//工具函数  文件读取 写入 函数
#ifndef _UTTL_H
#define _UTIL_H
#include "config.h"
//将文件中的经纬度数据读到我们准备好的array里面 
int read_data(char *path, double *longitude, double *latitude);
int prepare_data(char *path, char* mode, double* d, double *f, double *df);
double get_dis_euc(double, double, double, double);
double convert(double val);
double get_dis_ll(double lon1, double lat1, double lon2, double lat2);
void reset_dff(double *d, double *f, double *df);

#endif 
