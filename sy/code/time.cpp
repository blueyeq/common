//�˳�����������׼��ʱ��ͳһΪ�룬����ȡ��ʱ��Ϊͬһ�µģ���ʱ��������տ�ʼ��

#include "stdafx.h"
#include <iostream>
#include "time.h"

using namespace std;

//����
const int records_num=588012;
//����
char* timefile_path="time_in.txt";
char* timefile_path_out="time.txt";
FILE* timefile;
int count;
char cdataTime[50];//Date��ʽΪ��2013-03-01 00:05:10.000��
Mytime mytime[records_num];

void main1()
{
	freopen("time.txt","w",stdout);
	readTime(timefile_path);
}

//ͷ�ļ��з���ʵ��
int Mytime::getSeconds(char cdataTime[50]){
	int seconds=0;
	//ֻ��ȷ���룬����ֻ����ǰ19λ����
	for(int i=0;i<19;i++){
		//����ǰ�ַ�ǿ��תΪint��
		int temp=cdataTime[i]-'0';
		switch(i){
			case 8:{
				//��9λ����10��
				seconds+=temp*10*24*60*60;
				break;
			}
			case 9:{
				//��10λ����1�죨24Сʱ��������-1����Ϊ���������ں����ʱ������
				seconds+=(temp-1)*24*60*60;
				break;
			}
			case 11:{
				//��12λ����10Сʱ
				seconds+=temp*10*60*60;
				break;
			}
			case 12:{
				//��13λ����1Сʱ��60���ӣ�
				seconds+=temp*60*60;
				break;
			}
			case 14:{
				//��15λ����10����
				seconds+=temp*10*60;
				break;
			}
			case 15:{
				//��16λ����1���ӣ�60�룩
				seconds+=temp*60;
				break;
			}
			case 17:{
				//��18λ����10��
				seconds+=temp*10;
				break;
			}
			case 18:{
				//��19λ����1��
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
			////������Ϊ�˷�����ӡ�ٶ�
			//int temp=0;
			//while(temp<100000000){
			//	temp++;
			//}
		}
	}
}
