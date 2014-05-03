#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H
#include <QMessageBox>

class DataLoss : public QMessageBox
{
public:
    DataLoss();
};

class OneTask : public QMessageBox
{
public:
    OneTask();
};

class CalculationsInProgress : public QMessageBox
{
public:
    CalculationsInProgress();
};

class PossibleDataLoss : public QMessageBox
{
public:
    PossibleDataLoss();
};

#endif // MESSAGEBOX_H
