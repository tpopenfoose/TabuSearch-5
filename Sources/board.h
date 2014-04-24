#ifndef BOARD_H
#define BOARD_H

#include "globalne.h"
#include <QtGui>

class Board : public QWidget
{
   Q_OBJECT

public:

   Board(QWidget *parent = 0);

protected:

   void paintEvent(QPaintEvent *);

private:

   QPainter *painter;
   QPen pen;
   Figure f;
   int x;
   int y;

   int penwidth;
   int halfpen;

   TSF tsf;

   void drawEclipse(void);
   void drawRectangle(void);
   void drawSquare(void);
   void drawTriangle(void);

public slots:

   void paintBoard(TSF);
};

#endif // Board_H
