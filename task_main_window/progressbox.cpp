#include "progressbox.h"
#include <QHBoxLayout>

ProgressBox::ProgressBox() : QDockWidget()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setFixedHeight(25);
    QWidget* titleWidget = new QWidget(this);
    setTitleBarWidget( titleWidget );

    QWidget *progressboxwidget = new QWidget;
    QHBoxLayout* progressboxlayout = new QHBoxLayout(progressboxwidget);

    ETL = new QLabel;
    ETL->setFixedHeight(15);

    progressbar = new QProgressBar(progressboxwidget);
    progressbar->setRange(0,100);
    progressbar->setValue(0);

    progressbar->setFixedHeight(15);

    progressboxlayout->addWidget(progressbar);
    progressboxlayout->addWidget(ETL);
    setWidget(progressboxwidget);
}
