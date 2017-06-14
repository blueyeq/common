#include "stdAfx.h"
#include "polygon.h"
#include "records.h"
#include <ctime>
#include <iostream>

using namespace std;

//�ṹ�嶨��---vid���vid��Ӧ�ļ�¼��Ŀ
struct VIDMAP
{
	int vehicle_id;
	int records_num;
};
//��������
const int N=5694;//ȥ��vid����
const int M=165;//section����
const int numOfNodes=588012;//��¼��
//��������
std::vector<Record> records;
VIDMAP vidmap[N];
int vid_sec_time[N][M];//��Ϊvid,��Ϊsection,ֵΪʱ��
//��������
void readVid();
void readTime();
void readPoint();
void readSection();
void printRecSec();
void readVidRecNum();
void setVidSecTime();
void scanVidmap();
void getVidSecTime(int vehicle_id,int records_num,int n);
void printBina();
void printAll();
std::vector<geo::Section2X> readSection2();
geo::Point2X mid3_point(geo::Point2X p1, geo::Point2X p2, geo::Point2X p3);
void section_point();

int main3()
{
	//part1���õ�records���������
	//clock_t start,finish;
	//start=clock();
	//readVid();
	//readTime();
	//readPoint();
	//readSection();
	//printRecSec();
	//finish=clock();
	//cout<<(finish-start)/CLOCKS_PER_SEC<<endl;

	//part2������records��������vid_sec_time����
	//readVidRecNum();
	//setVidSecTime();
	//scanVidmap();
	//printBina();
	//printAll();

	//part3���ҳ�������һ���������
	section_point();

	system("pause");
    return 0;
}

//��ȡ&д��vehicle_id
void readVid()
{
	FILE* fileReading=freopen("vehicle_id.txt","r",stdin);
	int vid=0;
	while(~scanf("%d",&vid)){
		//printf("%d\n",vid);
		Record record;
		record.vehicle_id=vid;
		records.push_back(record);
	}
	fclose(fileReading);
}

//��ȡ&д��time
void readTime()
{
	FILE* fileReading=freopen("time.txt","r",stdin);
	int time=0;
	for(int i=0;i<records.size();i++){
		scanf("%d",&time);
		records[i].time=time;
	}
	fclose(fileReading);
}

//��ȡ&д��node�ļ�����γ�ȣ�
void readPoint()
{
    FILE* fileReading=freopen("node.txt","r",stdin);
	double px,py;
	std::vector<geo::Point2X> points;
    while(~scanf("%lf%lf",&px,&py)){
        points.push_back(geo::Point2X(px,py));
    }
	for(int i=0;i<records.size();i++){
		records[i].point=points[i];
	}
	fclose(fileReading);
}

//��ȡ&�ж�&д������
void readSection()
{
	double px,py;
    int n_points(0);
    FILE* fileReading=freopen("edges_out.txt","r",stdin);

	//��ȡ����edges_out.txt�б�ע��ÿ��section�ĵ�������n_points
	//ע������section_num��sections[x].id��records[x].section_id��ǰ������sections���飬�ʴ�0��ʼ��������records�����section_id�ֶΣ���ʾʵ�������ϵ�section����=0ʱ�������κ�ʵ��section�У�!=0ʱ��ֵ�Ŵ���section��id
	int section_num=0;
	std::vector<geo::Section2X> sections;
    while(~scanf("%d",&n_points)){
        geo::Section2X sec;
        for(int i = 0; i < n_points;++i){
            scanf("%lf%lf",&px,&py);
            geo::Point2X tmp_point(px,py);
			sec.add_points(tmp_point);
        }	
		sections.push_back(sec);
		sections[section_num].id=section_num;
		//�ж�����ɨ��ȫ�����ж�����ĵ�
        Polygon poly;
        for(int i=0;i<records.size();i++){
			if(records[i].section_id!=0){
				continue;
			}
            bool within = poly.IsWithin(sections[section_num],records[i].point);
            if(within){
				//д������
				records[i].section_id=sections[section_num].id+1;
            }
        }
		section_num++;
    }
	fclose(fileReading);
}

//��ӡ����record��section_id
void printRecSec()
{
	FILE* fileWriting=freopen("section_id.txt","w",stdout);
	for(int i=0;i<records.size();i++)
	{
		printf("%d\n",records[i].section_id);
	}
	fclose(fileWriting);
}

//��ȡȥ�غ��vehicle_id����Ӧ�ļ�¼��vid_recNum
void readVidRecNum()
{
	int count1=0;
	int count2=0;
	int vid,recNum=0;
	//��vehicle_id����ṹ��vidmap
	FILE* fileReading1=freopen("vehicle_id_uni.txt","r",stdin);
	while(~scanf("%d",&vid)){
		vidmap[count1].vehicle_id=vid;
		count1++;
	}
	fclose(fileReading1);
	//��vid_recNum����ṹ��vidmap
	FILE* fileReading2=freopen("vid_recNum.txt","r",stdin);
	while(~scanf("%d",&recNum)){
		vidmap[count2].records_num=recNum;
		count2++;
	}
	fclose(fileReading2);
}

//��ʼ��vid_sec_time��ά����
void setVidSecTime()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			vid_sec_time[i][j]=0;
		}
	}
}

//����vidmap,vidmapΪvid����vid��Ӧ�ļ�¼����NΪvid����
void scanVidmap()
{
	for(int i=0;i<N;i++)
	{
		int vehicle_id=vidmap[i].vehicle_id;
		int records_num=vidmap[i].records_num;
		getVidSecTime(vehicle_id,records_num,i);
	}
}

//����vehicle_id��section_id����ʱ������ʱ��Σ����浽��ά����vid_sec_time��Ӧλ����
void getVidSecTime(int vehicle_id,int records_num,int n)
{
	//ָ��i,j��section_id
	int i=0;
	int j=1;
	int section_id=0;
	//vid-section��Ӧ��һ������ʱ���ڵ����������ʱ�䣬��ʱ��
	int firstTime,lastTime,timeLength=0;

	for(i=0;i<records.size();i++){
		//�ҵ���vid��records�����е�һ�γ��ֵ�λ��
		//��ȵĻ���section_idΪ0���������κ�һ�����������ڣ���ֱ������
		if((records[i].vehicle_id==vehicle_id)||(records[i].section_id==0)){
			break;
		}
	}
	section_id=records[i].section_id;
	firstTime=records[i].time;

	//��i��ʼ�����records_num��Ԫ�ص�vid����vehicle_id
	//i+j<records.size()��ֹrecords����Խ��
	while((j<records_num+1)&&(i+j<records.size())){
		//�������ʼ��section��ͬ
		if(records[i+j].section_id==section_id)
		{
			//do nothing
		}
		//�������ʼ��section����ͬ������ֹ�ö�ʱ��ļ���
		else 
		{
			//section_id==0ʱ��ζ�ŵ㲻���κ������ڣ���ôʱ�䲻���㣨=0��
			if(section_id!=0){
				//����һ����section�㣬��ǰ���һϵ��section��ͬ�ĵ��һ���䣬��ʱ��μ������
				lastTime=records[i+j-1].time;
				timeLength=lastTime-firstTime;
			}
			//������������ʱ��δ��浽�����У������ά������ֵȫΪ0
			//��ά������е��ڲ���n���е���section_id
			vid_sec_time[n][section_id]+=timeLength;
			//����һ���µ���ʼ��
			section_id=records[i+j].section_id;
			firstTime=records[i+j].time;
			//����ִ�и�forѭ����ֱ���������vid�ļ�¼Ϊֹ
		}
		j++;
	}
}

//��ӡ��ά����
void printBina()
{
	FILE* fileWriting=freopen("vid_sec_time.txt","w",stdout);
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			printf("%d\t%d\t%d\n",i,j,vid_sec_time[i][j]);
		}
	}
	fclose(fileWriting);
}

//��ӡwithin_out
void printAll()
{
	FILE* fileWriting=freopen("within_out.txt","w",stdout);
	for(int i=0;i<records.size();i++)
	{
		printf("%d\t%d\t%lf\t%lf\t%d\n",records[i].vehicle_id,records[i].time,records[i].point.m_coords[0],records[i].point.m_coords[1],records[i].section_id);
	}
	fclose(fileWriting);
}

//�����������������ҳ�section������һ�����section
std::vector<geo::Section2X> readSection2()
{
	double px,py;
    int n_points(0);
    FILE *fileReading=freopen("edges_out.txt","r",stdin);

	//��ȡ����edges_out.txt�б�ע��ÿ��section�ĵ�������n_points
	int section_num=0;
	std::vector<geo::Section2X> sections;
    while(~scanf("%d",&n_points)){
        geo::Section2X sec;
        for(int i = 0; i < n_points;++i){
            scanf("%lf%lf",&px,&py);
            geo::Point2X tmp_point(px,py);
			sec.add_points(tmp_point);
        }
		sections.push_back(sec);
    }
	fclose(fileReading);
	return sections;
}

geo::Point2X mid3_point(geo::Point2X p1, geo::Point2X p2, geo::Point2X p3)
{
    double mid_x = (p1.m_coords[0] + p2.m_coords[0] + p3.m_coords[0])/3.0;
    double mid_y = (p1.m_coords[1] + p2.m_coords[1] + p3.m_coords[1])/3.0;
    geo::Point2X p(mid_x,mid_y);
    return p;
}

void section_point()
{
	FILE *file_out=freopen("section_point.txt","w",stdout);
    Polygon poly;
    std::vector<geo::Section2X> secs = readSection2();
    printf("size:%d\n",secs.size());
    for(int i = 0; i < secs.size(); ++i){
        bool find_point = false;
        for(int j = 0; j < secs[i].m_ponits.size();++j){
            geo::Point2X p1 = secs[i].m_ponits[j];
            geo::Point2X p2 = secs[i].m_ponits[(j+1)%secs[i].m_ponits.size()];
            geo::Point2X p3 = secs[i].m_ponits[(j+2)%secs[i].m_ponits.size()];
            geo::Point2X p_mid = mid3_point(p1,p2,p3);

            bool within2 = poly.IsWithin(secs[i],p_mid);
            if(within2){
                find_point = true;
                p_mid.print();
                break;
            }
        }
        if(!find_point){
            puts("error");
        }
    }
	fclose(file_out);
}