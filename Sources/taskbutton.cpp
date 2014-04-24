#include "taskbutton.h"
#include "files.h"

TaskButton::TaskButton(QWidget *parent) :
    QPushButton(parent)
{
    setIcon(QIcon(add_png.c_str()));
    setFixedSize(200,300);
    setIconSize(QSize(200,200));
    setMinimumSize(200,300);
}

QSize TaskButton::sizeHint() const
{
    return minimumSize();
}
