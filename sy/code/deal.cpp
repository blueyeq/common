#include "stdAfx.h"
#include <iostream>

using namespace std;

//��������
//�ṹ�嶨��---vidSecNum��Ӧ�ļ�¼��Ŀ
struct VIDSECnum
{
	int vid;
	int section;
	int num;
};
const int M=151;//������
const int N=1909;//����
VIDSECnum vid_sec_num[M][N];//��Ϊsec,��Ϊvid��ֵΪnum
int vid_sec_re[M][N];//��Ϊsec����Ϊvid��ֵΪ0/1/2

//��������
void read_vsn()
{
	FILE* fileReading=freopen("vid_sec.txt","r",stdin);
	int vid=0;
	int section=0;
	int num=0;
	//��ʼ������
	for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
			{
				vid_sec_num[i][j]=0;
			}
		}
	//���鸳ֵ
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
