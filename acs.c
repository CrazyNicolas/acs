//蚁群算法程序
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<time.h> 
#include<math.h>

#define MAXN 100  //城市数量  表明从测试数据文件中读入多少行 
#define PI 3.141592 // Pi的定义 
#define RRR 6378.388 // 地球半径 
#define Q0 0.8//概率阈值
#define T0  5e-7// （MAXN * 最优总花费）^-1 
#define NUM_ANTS 20//蚁群规模 
#define BETA 2.0 // 距离和信息素综合乘积中距离倒数的次幂 
#define ALPHA 0.2
#define RHO 0.2 // 挥发率 

typedef struct{
	int visited[MAXN]; //访问过的城市
	int order[MAXN]; //访问城市的顺序   
	int curr; //当前位置
	double accu_dis; //目前为止累计的行程数 
	int step; //记录当前已经是第几个城市了 比如一开始当前就是第一个城市了 
}Ant;

//对蚂蚁进行的初始化  
void init(Ant *a){
	a->step = 1;
	a->accu_dis = 0; 
	for(int i = 0 ; i < MAXN; i++){
		a->visited[i] = -1;
		a->order[i] = -1;
	}
	//随机选出一个起始位置
	a->curr = rand()%MAXN; 
	
	//在访问过的城市中相应的位置上置1
	a->visited[a->curr] = 1;
	//在访问顺序数组中当前位置 
	a->order[a->step - 1] = a->curr;
} 
 
//蚂蚁选择要前往的城市 若已经将所有城市访问完 返回-1否则返回下一个此蚂蚁选择的城市 
// 两个双精度指针代表 信息素矩阵 和 距离矩阵 
int next(Ant *ant, double *p){
	int next;
	if(ant->step == MAXN) return -1;
	//只剩一个的话也是直接走就好了 
	if(ant->step == MAXN-1){
		int i ;
		for(i = 0 ; i < MAXN ; i++){
			if(ant->visited[i] == -1) break;
		}
		return i; 
	} 
	//否则的话现在只剩下两个以上 要按照概率来判断
	//先摇骰子 看看是按照利用最大原则还是按照鼓励探索原则来更新  ACS State Transition Law
//	srand((unsigned int)time(NULL));
	double q = rand()/32767.0;
	// 如果小于Q0 执行 利用最大 原则 
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
	}else{ // 否则执行 鼓励探索原则 
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
		//把累积概率数组做出来
		//先求出value数组的总和
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
		//在得到累积概率列表以后 制造随机数 看看落在哪个区间 就选择哪个next
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

//局部更新规则 
void local_update(Ant *ant, int next, double *f ,double *d, double *p){
	//更新信息素矩阵
	*(f+MAXN*ant->curr+next) = (1-RHO) * (*(f+MAXN*ant->curr+next)) + RHO * T0;
	//更新信息素-距离product矩阵 
	*(p+MAXN*ant->curr+next) = (*(f+MAXN*ant->curr+next))/pow((*(d+MAXN*ant->curr+next)),BETA);
} 

//全局更新规则 
void global_update(Ant* best, double *f, double *d, double *p){
	//先挥发 
	for(int i = 0 ; i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
			*(f+MAXN*i+j) = (1-ALPHA) * (*(f+MAXN*i+j));
		}
	}
	//属于最好的蚂蚁的给予增强
	for(int i = 0 ; i < MAXN-1; i++){
		*(f + MAXN * best->order[i] + best->order[i+1]) += ALPHA / (best->accu_dis);
	}
	//更新一下乘积矩阵
	for(int i = 0 ; i < MAXN ; i++){
		for(int j = 0 ; j < MAXN ; j++){
			*(p+MAXN*i + j) = (*(f+MAXN*i+j))/pow((*(d+MAXN*i+j)),BETA);
		}
	} 
}

//蚂蚁向选择的城市move并且进行局部更新
void moveto(Ant *ant, int next, double *f, double *d, double *p){
	//先进行局部更新
	local_update(ant,next,f,d,p);
	//蚂蚁的move操作
	ant->accu_dis += (*(d+MAXN*ant->curr + next)); //更新累积的里程数 
	ant->curr = next; //把蚂蚁现在的位置变为 next
	ant->step++; //多走了一步
	//在访问顺序数组中当前位置 
	ant->order[ant->step - 1] = next;
	//在访问过的城市中相应的位置上置1
	ant->visited[ant->curr] = 1;
	
} 

 


 
//将文件中的经纬度数据读到我们准备好的array里面 
void read_data(char *path, double *longitude, double *latitude){
	FILE *fp = fopen(path,"r");
	//用来把前面的没用的信息读掉 
	char *tmp = (char*)malloc(MAXN);
	while(1){
		fgets(tmp,MAXN,fp);
		if(strcmp(tmp,"NODE_COORD_SECTION\n") == 0 ) break;
	} 
	// 开始读正常的数据
	int t;
	for(int i = 0; i < MAXN; i++){
		fscanf(fp,"%d %lf %lf",&t,&latitude[i],&longitude[i]);
	}
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
	double dij = ( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ));
	return dij;
}

//根据欧几里得距离计算
double get_dis_euc(double x1, double x2, double y1 , double y2){
	double d = sqrt((pow(x1-x2,2)) + pow(y1-y2,2));
	return d;
} 


//设置为全局变量省空间 
//一些必要的存放数据的结构 

double feromine[MAXN][MAXN];
double product[MAXN][MAXN];
double distance[MAXN][MAXN];
Ant ants[NUM_ANTS];


int main(int argc, char* argv[]){
	double *longitude = malloc(sizeof(double) * MAXN);
	double *latitude = malloc(sizeof(double) * MAXN); 
	
	//读取所需的城市的经纬度 
	read_data("kroA100.tsp",longitude,latitude);
	 
	//构建距离矩阵 
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
	//及时free掉
	free(longitude);
	free(latitude);
	//初始化信息素矩阵 所有蚂蚁都对这一个矩阵进行更新
	for(int i = 0 ; i < MAXN; i++){
		for(int j = 0 ; j < MAXN; j++){
			feromine[i][j] = T0;
		}
	} 
	
	//初始化二者乘积矩阵 按照论文的办法初始化
	for(int i=0;i<MAXN;i++){
		for(int j = 0; j< MAXN; j++){
			product[i][j] = feromine[i][j] / pow(distance[i][j],BETA);
		}
	} 
	
	
	
	//开始进行iteration
	int iter = 1;
	//设置一个打印感知器
	int cnt = 0; 

	//设置一个截至目前的全局最优
	int Lgb = 99999999; 
	//设置一个当前最好的蚂蚁 
	Ant best;  
	//知道我们认为收敛了就结束iter  
	srand((unsigned int)time(NULL)); //换一下随机数的种子
	while(1){
		

		//每一轮都要重新初始化一下蚂蚁 
		for(int i =0 ; i< NUM_ANTS; i++){
			Ant a;
			init(&a);
			ants[i] = a;
		} 
		
		
		//在一个iteration中 对每一只蚂蚁进行构建路径 称为一个step 
		for(int i =0 ; i < NUM_ANTS ; i++){
			while(1){
				//确定这只蚂蚁下一个去的地方
				int nt = next(&ants[i], product[0]);
				if(nt == -1) break;
				//move到下一个去的地方 并在moveto函数中执行本地更新 传信息素指针进去 
				moveto(&ants[i],nt, feromine[0],distance[0],product[0]);
			}
			//退出来以后其实还有一步要走 就是最后一个回到最初的起点这一步 也要算距离
			(&ants[i])->accu_dis += distance[ants[i].order[0]][ants[i].order[MAXN-1]];
			//并且应该更新这条路的信息素
			local_update(&ants[i],ants[i].order[0],feromine[0],distance[0],product[0]);  
			
			//如果当前这只蚂蚁构建的路程优于之前的全局最优 替换之
			if(ants[i].accu_dis < Lgb){
				Lgb = ants[i].accu_dis;
				best = ants[i]; //这里用best记录下来了最好的蚂蚁的下标 
			} 
		}
		//所有蚂蚁构建完路程了 进行全局更新
		global_update(&best,feromine[0],distance[0],product[0]); 
		
		//停止计时
		double end = (double)clock()/CLOCKS_PER_SEC;
		
		//每十次迭代打印一些基本信息
		cnt++;  
		if(cnt%500 == 0){
			printf("-----------------------\n");
			printf("already %d iteration\nTime Used:  %f sec\nThe BEST: %d km\n",cnt,end,Lgb);
			printf("-----------------------\n");
			
		}
		//评估收敛情况决定是否退出迭代
		//先暂时按照迭代一定次数退出 来做
		if(cnt > 30000) break;
		iter++;
	}
	return 0;
	
} 
