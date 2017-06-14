#include "stdAfx.h"
#include <stdio.h>
#include <map>
#include <vector>
#include "geometry.h"
#include <cmath>

using namespace std;

const int ROWS=165;
vector<int> id2vid;
int getId(map<int,int> &idmap, int key)
{
  if(idmap.find(key) == idmap.end()){
    int size = idmap.size();
    idmap[key] = size;
    id2vid.push_back(key);
  }
  return idmap[key];
}

void read_vidsec(map<int,vector<int> > &vid_sec_list, map<int,int> &vid_cols, int min_count)
{
  FILE *fin = freopen("vid_sec.txt","r",stdin);
  int sec_id,vid,counts;
  int lines(0);
  while(~scanf("%d%d%d",&vid,&sec_id,&counts)){
    int row = sec_id;//getId(sec_rows,sec_id);
    int col = getId(vid_cols,vid);
    if(counts > min_count){
      vid_sec_list[col].push_back(row);
    }
    ++lines;
  }
  fclose(fin);
  printf("lines:%d\n",lines);
}

void read_bus_station_sec(map<int,vector<int> > &vid_sec_list, map<int,int> &vid_cols)
{
  FILE *fin = freopen("bus_station_sec.txt","r",stdin);
  int bus_id,station_id,sec_id;
  while(~scanf("%d%d%d",&bus_id,&station_id,&sec_id)){
    if(sec_id == -1){
      continue;
    }
    int row = sec_id;//getId(sec_rows,sec_id);
    int col = getId(vid_cols,bus_id);
    vid_sec_list[col].push_back(row);
  }
  fclose(fin);
}

void write_vid2col(const map<int,int>&vid_cols)
{
  FILE *fout = freopen("vid2cols.txt","w",stdout);
  map<int,int>::const_iterator it = vid_cols.begin();
  for( ;it != vid_cols.end(); ++it){
    printf("%d %d\n",it->first,it->second+1);
  }
  fclose(fout);
}
void build_mat(map<int,vector<int> > &vid_sec_list, int rows, int cols)
{
  FILE *fout = freopen("vid_sec_mat.txt","w",stdout);
  for(int i = 1; i <= rows; ++i){
    for(int j = 0; j < cols; ++j){
      int val = -1;
      int vid = -1;
      if(vid_sec_list.find(j) == vid_sec_list.end()){
        val = 0;
      }else{
        val = 0;
        vector<int> rows = vid_sec_list[j];
        if(rows.size()==1 && rows[0] == i){
          val = 2;
        }else{
          for(int k = 0; k < rows.size(); ++k){
            if(rows[k] == i){
              val = 1;
              break;
            }
          }
        }
      }
      if(j>0){
        printf(" ");
      }
      printf("%d",val);
    }
    printf("\n");
  }
  fclose(fout);
}

double distance(geo::Point2X *p1, geo::Point2X *p2)
{
  double dx = (p1->m_coords[0] - p2->m_coords[0]);
  double dy = (p1->m_coords[1] - p2->m_coords[1]);
  return sqrt(dx*dx+dy*dy);
}

void build_dis_mat()
{
  vector<geo::Point2X> points;
  FILE *fin = freopen("section_point.txt","r", stdin);
  FILE *fout = freopen("section_point_dis.txt","w", stdout);
  double px, py;
  while(~scanf("%lf%lf",&px,&py)){
    points.push_back(geo::Point2X(px,py));
  }
  for(int i = 0; i < points.size(); ++i){
    for(int j = 0; j < points.size(); ++j){
      //double dis;// = distance(points[i],points[j]);
	  geo::Point2X p1 = points[i];
	  geo::Point2X p2 = points[j];
	  double dis = distance(&p1,&p2);
      if(j>0){ 
        printf(" ");
      }
      printf("%.4lf",dis);
    }
    printf("\n");
  }
  fclose(fin);
  fclose(fout);
}

int main()
{
  printf("start ...\n");
  map<int,vector<int> > vid_sec_list;
  map<int,int> vid_cols; 
  id2vid.clear();
  int min_count = 37;
  read_vidsec(vid_sec_list,vid_cols,min_count);
//  read_bus_station_sec(vid_sec_list,vid_cols);
  write_vid2col(vid_cols);
  build_mat(vid_sec_list,ROWS,vid_cols.size());
//  build_dis_mat();
  printf("build done.\n");
  return 0;
}

/* sw=2;ts=2;sts=2;expandtab */
