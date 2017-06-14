#ifndef POLY_H
#define POLY_H

#include "stdAfx.h"
#include <algorithm>

#include "geometry.h"

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

class Polygon{
public:
    bool IsWithin(geo::Section2X poly, geo::Point point);
};

bool Polygon::IsWithin(geo::Section2X poly, geo::Point point)
{
    int n_point = poly.m_ponits.size();
    if(n_point < 3){
        return false;
    }
    int count_(0);
    geo::Point p1 = poly.m_ponits[0];
    for(int i = 1; i <= n_point; ++i){
        geo::Point p2 = poly.m_ponits[i%n_point];
        if(point.m_coords[1] > MIN( p1.m_coords[1],p2.m_coords[1])){
            if(point.m_coords[1] <= MAX(p1.m_coords[1],p2.m_coords[1])){
                if(point.m_coords[0] <= MAX(p1.m_coords[0],p2.m_coords[0])){
                    if(p1.m_coords[1] != p2.m_coords[1]){
                        double xinters = (point.m_coords[1]-p1.m_coords[1])*(p2.m_coords[0]-p1.m_coords[0]) /
                                            (p2.m_coords[1]-p1.m_coords[1])+p1.m_coords[0];
                        if(p1.m_coords[0] == p2.m_coords[0] || point.m_coords[0] <= xinters){
                            count_++;
                        }
                       // printf("count_[%d]\n",count_);

                    }
                }
            }
        }
        p1 = p2;
    }
    //printf("count[%d]\n",count_);
    if(count_ % 2 != 0){
        return true;
    }
    return false;
}
#endif