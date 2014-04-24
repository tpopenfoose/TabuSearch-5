#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QtGui>

class TaskLayout;

class MainScreen : public QScrollArea
{
public:

    MainScreen(QWidget * parent = 0);

private:

    QWidget *innerScreen;
};

#endif // MAINSCREEN_H
