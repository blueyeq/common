//此程序用来将标准的时间统一为秒，由于取的时间为同一月的，故时间规整从日开始计

#include "stdafx.h"
#include <iostream>
#include "time.h"

using namespace std;

//常量
const int records_num=588012;
//变量
char* timefile_path="time_in.txt";
char* timefile_path_out="time.txt";
FILE* timefile;
int count;
char cdataTime[50];//Date格式为“2013-03-01 00:05:10.000”
Mytime mytime[records_num];

void main1()
{
	freopen("time.txt","w",stdout);
	readTime(timefile_path);
}

//头文件中方法实现
int Mytime::getSeconds(char cdataTime[50]){
	int seconds=0;
	//只精确到秒，所以只考虑前19位即可
	for(int i=0;i<19;i++){
		//将当前字符强制转为int型
		int temp=cdataTime[i]-'0';
		switch(i){
			case 8:{
				//第9位代表10天
				seconds+=temp*10*24*60*60;
				break;
			}
			case 9:{
				//第10位代表1天（24小时），这里-1是因为当天体现在后面的时分秒了
				seconds+=(temp-1)*24*60*60;
				break;
			}
			case 11:{
				//第12位代表10小时
				seconds+=temp*10*60*60;
				break;
			}
			case 12:{
				//第13位代表1小时（60分钟）
				seconds+=temp*60*60;
				break;
			}
			case 14:{
				//第15位代表10分钟
				seconds+=temp*10*60;
				break;
			}
			case 15:{
				//第16位代表1分钟（60秒）
				seconds+=temp*60;
				break;
			}
			case 17:{
				//第18位代表10秒
				seconds+=temp*10;
				break;
			}
			case 18:{
				//第19位代表1秒
				seconds+=temp;
				break;
			}
		}
	}
	return seconds;
}

void readTime(char* timefile1){
	if(NULL==(timefile=freopen(timefile_path,"r",stdin))){
		cout<<"something wrong with time_in.txt"<<endl;
	}
	else{
		count=0;
		while(EOF!=scanf("%.s",&timefile)){
			fgets(cdataTime,sizeof(cdataTime),stdin);
			mytime[count].seconds=mytime[count].getSeconds(cdataTime);
			//cout<<"mytime="<<mytime[count].seconds<<endl;
			printf("%d\n",mytime[count].seconds);
			count++;
			////以下是为了放慢打印速度
			//int temp=0;
			//while(temp<100000000){
			//	temp++;
			//}
		}
	}
}
