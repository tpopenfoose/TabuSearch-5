#ifndef PROGRESSBOX_H
#define PROGRESSBOX_H

#include <QDockWidget>
#include <QLabel>
#include <QProgressBar>

class ProgressBox : public QDockWidget
{
public:
    ProgressBox();
    QLabel *ETL;
    QProgressBar *progressbar;
};

#endif // PROGRESSBOX_H
