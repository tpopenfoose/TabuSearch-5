#include "messagebox.h"

DataLoss::DataLoss()
{
    setText("Uwaga!");
    setInformativeText("Dotyczczasowe dane zostaną utracone?");
    setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    setDefaultButton(QMessageBox::Cancel);
}

OneTask::OneTask()
{
    setText("Nie mozna usunąć pierwszego okna.");
    setStandardButtons(QMessageBox::Ok);
}

CalculationsInProgress::CalculationsInProgress()
{
    setText("Trwają obliczenia.");
    setInformativeText("Czy chcesz zatrzymać?");
    setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    setDefaultButton(QMessageBox::Cancel);
}

PossibleDataLoss::PossibleDataLoss()
{
    setText("Zmiany zostaną utracone.");
    setInformativeText("Czy chcesz zapisać?");
    setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    setDefaultButton(QMessageBox::Save);
}
