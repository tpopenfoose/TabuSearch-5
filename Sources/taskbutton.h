#ifndef TASKBUTTON_H
#define TASKBUTTON_H

#include <QPushButton>

class TaskButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TaskButton(QWidget *parent = 0);
    QSize sizeHint() const;
    
signals:
    
public slots:

private:
};

#endif // TASKBUTTON_H
