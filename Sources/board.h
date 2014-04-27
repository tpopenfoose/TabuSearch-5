#ifndef BOARD_H
#define BOARD_H

#include "globalne.h"
#include <QtGui>
#include <QWidget>

class Board : public QWidget
{
   Q_OBJECT

public:

   Board(QWidget *parent = 0);

protected:

   void paintEvent(QPaintEvent *);

private:

   QPainter painter;

   TSF tsf;

public slots:

   void paintBoard(TSF);
};

#endif // Board_H
