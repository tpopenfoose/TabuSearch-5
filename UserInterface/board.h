#ifndef BOARD_H
#define BOARD_H

#include "result.h"
#include <QWidget>

class Board : public QWidget
{

public:

   Board(QWidget *parent = 0);
   void paintBoard(const Result & p_result);

protected:

   void paintEvent(QPaintEvent *);

private:

   QPainter m_painter;
   Result m_result;
};

#endif // Board_H
