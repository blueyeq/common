#include "stdAfx.h"
#include <map>
#include <algorithm>

#include "geometry.h"


class DiviDeSection{
public:
    DiviDeSection():m_points_cnt(0)
    {
        m_lines.clear();
    }
    void addLine(const geo::Line &a);
    int getSections(std::vector<geo::Section2X> &sections);


private:
    int   select_min_point();
    int   get_point_id(const geo::Point2X &point);
    int   select_left(int min_point);
    int   select_right(int start_point,int end_point);
    void  init();
    void  dele_edg(int start_id, int end_id);
    void  build_section(const std::vector<int> &tmp_section,std::vector<geo::Section2X> &sections);
private:
    std::vector<geo::Line> m_lines;
    std::vector<geo::Point2X> m_points;
    std::map<geo::Point2X,int> m_points_id;
    std::vector< std::vector<int> > m_graph;
    std::vector<bool>  m_edg_used;
    std::vector<int> m_points_degree;
    int m_points_cnt;
    std::map<geo::Point2X,int>::iterator m_min_point;
    int m_cur_order_start;
};

void DiviDeSection::addLine(const geo::Line &a){
    m_lines.PB(a);
}

int DiviDeSection::getSections(std::vector<geo::Section2X> &sections)
{
    sections.clear();
    init();
    bool is_end(false);
    while(true){
        // 最低点
        int min_point = select_min_point();
        if(min_point < 0) {
            break;
        }
        // 水平夹角最小的点(逆时针的第一个点)
        int new_point = select_left(min_point);
        if(new_point < 0){
            break;
        }
        //删除这条边
        dele_edg(min_point,new_point);
        int start_point = new_point;
        int end_point = min_point;
        std::vector<int> tmp_section;
        tmp_section.PB(min_point);
        tmp_section.PB(new_point);
        std::map<int,bool> visited; //记录哪些点访问过 重复访问则成环
        visited[min_point] = true;
        visited[new_point] = true;
        while((new_point != min_point) ){
            //顺时针扫点
            new_point = select_right(start_point,end_point);
            //找到环或者最后一条边
            if(new_point < 0 || visited.find(new_point) != visited.end()){
                if(new_point < 0){
                  /*my_log("INFO:process point[%d] done.",min_point);*/
                }
                break;
            }
            end_point = start_point;
            start_point = new_point; // 新点作为起点
            tmp_section.PB(new_point);
            visited[new_point] = true;
        }
        if(new_point == min_point && tmp_section.size() > 2){
          build_section(tmp_section,sections);
          /*my_log("get section count:%zu",sections.size());*/
        }
    }
    return sections.size();
}

int DiviDeSection::get_point_id(const geo::Point2X &point)
{
    if(m_points_id.find(point) == m_points_id.end()){
        m_points_id[point] = m_points_cnt++;
        m_points.PB(point);
        m_graph.PB(std::vector<int>());
        m_points_degree.PB(0);

    }
    return m_points_id[point];
}

void DiviDeSection::init()
{
    m_graph.clear();
    m_points.clear();
    m_points_id.clear();
    m_points_degree.clear();
    m_points_cnt = 0;
    for(int i = 0; i < m_lines.size(); ++i){
        int start_id = get_point_id(m_lines[i].m_start);
        int end_id = get_point_id(m_lines[i].m_end);
        m_graph[start_id].PB(end_id);
        m_graph[end_id].PB(start_id);
        m_points_degree[start_id]++;
        m_points_degree[end_id]++;
    }
    /*printf("points count[%d]\n",m_points_cnt);*/
    m_min_point = m_points_id.begin();
}

void DiviDeSection::dele_edg(int start_id, int end_id)
{
    for(int i = 0; i < m_graph[start_id].size(); ++i){
        if(m_graph[start_id][i] == end_id){
            m_graph[start_id].erase(m_graph[start_id].begin()+i);
            m_points_degree[start_id]--;
            break;
        }
    }
    for(int i = 0; i < m_graph[end_id].size(); ++i){
        if(m_graph[end_id][i] == start_id){
            m_graph[end_id].erase(m_graph[end_id].begin()+i);
            m_points_degree[end_id]--;
            break;
        }
    }

}

int DiviDeSection::select_min_point()
{
    while(m_min_point != m_points_id.end()){
        if(m_points_degree[m_min_point->second] > 1) {
            return m_min_point->second;
        }
        m_min_point++;
    }
    return -1;
}

int DiviDeSection::select_left(int min_point)
{
    geo::Point2X px(1.0,0.0);
    double max_cos(-99.0);
    double len(0.0);
    int left_point(-1);
    for(int i = 0; i < m_graph[min_point].size(); ++i){
        geo::Point2X p_now = m_points[m_graph[min_point][i]] - m_points[min_point];
        double cos = px.cos(p_now);
        if(cos > max_cos) {
            left_point = m_graph[min_point][i];
            max_cos = cos;
            len = p_now.len();
        }else if(cos == max_cos && len > p_now.len()){
            len = p_now.len();
            left_point = m_graph[min_point][i];
        }

    }
    return left_point;
}

int DiviDeSection::select_right(int start_point,int end_point)
{
    int right_point(-1);
    double right_cos(-99);
    double right_product(-999);
    geo::Point2X p_start = m_points[end_point] - m_points[start_point];
    for(int i = 0; i < m_graph[start_point].size(); ++i){
        if(m_graph[start_point][i] == end_point) {
          continue;
        }
        geo::Point2X p_now = m_points[m_graph[start_point][i]] - m_points[end_point];
        double cos = p_now.cos(p_start);
        double product = p_now.crossProduct(p_start);
        if(right_point == -1 ){
            right_point = m_graph[start_point][i];
            right_cos = cos;
            right_product = product;
        }else if(product > 0){
            if(right_product < 0 || cos > right_cos){
                right_point = m_graph[start_point][i];
                right_cos = cos;
                right_product = product;
            }
        }else if(product < 0){
            if(right_product < 0 && cos < right_cos){
                right_point = m_graph[start_point][i];
                right_cos = cos;
                right_product = product;
            }
        }
    }
    return right_point;
}

void  DiviDeSection::build_section(const std::vector<int> &tmp_section,std::vector<geo::Section2X> &sections)
{
    geo::Section2X sec;
    for(int i = 0; i < tmp_section.size(); ++i){
        sec.add_points(m_points[tmp_section[i]]);
    }
    sections.PB(sec);
}

/* sw=2;ts=2;sts=2;expandtab */
