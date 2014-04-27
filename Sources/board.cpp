#include "board.h"
#include <QStyleOption>

Board::Board(QWidget *parent) : QWidget(parent)
{
    QString styl = "border: 2px  solid  blue";
    this->setStyleSheet(styl);
    this->hide();
}

void Board::paintEvent(QPaintEvent *)
{
    painter.begin(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    for(auto & iter : tsf.result)
        iter->draw(painter,tsf.data.size, 1);

    painter.end();
}

void Board::paintBoard(TSF tsf)
{
    this->tsf = tsf;

    this->setFixedSize(tsf.data.width+4,tsf.data.height+4);

    update();

    setVisible(true);
}
