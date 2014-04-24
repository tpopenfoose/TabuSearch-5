#ifndef TASKBUTTONGROUP_H
#define TASKBUTTONGROUP_H

#include <QButtonGroup>
#include <QPushButton>

class TaskButtonGroup : public QButtonGroup
{
    Q_OBJECT

public:

    explicit TaskButtonGroup(QWidget *parent = 0);
    
public slots:

    void buttonClick(QAbstractButton* button);
    
};

#endif // TASKBUTTONGROUP_H
