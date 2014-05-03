#include "statusbox.h"
#include <QVBoxLayout>
#include <QLabel>

StatusBox::StatusBox() : QDockWidget()
{
    setFeatures(QDockWidget::NoDockWidgetFeatures);
    setFixedWidth(100);
    QWidget *titleWidget = new QWidget(this);
    setTitleBarWidget( titleWidget );

    QWidget *statusboxwidget = new QWidget;
    QVBoxLayout *statusboxlayout = new QVBoxLayout(statusboxwidget);

    QLabel *statusboxlabel1 = new QLabel(tr("Pierwsze"));
    statusboxlabel1->setFixedSize(90,15);

    QLabel *statusboxlabel2 = new QLabel(tr("Ilość figur:"));
    statusboxlabel2->setFixedSize(90,15);

    lcd1 = new QLCDNumber;

    QLabel *statusboxlabel3 = new QLabel(tr("Procent skrawków:"));
    statusboxlabel3->setFixedSize(90,15);

    lcd2 = new QLCDNumber;

    QLabel *statusboxlabel4 = new QLabel(tr("Ostatnie"));
    statusboxlabel4->setFixedSize(90,15);

    QLabel *statusboxlabel5 = new QLabel(tr("Ilość figur:"));
    statusboxlabel5->setFixedSize(90,15);

    lcd3 = new QLCDNumber;

    QLabel *statusboxlabel6 = new QLabel(tr("Procent skrawków:"));
    statusboxlabel6->setFixedSize(90,15);

    lcd4 = new QLCDNumber;

    statusboxlayout->addWidget(statusboxlabel1);
    statusboxlayout->addWidget(statusboxlabel2);
    statusboxlayout->addWidget(lcd1);
    statusboxlayout->addWidget(statusboxlabel3);
    statusboxlayout->addWidget(lcd2);
    statusboxlayout->addWidget(statusboxlabel4);
    statusboxlayout->addWidget(statusboxlabel5);
    statusboxlayout->addWidget(lcd3);
    statusboxlayout->addWidget(statusboxlabel6);
    statusboxlayout->addWidget(lcd4);
    setWidget(statusboxwidget);
}
