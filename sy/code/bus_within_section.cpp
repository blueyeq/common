#include <stdio.h>
#include <vector>

#include "stdAfx.h"
#include "polygon.h"
using namespace std;

std::vector<geo::Section2X> readSections()
{
  FILE *fileReading=freopen("edges_out.txt","r",stdin);
	std::vector<geo::Section2X> sections;
  int n_points(0);
  while(~scanf("%d",&n_points)){
    geo::Section2X sec;
    for(int i = 0; i < n_points;++i){
	    double px,py;
      scanf("%lf%lf",&px,&py);
      geo::Point2X tmp_point(px,py);
		  sec.add_points(tmp_point);
    }
	  sections.push_back(sec);
  }
	fclose(fileReading);
	return sections;
}

void busWithinSection(vector<geo::Section2X> &secs)
{
  FILE *fileReading=freopen("busStation.txt","r",stdin);
  FILE *fileWriting =freopen("bus_station_sec.txt","w",stdout);
  int bus_id, station_id;
  double lat,lon; 
  Polygon poly;
  while(~scanf("%d%d%lf%lf",&bus_id,&station_id,&lat,&lon)){
    geo::Point2X point(lat,lon);
    int belong_sec = -1;
    for(int i = 0; i < secs.size(); ++i){
      if(poly.IsWithin(secs[i],point)){
        belong_sec = i+1;
        break;
      }
    }
    printf("%d %d %d\n",bus_id,station_id,belong_sec);
  }
	fclose(fileReading);
	fclose(fileWriting);
}

int main()
{
  vector<geo::Section2X> secs = readSections();
  busWithinSection(secs);
  return 0;
}
/* sw=2;ts=2;sts=2;expandtab */
