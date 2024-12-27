#ifndef WORKERS_H
#define WORKERS_H

#include "qdialog.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>

namespace Ui {
class Workers;
}

class Workers : public QDialog
{
    Q_OBJECT

public:
    explicit Workers(QWidget *parent = nullptr);
    ~Workers();

private slots:
    void on_pushButton_add_clicked(); // Обработчик кнопки "Добавить"
    void on_pushButton_delete_clicked();

private:
    Ui::Workers *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // WORKERS_H
