#include "cotalog.h"
#include "ui_cotalog.h"

Cotalog::Cotalog(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cotalog)
{
    ui->setupUi(this);
}

Cotalog::~Cotalog()
{
    delete ui;
}
