#ifndef BOARD_H
#define BOARD_H

#include <QtGui>

class BoardIf : public QWidget
{
   Q_OBJECT

public:

   BoardIf(QWidget *parent = 0);
   //virtual void paintBoard(TSF);
};

#endif // Board_H
