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
    m_painter.begin(this);

    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &m_painter, this);

    for(auto & iter : m_result.getResult())
        iter->draw(m_painter,m_result.get_size(), 1);

    m_painter.end();
}

void Board::paintBoard(const Result & p_result)
{
    m_result = p_result;

    setFixedSize(m_result.get_width()+4,m_result.get_height()+4);

    update();

    setVisible(true);
}
