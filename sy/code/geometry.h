#include "stdAfx.h"
#ifndef _HNU0314_GEO_LIB_H
#define _HNU0314_GEO_LIB_H

#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <vector>

#define PB push_back

#define my_log(...) \
    printf("[%s:%d] ",__FILE__,__LINE__); \
    printf(__VA_ARGS__); puts("")

namespace geo{

//点 或者 向量
class Point{
public:
    Point()
    {
        m_coords.clear();
    }
    virtual double crossProduct(const Point &a) {return 0.0f;}; //向量差积
    virtual double dotProduct(const Point &a){return 0.0f;}    //向量点积
    virtual double cos(Point &a) { return 0.0f;}                //向量夹角的cosin值
    virtual double len() const{  return 0.0f;}                        //向量长度
    bool operator == (const Point &a) const{
        for(int i = 0; i < m_coords.size(); ++i){
            if(m_coords[i] != a.m_coords[i]) {
                return false;
            }
        }
        return true;
    }
    bool operator < (const Point &a) const{

        for(int i = m_coords.size() -1; i >= 0 ; --i){  //按照y值排序
            if(m_coords[i] != a.m_coords[i]){
                return m_coords[i] < a.m_coords[i];
            }
        }
        return false;
    }
    Point operator -(const Point &a) const{
        Point c;
        for(int i = 0; i < m_coords.size(); ++i){
            c.m_coords.PB(m_coords[i]-a.m_coords[i]);
        }
        return c;
    }
    void print() const
    {
        for(int i = 0; i < m_coords.size(); ++i){
            printf("%.4f ",m_coords[i]);
        }
        puts("");
    }
public:
    std::vector<double> m_coords;                    // x,y,z....
};

//而为向量或者点
class Point2X:public Point{
public:
	Point2X()
	{
	}
    Point2X(double px,double py)
    {
        m_coords.clear();
        m_coords.PB(px);
        m_coords.PB(py);
    }
    Point2X(const Point &a)
    {
        m_coords.clear();
        m_coords.PB(a.m_coords[0]);
        m_coords.PB(a.m_coords[1]);
    }
    double crossProduct(const Point &a)
    {
        if(!checkPoint(a)) {
            return 0;
        }
        // x1 * y2 - x2 * y1
        return m_coords[0] * a.m_coords[1] - a.m_coords[0] * m_coords[1];
    }
    double dotProduct(const Point &a)
    {
        if(!checkPoint(a)){
            return 0;
        }
        // x1 * x2 + y1 * y2
        return m_coords[0] * a.m_coords[0] + m_coords[1] * a.m_coords[1];
    }
    double cos(const Point &a)
    {
        if(!checkPoint(a)){
            return 0;
        }
        // x*y/(|x|*|y|)
        double product_dot = dotProduct(a);
        double cos_value = product_dot / (a.len() * len());
        return cos_value;
    }
    double len() const
    {
        if(!checkPoint(*this)){
            return 0;
        }
        // sqrt(x*x + y*y)
        return std::sqrt(m_coords[0] * m_coords[0] + m_coords[1] * m_coords[1]);
    }

private:
    bool checkPoint(const Point &a) const
    {
        if(a.m_coords.size() < 2){
            /*my_log("ERROR: check ponit2X failed size[%zu]",a.m_coords.size());*/
            return false;
        }
        return true;
    }
};

class Line{

public:
    Line(const Point &s, const Point &e){
        m_start = s;
        m_end = e;
    }
    bool operator == (const Line &a){
        return (m_start == a.m_start) && (m_end == a.m_end);
    }
    bool operator < (const Line &a){
        if (m_start == a.m_start){
            return m_end < a.m_end;
        }
        return m_start < a.m_start;
    }
public:
    Point m_start;
    Point m_end;
};


class Section2X{
public:
    Section2X()
    {
        m_ponits.clear();
    }
    void add_points(const Point &p)
    {
        m_ponits.PB(p);
    }
    void print()
    {
        printf("%d\n",m_ponits.size());
        for(int i = 0; i < m_ponits.size(); ++i){
            m_ponits[i].print();
        }
    }
public:
    std::vector<Point2X> m_ponits;
	int id;
};

}


#endif // _HNU0314_GEO_LIB




/* sw=2;ts=2;sts=2;expandtab */
