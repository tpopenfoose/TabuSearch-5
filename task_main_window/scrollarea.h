#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QScrollArea>
#include <QLabel>
#include "board.h"

class ScrollArea : public QScrollArea
{
public:
    ScrollArea();

    QLabel *resultlabel1;
    QLabel *resultlabel2;

    Board *board1;
    Board *board2;
};

#endif // SCROLLAREA_H
