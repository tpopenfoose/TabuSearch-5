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
        iter->draw(m_painter, m_data.size, 1);

    m_painter.end();
}

void Board::paintBoard(const Result & p_result, const ConfigData& p_data)
{
    m_result = p_result;
    m_data = p_data;

    setFixedSize(m_data.width + 4, m_data.height + 4);

    update();

    setVisible(true);
}
