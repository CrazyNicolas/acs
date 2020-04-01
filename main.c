//mainº¯ÊýÈë¿Ú
#include "utils.h"
int main(int argc, char* argv[]){
	double D[MAXN][MAXN];
	double F[MAXN][MAXN];
	double DF[MAXN][MAXN];
	prepare_data("kroA100.tsp","EUC",D[0],F[0],DF[0]);
	printf("%f",D[1][1]);
	return 0;
	
} 
