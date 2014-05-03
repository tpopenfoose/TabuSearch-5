#ifndef STATUSBOX_H
#define STATUSBOX_H

#include <QDockWidget>
#include <QLCDNumber>

class StatusBox : public QDockWidget
{
public:
    StatusBox();

    QLCDNumber *lcd1;
    QLCDNumber *lcd2;
    QLCDNumber *lcd3;
    QLCDNumber *lcd4;
};

#endif // STATUSBOX_H
