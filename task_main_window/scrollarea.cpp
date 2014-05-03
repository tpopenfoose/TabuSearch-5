#include "scrollarea.h"
#include <QFormLayout>

ScrollArea::ScrollArea() : QScrollArea()
{
    setMinimumWidth(500);
    setWidgetResizable(true);

    QWidget *scrollareawidget = new QWidget;

    QFormLayout *scrollarealayout = new QFormLayout(scrollareawidget);
    board1 = new Board();
    board2 = new Board();

    resultlabel1 = new QLabel("Pierwszy Wynik");
    resultlabel1->setFixedSize(120,30);
    resultlabel1->hide();
    resultlabel2 = new QLabel("Ostatni Wynik");
    resultlabel2->setFixedSize(120,30);
    resultlabel2->hide();
    scrollarealayout->addRow(resultlabel1, board1);
    scrollarealayout->addRow(resultlabel2, board2);

    setWidget(scrollareawidget);
}
