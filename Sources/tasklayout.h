#ifndef TASKLAYOUT_H
#define TASKLAYOUT_H

#include <QtGui>

class TaskLayout : public QLayout
{
public:
    TaskLayout(QWidget *parent);
    ~TaskLayout();

    void addItem(QLayoutItem *item);
    void removeItem(QLayoutItem *item);
    Qt::Orientations expandingDirections() const;
    bool hasHeightForWidth() const;
    int heightForWidth(int) const;
    int count() const;
    QLayoutItem *itemAt(int index) const;
    QSize minimumSize() const;
    void setGeometry(const QRect &rect);
    QSize sizeHint() const;
    QLayoutItem *takeAt(int index);

private:
    int doLayout(const QRect &rect, bool testOnly) const;

    QList<QLayoutItem *> itemList;

    int space;

};

#endif // TASKLAYOUT_H


