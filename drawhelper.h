#ifndef DRAWHELPER_H
#define DRAWHELPER_H

#include <QGraphicsScene>

class drawhelper
{
private:
    QGraphicsScene *scene;
    double r = 20;
    double margin_x = 300;
    double margin_y = 50;
    void draw_node(double y, int type);
    void draw_line(double y1, int type1, double y2, int type2);
public:
    drawhelper(QGraphicsScene *);
    void draw_graph(int m, int n, int a, int b);
};

#endif // DRAWHELPER_H
