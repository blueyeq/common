#include "stdAfx.h"
#include <iostream>

using namespace std;

//常量声明
//结构体定义---vidSecNum对应的记录数目
struct VIDSECnum
{
	int vid;
	int section;
	int num;
};
const int M=151;//区域数
const int N=1909;//车数
VIDSECnum vid_sec_num[M][N];//行为sec,列为vid，值为num
int vid_sec_re[M][N];//行为sec，列为vid，值为0/1/2

//函数定义
void read_vsn()
{
	FILE* fileReading=freopen("vid_sec.txt","r",stdin);
	int vid=0;
	int section=0;
	int num=0;
	//初始化数组
	for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				vid_sec_num[i][j]=0;
			}
		}
	//数组赋值
	while(~scanf("%ld%ld%ld,&vid",&vid,&section,&num))
	{
		for(int i=0;i<M;i++)
		{
			if
			for(int j=0;i<N;j++)
			{

			}
		}
	}
}

int main4()
{
	read_vsn();
	system("pause");
	return 0;
}
