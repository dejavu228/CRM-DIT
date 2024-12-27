#include "hub.h"
#include "ui_hub.h"
#include <workers.h>
#include <sklad.h>
#include <cotalog.h>


Hub::Hub(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Hub)
{
    ui->setupUi(this);

}

Hub::~Hub()
{
    delete ui;
}


void Hub::on_pushButtonWorkers_clicked()
{
    Workers workersDialog(this);
    workersDialog.exec();
}



void Hub::on_Exit_clicked()
{
    this -> close();
}

void Hub::on_SkladButton_clicked()
{
    Sklad *skladWindow = new Sklad(this); // Передаём Hub как родителя
    skladWindow->setAttribute(Qt::WA_DeleteOnClose); // Удалить окно при закрытии
    skladWindow->show(); // Показываем окно
}


