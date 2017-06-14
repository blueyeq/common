#include "stdAfx.h"
#include "polygon.h"
#include "records.h"
#include <ctime>
#include <iostream>

using namespace std;

//结构体定义---vid与该vid对应的记录数目
struct VIDMAP
{
	int vehicle_id;
	int records_num;
};
//常量声明
const int N=5694;//去重vid个数
const int M=165;//section个数
const int numOfNodes=588012;//记录数
//变量声明
std::vector<Record> records;
VIDMAP vidmap[N];
int vid_sec_time[N][M];//行为vid,列为section,值为时间
//函数声明
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
	//part1，得到records向量并输出
	//clock_t start,finish;
	//start=clock();
	//readVid();
	//readTime();
	//readPoint();
	//readSection();
	//printRecSec();
	//finish=clock();
	//cout<<(finish-start)/CLOCKS_PER_SEC<<endl;

	//part2，根据records向量计算vid_sec_time数组
	//readVidRecNum();
	//setVidSecTime();
	//scanVidmap();
	//printBina();
	//printAll();

	//part3，找出区域内一点代替区域
	section_point();

	system("pause");
    return 0;
}

//读取&写入vehicle_id
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

//读取&写入time
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

//读取&写入node文件（经纬度）
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

//读取&判定&写入区域
void readSection()
{
	double px,py;
    int n_points(0);
    FILE* fileReading=freopen("edges_out.txt","r",stdin);

	//读取区域，edges_out.txt中标注了每个section的点数，即n_points
	//注意区分section_num，sections[x].id和records[x].section_id，前两者是sections数组，故从0开始，后者是records数组的section_id字段，表示实际意义上的section，故=0时代表不在任何实际section中，!=0时的值才代表section的id
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
		//判定区域，扫描全部待判定区域的点
        Polygon poly;
        for(int i=0;i<records.size();i++){
			if(records[i].section_id!=0){
				continue;
			}
            bool within = poly.IsWithin(sections[section_num],records[i].point);
            if(within){
				//写入区域
				records[i].section_id=sections[section_num].id+1;
            }
        }
		section_num++;
    }
	fclose(fileReading);
}

//打印所有record的section_id
void printRecSec()
{
	FILE* fileWriting=freopen("section_id.txt","w",stdout);
	for(int i=0;i<records.size();i++)
	{
		printf("%d\n",records[i].section_id);
	}
	fclose(fileWriting);
}

//读取去重后的vehicle_id及对应的记录数vid_recNum
void readVidRecNum()
{
	int count1=0;
	int count2=0;
	int vid,recNum=0;
	//把vehicle_id存入结构体vidmap
	FILE* fileReading1=freopen("vehicle_id_uni.txt","r",stdin);
	while(~scanf("%d",&vid)){
		vidmap[count1].vehicle_id=vid;
		count1++;
	}
	fclose(fileReading1);
	//把vid_recNum存入结构体vidmap
	FILE* fileReading2=freopen("vid_recNum.txt","r",stdin);
	while(~scanf("%d",&recNum)){
		vidmap[count2].records_num=recNum;
		count2++;
	}
	fclose(fileReading2);
}

//初始化vid_sec_time二维数组
void setVidSecTime()
{
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			vid_sec_time[i][j]=0;
		}
	}
}

//遍历vidmap,vidmap为vid及该vid对应的记录数，N为vid个数
void scanVidmap()
{
	for(int i=0;i<N;i++)
	{
		int vehicle_id=vidmap[i].vehicle_id;
		int records_num=vidmap[i].records_num;
		getVidSecTime(vehicle_id,records_num,i);
	}
}

//计算vehicle_id跟section_id不变时的连续时间段，保存到二维数组vid_sec_time对应位置上
void getVidSecTime(int vehicle_id,int records_num,int n)
{
	//指针i,j及section_id
	int i=0;
	int j=1;
	int section_id=0;
	//vid-section对应的一段连续时间内的最早和最晚时间，及时长
	int firstTime,lastTime,timeLength=0;

	for(i=0;i<records.size();i++){
		//找到该vid在records数组中第一次出现的位置
		//相等的或者section_id为0（即不在任何一个已有区域内）的直接跳过
		if((records[i].vehicle_id==vehicle_id)||(records[i].section_id==0)){
			break;
		}
	}
	section_id=records[i].section_id;
	firstTime=records[i].time;

	//从i开始往后的records_num个元素的vid都是vehicle_id
	//i+j<records.size()防止records向量越界
	while((j<records_num+1)&&(i+j<records.size())){
		//如果与起始点section相同
		if(records[i+j].section_id==section_id)
		{
			//do nothing
		}
		//如果与起始点section不相同，则终止该段时间的计算
		else 
		{
			//section_id==0时意味着点不在任何区域内，那么时间不计算（=0）
			if(section_id!=0){
				//遇到一个新section点，则前面的一系列section相同的点告一段落，将时间段计算出来
				lastTime=records[i+j-1].time;
				timeLength=lastTime-firstTime;
			}
			//将上面计算出的时间段储存到数组中，最初二维数组中值全为0
			//二维数组的行等于参数n，列等于section_id
			vid_sec_time[n][section_id]+=timeLength;
			//创建一个新的起始点
			section_id=records[i+j].section_id;
			firstTime=records[i+j].time;
			//继续执行该for循环，直到遍历完该vid的记录为止
		}
		j++;
	}
}

//打印二维数组
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

//打印within_out
void printAll()
{
	FILE* fileWriting=freopen("within_out.txt","w",stdout);
	for(int i=0;i<records.size();i++)
	{
		printf("%d\t%d\t%lf\t%lf\t%d\n",records[i].vehicle_id,records[i].time,records[i].point.m_coords[0],records[i].point.m_coords[1],records[i].section_id);
	}
	fclose(fileWriting);
}

//下面三个方法用于找出section中任意一点代替section
std::vector<geo::Section2X> readSection2()
{
	double px,py;
    int n_points(0);
    FILE *fileReading=freopen("edges_out.txt","r",stdin);

	//读取区域，edges_out.txt中标注了每个section的点数，即n_points
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