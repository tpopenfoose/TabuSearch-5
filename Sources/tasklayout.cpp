#include "tasklayout.h"

#include <iostream>

using namespace std;

TaskLayout::TaskLayout(int width, QWidget *parent)
    : QLayout(parent)
{
    int column_count = (width)/200;
    int margin = 10;
    space = (width-(column_count*200)-(2*margin))/(column_count-1);

    setContentsMargins(margin, margin, margin, margin);
}

TaskLayout::~TaskLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void TaskLayout::addItem(QLayoutItem *item)
{
    itemList.append(item);
}

void TaskLayout::removeItem(QLayoutItem *item)
{
    itemList.removeOne(item);
}

int TaskLayout::count() const
{
    return itemList.size();
}

QLayoutItem *TaskLayout::itemAt(int index) const
{
    return itemList.value(index);
}

QLayoutItem *TaskLayout::takeAt(int index)
{
    if (index >= 0 && index < itemList.size())
        return itemList.takeAt(index);
    else
        return 0;
}

Qt::Orientations TaskLayout::expandingDirections() const
{
    //return Qt::Horizontal|Qt::Vertical;
    return 0;
}

bool TaskLayout::hasHeightForWidth() const
{
    return true;
}

int TaskLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}

void TaskLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize TaskLayout::sizeHint() const
{
    return minimumSize();
}

QSize TaskLayout::minimumSize() const
{
    QSize size;
    QLayoutItem *item;
    foreach (item, itemList)
    {
        size = size.expandedTo(item->minimumSize());
    }

    size += QSize(2*margin(), 2*margin());

    return size;
}

int TaskLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int lineHeight = 0;

    QLayoutItem *item;
    foreach (item, itemList)
    {
        int nextX = x + item->sizeHint().width() + space;

        if (nextX - space > effectiveRect.right() && lineHeight > 0)
        {
            x = effectiveRect.x();
            y = y + lineHeight + space;
            nextX = x + item->sizeHint().width() + space;
            lineHeight = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect(QPoint(x, y), item->sizeHint()));

        x = nextX;
        lineHeight = qMax(lineHeight, item->sizeHint().height());
    }
    return y + lineHeight - rect.y() + bottom;
}
