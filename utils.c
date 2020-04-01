//utilsʵ��
#include "utils.h" 
//����ŷ����þ������
double get_dis_euc(double x1, double x2, double y1 , double y2){
	return sqrt((pow(x1-x2,2)) + pow(y1-y2,2)); 
} 

//���ݾ�γ�ȼ�����빫ʽ
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

int read_data(char *path, double *xx, double *yy){ // x��latitude y��longitude 
	FILE *fp = fopen(path,"r");
	if(fp){
		//������ǰ���û�õ���Ϣ���� 
		char *tmp = (char*)malloc(MAXN);
		while(1){
			fgets(tmp,MAXN,fp);
			if(strcmp(tmp,"NODE_COORD_SECTION\n") == 0 ) break;
		} 
		// ��ʼ������������
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

//����ģʽ��·����ȡ�ļ� ���������� ��Ϣ�ؾ���  ������Ϣ��-�����ۺϺ������� 
int prepare_data(char *path, char* mode, double* d, double *f, double *df){
	double *xx = (double*)malloc(sizeof(double)*MAXN); 
	double *yy = (double*)malloc(sizeof(double)*MAXN);
	if(read_data(path,xx,yy)){//�����ȡ�����ļ�û�з������� 
		if(strcmp(mode,"EUC") == 0){//�����ŷ����þ������ģʽ 
			for(int i = 0 ; i < MAXN; i++){
				for(int j = 0 ; j < MAXN; j++){
					*(d+MAXN*i+j) =get_dis_euc(*(xx+i),*(xx+j),*(yy+i),*(yy+j)); //�����Ǿ����ж��ߵļ�� 
					*(f+MAXN*i+j) = T0; //ÿһ��·������Ϣ�ض�����ΪT0
					*(df+MAXN*i+j) = T0/(pow(*(d+MAXN*i+j),BETA));  
				}
			}
			return 1;
		
		}else if(strcmp(mode,"GEO")==0){
			for(int i = 0 ; i < MAXN; i++){
				for(int j = 0 ; j < MAXN; j++){
					double x1 = convert(*(xx+i));
					double x2 = convert(*(xx+j)); // ����latitude 
					double y1 = convert(*(yy+i));
					double y2 = convert(*(yy+j));
					*(d+MAXN*i+j) = get_dis_ll(y1,x1,y2,x2); //�����Ǿ����ж��ߵļ�� 
					*(f+MAXN*i+j) = T0; //ÿһ��·������Ϣ�ض�����ΪT0
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
			*(f+MAXN*i+j) = T0; //ÿһ��·������Ϣ�ض�����ΪT0
			*(df+MAXN*i+j) = T0/(pow(*(d+MAXN*i+j),BETA)); //BETAΪ������ 
		}
	}
} 
