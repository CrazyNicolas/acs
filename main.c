//main函数入口
#include "utils.h"
#include "acs.h" 


//global变量  D--路劲距离矩阵    F--路径信息素矩阵   DF---路径信息素距离综合矩阵 
double D[MAXN][MAXN];
double F[MAXN][MAXN];
double DF[MAXN][MAXN];
int main(int argc, char* argv[]){
	//初始化三个数据矩阵 
	prepare_data("kroA100.tsp","EUC",D[0],F[0],DF[0]);
	
	//初始化蚁群
	ACS *acs = init_ACS(D[0],F[0],DF[0]);
	//以下是业务逻辑  先规划以下大致有：1.根据要求代数运行蚁群迭代  2.根据要求格式打印出蚁群路径和相应参数变化趋势 
	
	//每一次迭代结束时 要把acs free一下 避免内存泄露
	del_ACS(acs); 
	//每一次迭代 最后都要记得将F和DF矩阵初始化 这很重要 
	reset_dff(D[0],F[0],DF[0]); 
	return 0;
	
} 
