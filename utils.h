//���ߺ���  �ļ���ȡ д�� ����
#ifndef _UTTL_H
#define _UTIL_H
#include "config.h"
//���ļ��еľ�γ�����ݶ�������׼���õ�array���� 
int read_data(char *path, double *longitude, double *latitude);
int prepare_data(char *path, char* mode, double* d, double *f, double *df);
double get_dis_euc(double, double, double, double);
double convert(double val);
double get_dis_ll(double lon1, double lat1, double lon2, double lat2);
void reset_dff(double *d, double *f, double *df);

#endif 
