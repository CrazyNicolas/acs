//utils实现
#include "utils.h" 
//根据欧几里得距离计算
double get_dis_euc(double x1, double x2, double y1 , double y2){
	return sqrt((pow(x1-x2,2)) + pow(y1-y2,2)); 
} 

//根据经纬度计算距离公式
double convert(double val){
	double deg,min;
	deg = floor(val);
	min = val - deg;
	return PI * (deg + 5.0 * min / 3.0 ) / 180.0;
} 
double get_dis_ll(double lon1, double lat1, double lon2, double lat2){
	double q1 = cos( lon1 - lon2 );
	double q2 = cos( lat1 - lat2 );
	double q3 = cos( lat1 + lat2 );
	return ( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ));
}

int read_data(char *path, double *xx, double *yy){ // x是latitude y是longitude 
	FILE *fp = fopen(path,"r");
	if(fp){
		//用来把前面的没用的信息读掉 
		char *tmp = (char*)malloc(MAXN);
		while(1){
			fgets(tmp,MAXN,fp);
			if(strcmp(tmp,"NODE_COORD_SECTION\n") == 0 ) break;
		} 
		// 开始读正常的数据
		int t;
		for(int i = 0; i < MAXN; i++){
			fscanf(fp,"%d %lf %lf",&t,&xx[i],&yy[i]);
		}
		return 1;
	}else{
		return 0;
	}
	fclose(fp);
}

//按照模式和路径读取文件 计算距离矩阵 信息素矩阵  还有信息素-距离综合衡量矩阵 
int prepare_data(char *path, char* mode, double* d, double *f, double *df){
	double *xx = (double*)malloc(sizeof(double)*MAXN); 
	double *yy = (double*)malloc(sizeof(double)*MAXN);
	if(read_data(path,xx,yy)){//如果读取坐标文件没有发生错误 
		if(strcmp(mode,"EUC") == 0){//如果是欧几里得距离计算模式 
			for(int i = 0 ; i < MAXN; i++){
				for(int j = 0 ; j < MAXN; j++){
					*(d+MAXN*i+j) =get_dis_euc(*(xx+i),*(xx+j),*(yy+i),*(yy+j)); //距离是矩阵中二者的间距 
					*(f+MAXN*i+j) = T0; //每一条路径上信息素都设置为T0
					*(df+MAXN*i+j) = T0/(pow(*(d+MAXN*i+j),BETA));  
				}
			}
			return 1;
		
		}else if(strcmp(mode,"GEO")==0){
			for(int i = 0 ; i < MAXN; i++){
				for(int j = 0 ; j < MAXN; j++){
					double x1 = convert(*(xx+i));
					double x2 = convert(*(xx+j)); // 这是latitude 
					double y1 = convert(*(yy+i));
					double y2 = convert(*(yy+j));
					*(d+MAXN*i+j) = get_dis_ll(y1,x1,y2,x2); //距离是矩阵中二者的间距 
					*(f+MAXN*i+j) = T0; //每一条路径上信息素都设置为T0
					*(df+MAXN*i+j) = T0/(pow(*(d+MAXN*i+j),BETA));  
				}
			}
			return 1;
		}else{
			printf("wrong mode\n");
			return 0; 
		}
	}else{
		printf("read file error\n");
		return 0;
	}
	

} 

void reset_dff(double *d, double *f, double *df){
	for(int i = 0 ; i <MAXN ; i++){
		for(int j=0; j < MAXN; j++){
			*(f+MAXN*i+j) = T0; //每一条路径上信息素都设置为T0
			*(df+MAXN*i+j) = T0/(pow(*(d+MAXN*i+j),BETA)); //BETA为超参数 
		}
	}
} 
