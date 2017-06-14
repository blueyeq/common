#include "stdAfx.h"
#include "divide_section.h"

int main2()
{
    freopen("edges.txt","r",stdin);
    freopen("edges_out.txt","w",stdout);
    DiviDeSection div;
    double p1x,p1y,p2x,p2y;
    while(~scanf("%lf%lf%lf%lf",&p1x,&p1y,&p2x,&p2y)){
        geo::Point2X p1(p1x,p1y), p2(p2x,p2y);
        geo::Line line(p1,p2);
        div.addLine(line);
    }
    std::vector<geo::Section2X> sections;
    div.getSections(sections);
    /*printf("sections count:%zu\n",sections.size());*/
    for(int i = 0; i < sections.size(); ++i){
		sections[i].id=i;
		//printf("%d\n",sections[i].id);
        sections[i].print();
    }
    return 0;
}
/* sw=2;ts=2;sts=2;expandtab */
