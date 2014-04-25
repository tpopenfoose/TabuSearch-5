#include "board.h"
#include <QStyleOption>

Board::Board(QWidget *parent) : QWidget(parent)
{
    painter = new QPainter;
    QString styl = "border: 2px  solid  blue";
    this->setStyleSheet(styl);
    this->hide();

    penwidth = 1;
    halfpen = penwidth/2;
}

void Board::paintEvent(QPaintEvent *)
{
    painter->begin(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, painter, this);
    pen.setWidth(penwidth);

    for (int i = 0; i < tsf.result.size(); i++)
    {
        x = tsf.result[i].x;
        y = tsf.result[i].y;
        f = tsf.result[i];

        switch(f.figureName)
        {
            case kolo:
                drawEclipse();
            break;

            case kwadrat:
                drawSquare();
            break;

            case prostokat:
                drawRectangle();
            break;

            case trojkat:
                drawTriangle();
            break;
         }
     }

    painter->end();
}

void Board::drawEclipse(void)
{
    pen.setColor(QColor(255,0,0));
    //pen.setColor(Qt::red);
    painter->setPen(pen);
    painter->drawEllipse(x+2, y+2, tsf.data.size-penwidth, tsf.data.size-penwidth);
}

void Board::drawRectangle(void)
{
    pen.setColor(QColor(0,0,255));
    painter->setPen(pen);

    if(f.pozycja%2 == 0 )
        painter->drawRect(x+2, y+2, tsf.data.size-penwidth, tsf.data.size-10-penwidth);

    else
        painter->drawRect(x+2, y+2, tsf.data.size-10-penwidth, tsf.data.size-penwidth);
}

void Board::drawSquare(void)
{
    pen.setColor(QColor(0,255,0));
    painter->setPen(pen);

    painter->drawRect(x+2, y+2, tsf.data.size-penwidth, tsf.data.size-penwidth);
    //p.fillRect(x+2, y+2, tsf.data.size, tsf.data.size,QBrush(QColor(0,255,0),Qt::SolidPattern));
}

void Board::drawTriangle(void)
{
    pen.setColor(QColor(255,0,255));
    painter->setPen(pen);

    int x1=0,x2=0,x3=0,y1=0,y2=0,y3=0;

    if( f.pozycja == 0)
    {
        x1 = f.x+halfpen;
        y1 = f.y + tsf.data.size-halfpen;

        x2 = f.x + (tsf.data.size/2);
        y2 = f.y+halfpen;

        x3 = f.x + tsf.data.size-halfpen;
        y3 = f.y + tsf.data.size-halfpen;
    }

    if( f.pozycja == 1)
    {
        x1 = f.x+halfpen;
        y1 = f.y+halfpen;

        x2 = f.x + tsf.data.size-halfpen;
        y2 = f.y + (tsf.data.size/2);

        x3 = f.x+halfpen;
        y3 = f.y + tsf.data.size-halfpen;

    }
    if( f.pozycja == 2)
    {
        x1 = f.x+halfpen;
        y1 = f.y+halfpen;

        x2 = f.x + (tsf.data.size/2);
        y2 = f.y + tsf.data.size-halfpen;

        x3 = f.x + tsf.data.size-halfpen;
        y3 = f.y+halfpen;

    }
    if( f.pozycja == 3)
    {
        x1 = f.x + tsf.data.size-halfpen;
        y1 = f.y+halfpen;

        x2 = f.x+halfpen;
        y2 = f.y + (tsf.data.size/2);

        x3 = f.x + tsf.data.size-halfpen;
        y3 = f.y + tsf.data.size-halfpen;
    }

    painter->drawLine(x1+2,y1+2,x2+2,y2+2);
    painter->drawLine(x2+2,y2+2,x3+2,y3+2);
    painter->drawLine(x1+2,y1+2,x3+2,y3+2);

}

void Board::paintBoard(TSF tsf)
{
    this->tsf = tsf;

    this->setFixedSize(tsf.data.width+4,tsf.data.height+4);

    update();

    setVisible(true);
}
