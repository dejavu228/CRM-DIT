#ifndef SKLAD_H
#define SKLAD_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class Sklad;
}

class Sklad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sklad(QWidget *parent = nullptr);
    ~Sklad();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_clicked();

private:
    Ui::Sklad *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};

#endif // SKLAD_H
