#include "drawhelper.h"
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <cmath>
#include <iostream>
#include "graph.h"

drawhelper::drawhelper(QGraphicsScene *s) : scene(s)
{
}

void drawhelper::draw_node(double y, int type)
{
    // 定义一个 item
    QGraphicsEllipseItem *pItem = new QGraphicsEllipseItem();

    // 设置画笔、画刷
    QPen pen = pItem->pen();
    pen.setWidth(5);
    pen.setColor(Qt::white);
    pItem->setPen(pen);
    switch(type) {
    case 0:
        pItem->setBrush(QBrush(Qt::red));
        break;
    case 1:
        pItem->setBrush(QBrush(Qt::green));
        break;
    case 2:
        pItem->setBrush(QBrush(Qt::blue));
        break;
    default:
        pItem->setBrush(QBrush(Qt::yellow));
    }

    double x = (type+1) * margin_x;
    y = (y+1) * margin_y;
    // 矩形区域 圆心：(x, y) 宽：r 高：r
    pItem->setRect(QRectF(x-r/sqrt(2), y-r/sqrt(2), r, r));
    pItem->setStartAngle(0);  // 起始角度
    pItem->setSpanAngle(16*360);  // 跨角

    scene->addItem(pItem);
}

void drawhelper::draw_line(double y1, int type1, double y2, int type2)
{
    double x1 = (type1+1) * margin_x;
    double x2 = (type2+1) * margin_x;
    y1 = (y1+1) * margin_y;
    y2 = (y2+1) * margin_y;
    scene->addLine(x1, y1, x2, y2);
}

void drawhelper::draw_graph(int m, int n, int a, int b)
{
    scene->clear();
    graph g(m, n, a, b);
    if (g.dinic()) {
        double gap = ((double)(abs(m-n)))/2;
        int i, j;
        draw_node((m > n ? m : n) / 2, 0);
        if (m > n) {
            for (i = 0; i < m; i++) {
                draw_node(i, 1);
                draw_line((m > n ? m : n) / 2, 0, i, 1);
            }
            for (i = 0; i < n; i++) {
                draw_node(i+gap, 2);
                draw_line(i+gap, 2, (m > n ? m : n) / 2, 3);
            }
            for (i = m + 1; i < m + n + 1; ++i)
                for (j = 1; j < m + 1; ++j)
                    if (g.adj[i][j] > 0) draw_line(j-1, 1, i-1 - m + gap, 2);
        }
        else {
            for (i = 0; i < m; i++) {
                draw_node(i+gap, 1);
                draw_line((m > n ? m : n) / 2, 0, i+gap, 1);
            }
            for (i = 0; i < n; i++) {
                draw_node(i, 2);
                draw_line(i, 2, (m > n ? m : n) / 2, 3);
            }
            for (i = m + 1; i < m + n + 1; ++i)
                for (j = 1; j < m + 1; ++j)
                    if (g.adj[i][j] > 0) draw_line(j-1 + gap, 1, i - 1 - m, 2);
        }
        draw_node((m > n ? m : n) / 2, 3);
    }
    else scene->addText("No Solution!", QFont("Calibri"));
}
