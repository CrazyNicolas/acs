//��Ⱥ�㷨����
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include<math.h>

#define MAXN 100  //��������  �����Ӳ��������ļ��ж�������� 
#define PI 3.141592 // Pi�Ķ��� 
#define RRR 6378.388 // ����뾶 
#define Q0 0.8//������ֵ
#define T0  5e-7// ��MAXN * �����ܻ��ѣ�^-1 
#define NUM_ANTS 20//��Ⱥ��ģ 
#define BETA 2.0 // �������Ϣ���ۺϳ˻��о��뵹���Ĵ��� 
#define ALPHA 0.2
#define RHO 0.2 // �ӷ��� 

typedef struct{
	int visited[MAXN]; //���ʹ��ĳ���
	int order[MAXN]; //���ʳ��е�˳��   
	int curr; //��ǰλ��
	double accu_dis; //ĿǰΪֹ�ۼƵ��г��� 
	int step; //��¼��ǰ�Ѿ��ǵڼ��������� ����һ��ʼ��ǰ���ǵ�һ�������� 
}Ant;

//�����Ͻ��еĳ�ʼ��  
void init(Ant *a){
	a->step = 1;
	a->accu_dis = 0; 
	for(int i = 0 ; i < MAXN; i++){
		a->visited[i] = -1;
		a->order[i] = -1;
	}
	//���ѡ��һ����ʼλ��
	a->curr = rand()%MAXN; 
	
	//�ڷ��ʹ��ĳ�������Ӧ��λ������1
	a->visited[a->curr] = 1;
	//�ڷ���˳�������е�ǰλ�� 
	a->order[a->step - 1] = a->curr;
} 
 
//����ѡ��Ҫǰ���ĳ��� ���Ѿ������г��з����� ����-1���򷵻���һ��������ѡ��ĳ��� 
// ����˫����ָ����� ��Ϣ�ؾ��� �� ������� 
int next(Ant *ant, double *p){
	int next;
	if(ant->step == MAXN) return -1;
	//ֻʣһ���Ļ�Ҳ��ֱ���߾ͺ��� 
	if(ant->step == MAXN-1){
		int i ;
		for(i = 0 ; i < MAXN ; i++){
			if(ant->visited[i] == -1) break;
		}
		return i; 
	} 
	//����Ļ�����ֻʣ���������� Ҫ���ո������ж�
	//��ҡ���� �����ǰ����������ԭ���ǰ��չ���̽��ԭ��������  ACS State Transition Law
//	srand((unsigned int)time(NULL));
	double q = rand()/32767.0;
	// ���С��Q0 ִ�� ������� ԭ�� 
	if(q < Q0){
		double max = -1;
		for(int i = 0 ; i < MAXN ; i++){
			if(ant->visited[i] == -1){
				if(*(p+MAXN*(ant->curr)+i) > max){
					max = *(p+MAXN*(ant->curr)+i);
					next = i;
				}
				
			}
		} 
	}else{ // ����ִ�� ����̽��ԭ�� 
	    int pos[MAXN - ant->step];
		double value[MAXN - ant->step];
		double possibility[MAXN - ant->step];
		for(int j = 0 ; j < (MAXN - ant->step);j++){
			possibility[j] = 0;
		}
		int count = 0;
		for(int i = 0 ; i < MAXN ; i++){
			if(ant->visited [i]== -1){
				pos[count] = i;
				value[count] = *(p+MAXN*(ant->curr)+i);
				count++;
			}
		}
		//���ۻ���������������
		//�����value������ܺ�
		double sum = 0;
		for(int k = 0 ; k < MAXN-ant->step ; k++){
			sum += value[k];
		} 
		for(int k = 0 ; k < MAXN-ant->step ; k++){
			value[k] /= sum;
		} 
		
		for(int i = 0 ; i < MAXN-ant->step ; i++){
			for(int j = 0 ; j <= i ; j++){
				possibility[i]+=value[j];
			}
		} 
		//�ڵõ��ۻ������б��Ժ� ��������� ���������ĸ����� ��ѡ���ĸ�next
		double pp = rand()/32767.0;
		for(int i=0; i< MAXN-ant->step; i++){
			if(pp < possibility[i]){
				next = pos[i];
				break;
			}
		}
	}
	
	return next; 
	 
} 

//�ֲ����¹��� 
void local_update(Ant *ant, int next, double *f ,double *d, double *p){
	//������Ϣ�ؾ���
	*(f+MAXN*ant->curr+next) = (1-RHO) * (*(f+MAXN*ant->curr+next)) + RHO * T0;
	//������Ϣ��-����product���� 
	*(p+MAXN*ant->curr+next) = (*(f+MAXN*ant->curr+next))/pow((*(d+MAXN*ant->curr+next)),BETA);
} 

//ȫ�ָ��¹��� 
void global_update(Ant* best, double *f, double *d, double *p){
	//�Ȼӷ� 
	for(int i = 0 ; i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
			*(f+MAXN*i+j) = (1-ALPHA) * (*(f+MAXN*i+j));
		}
	}
	//������õ����ϵĸ�����ǿ
	for(int i = 0 ; i < MAXN-1; i++){
		*(f + MAXN * best->order[i] + best->order[i+1]) += ALPHA / (best->accu_dis);
	}
	//����һ�³˻�����
	for(int i = 0 ; i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
			*(p+MAXN*i + j) = (*(f+MAXN*i+j))/pow((*(d+MAXN*i+j)),BETA);
		}
	} 
}

//������ѡ��ĳ���move���ҽ��оֲ�����
void moveto(Ant *ant, int next, double *f, double *d, double *p){
	//�Ƚ��оֲ�����
	local_update(ant,next,f,d,p);
	//���ϵ�move����
	ant->accu_dis += (*(d+MAXN*ant->curr + next)); //�����ۻ�������� 
	ant->curr = next; //���������ڵ�λ�ñ�Ϊ next
	ant->step++; //������һ��
	//�ڷ���˳�������е�ǰλ�� 
	ant->order[ant->step - 1] = next;
	//�ڷ��ʹ��ĳ�������Ӧ��λ������1
	ant->visited[ant->curr] = 1;
	
} 

 


 
//���ļ��еľ�γ�����ݶ�������׼���õ�array���� 
void read_data(char *path, double *longitude, double *latitude){
	FILE *fp = fopen(path,"r");
	//������ǰ���û�õ���Ϣ���� 
	char *tmp = (char*)malloc(MAXN);
	while(1){
		fgets(tmp,MAXN,fp);
		if(strcmp(tmp,"NODE_COORD_SECTION\n") == 0 ) break;
	} 
	// ��ʼ������������
	int t;
	for(int i = 0; i < MAXN; i++){
		fscanf(fp,"%d %lf %lf",&t,&latitude[i],&longitude[i]);
	}
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
	double dij = ( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ));
	return dij;
}

//����ŷ����þ������
double get_dis_euc(double x1, double x2, double y1 , double y2){
	double d = sqrt((pow(x1-x2,2)) + pow(y1-y2,2));
	return d;
} 


//����Ϊȫ�ֱ���ʡ�ռ� 
//һЩ��Ҫ�Ĵ�����ݵĽṹ 

double feromine[MAXN][MAXN];
double product[MAXN][MAXN];
double distance[MAXN][MAXN];
Ant ants[NUM_ANTS];


int main(int argc, char* argv[]){
	double *longitude = malloc(sizeof(double) * MAXN);
	double *latitude = malloc(sizeof(double) * MAXN); 
	
	//��ȡ����ĳ��еľ�γ�� 
	read_data("kroA100.tsp",longitude,latitude);
	 
	//����������� 
	for(int i = 0 ;i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
//			double lon1= convert(longitude[i]);
//			double lat1 = convert(latitude[i]);
//			double lon2= convert(longitude[j]);
//			double lat2 = convert(latitude[j]);
			double x1 = longitude[i],x2=longitude[j],y1=latitude[i],y2=latitude[j];
//			distance[i][j] = get_dis_ll(lon1,lat1,lon2,lat2); 
			distance[i][j] = get_dis_euc(x1,x2,y1,y2);
		}
	} 
	//��ʱfree��
	free(longitude);
	free(latitude);
	//��ʼ����Ϣ�ؾ��� �������϶�����һ��������и���
	for(int i = 0 ; i < MAXN; i++){
		for(int j = 0 ; j < MAXN; j++){
			feromine[i][j] = T0;
		}
	} 
	
	//��ʼ�����߳˻����� �������ĵİ취��ʼ��
	for(int i=0;i<MAXN;i++){
		for(int j = 0; j< MAXN; j++){
			product[i][j] = feromine[i][j] / pow(distance[i][j],BETA);
		}
	} 
	
	
	
	//��ʼ����iteration
	int iter = 1;
	//����һ����ӡ��֪��
	int cnt = 0; 

	//����һ������Ŀǰ��ȫ������
	int Lgb = 99999999; 
	//����һ����ǰ��õ����� 
	Ant best;  
	//֪��������Ϊ�����˾ͽ���iter  
	srand((unsigned int)time(NULL)); //��һ�������������
	while(1){
		

		//ÿһ�ֶ�Ҫ���³�ʼ��һ������ 
		for(int i =0 ; i< NUM_ANTS; i++){
			Ant a;
			init(&a);
			ants[i] = a;
		} 
		
		
		//��һ��iteration�� ��ÿһֻ���Ͻ��й���·�� ��Ϊһ��step 
		for(int i =0 ; i < NUM_ANTS ; i++){
			while(1){
				//ȷ����ֻ������һ��ȥ�ĵط�
				int nt = next(&ants[i], product[0]);
				if(nt == -1) break;
				//move����һ��ȥ�ĵط� ����moveto������ִ�б��ظ��� ����Ϣ��ָ���ȥ 
				moveto(&ants[i],nt, feromine[0],distance[0],product[0]);
			}
			//�˳����Ժ���ʵ����һ��Ҫ�� �������һ���ص�����������һ�� ҲҪ�����
			(&ants[i])->accu_dis += distance[ants[i].order[0]][ants[i].order[MAXN-1]];
			//����Ӧ�ø�������·����Ϣ��
			local_update(&ants[i],ants[i].order[0],feromine[0],distance[0],product[0]);  
			
			//�����ǰ��ֻ���Ϲ�����·������֮ǰ��ȫ������ �滻֮
			if(ants[i].accu_dis < Lgb){
				Lgb = ants[i].accu_dis;
				best = ants[i]; //������best��¼��������õ����ϵ��±� 
			} 
		}
		//�������Ϲ�����·���� ����ȫ�ָ���
		global_update(&best,feromine[0],distance[0],product[0]); 
		
		//ֹͣ��ʱ
		double end = (double)clock()/CLOCKS_PER_SEC;
		
		//ÿʮ�ε�����ӡһЩ������Ϣ
		cnt++;  
		if(cnt%500 == 0){
			printf("-----------------------\n");
			printf("already %d iteration\nTime Used:  %f sec\nThe BEST: %d km\n",cnt,end,Lgb);
			printf("-----------------------\n");
			
		}
		//����������������Ƿ��˳�����
		//����ʱ���յ���һ�������˳� ����
		if(cnt > 30000) break;
		iter++;
	}
	return 0;
	
} 
