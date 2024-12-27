#include "sklad.h"
#include "ui_sklad.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Sklad::Sklad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sklad) // Инициализация правильного класса Ui::Sklad
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/deja vu/Desktop/crmDIT/БД/sklad.accdb");

    if (db.open()) {
        qDebug("База данных успешно открыта.");
    } else {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
    }

    // Настройка модели для отображения данных в QTableView
    model = new QSqlTableModel(this, db);
    model->setTable("Sklad");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents(); // Автоматическая подгонка ширины
    ui->tableView->setColumnWidth(0, 50);  // ID
    ui->tableView->setColumnWidth(1, 200); // Название товара
    ui->tableView->setColumnWidth(2, 200); // Количество
    ui->tableView->setColumnWidth(3, 200);
}

Sklad::~Sklad()
{
    delete ui;
}
    void Sklad::on_pushButton_add_clicked()
    {

            QString id = ui->lineEdit_id->text();
            QString name = ui->lineEdit_name->text();
            QString quantity = ui->lineEdit_quantity->text();
            QString price = ui->lineEdit_price->text();

            // Проверка на заполненность всех полей
            if (id.isEmpty() || name.isEmpty() || quantity.isEmpty() || price.isEmpty()) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("Все поля должны быть заполнены!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
                return;
            }

            // Проверка: ID, количество и цена должны быть числовыми
            bool idOk, quantityOk, priceOk;
            int idValue = id.toInt(&idOk);
            int quantityValue = quantity.toInt(&quantityOk);
            double priceValue = price.toDouble(&priceOk);

            if (!idOk || !quantityOk || !priceOk) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("ID, количество и цена должны быть числовыми!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
                return;
            }

            // Подтверждение добавления записи
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setWindowTitle("Подтверждение");
            msgBox.setText(QString("Вы уверены, что хотите добавить запись?\n\n"
                                   "ID: %1\nНазвание: %2\nКоличество: %3\nЦена: %4")
                               .arg(idValue)
                               .arg(name)
                               .arg(quantityValue)
                               .arg(priceValue));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Да");
            msgBox.setButtonText(QMessageBox::No, "Нет");

            if (msgBox.exec() == QMessageBox::No) {
                return;
            }

            // SQL-запрос для добавления записи
            QSqlQuery query;
            query.prepare("INSERT INTO Sklad (ID, [Название товара], Количество, Цена) VALUES (?, ?, ?, ?)");
            query.addBindValue(idValue);
            query.addBindValue(name);
            query.addBindValue(quantityValue);
            query.addBindValue(priceValue);

            if (query.exec()) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Information);
                msgBox.setWindowTitle("Успех");
                msgBox.setText("Запись успешно добавлена!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();

                model->select(); // Обновляем таблицу

                // Очищаем поля ввода
                ui->lineEdit_id->clear();
                ui->lineEdit_name->clear();
                ui->lineEdit_quantity->clear();
                ui->lineEdit_price->clear();
            } else {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("Не удалось добавить запись: " + query.lastError().text());
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
            }
        }



    void Sklad::on_pushButton_clicked()
    {
            QString id = ui->lineEdit_id->text(); // Используем поле для ввода ID

            if (id.isEmpty()) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("Введите ID для удаления!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
                return;
            }

            // Проверка: является ли ID числом
            bool idOk;
            int idValue = id.toInt(&idOk);
            if (!idOk) {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Warning);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("ID должен быть числом!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
                return;
            }

            // Подтверждение удаления
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setWindowTitle("Подтверждение");
            msgBox.setText(QString("Вы уверены, что хотите удалить запись с ID %1?").arg(idValue));
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setButtonText(QMessageBox::Yes, "Да");
            msgBox.setButtonText(QMessageBox::No, "Нет");

            if (msgBox.exec() == QMessageBox::No) {
                return;
            }

            // SQL-запрос для удаления записи
            QSqlQuery query;
            query.prepare("DELETE FROM Sklad WHERE ID = ?");
            query.addBindValue(idValue);

            if (query.exec()) {
                if (query.numRowsAffected() > 0) {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Information);
                    msgBox.setWindowTitle("Успех");
                    msgBox.setText(QString("Запись с ID %1 успешно удалена!").arg(idValue));
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setButtonText(QMessageBox::Ok, "Ок");
                    msgBox.exec();
                } else {
                    QMessageBox msgBox;
                    msgBox.setIcon(QMessageBox::Warning);
                    msgBox.setWindowTitle("Ошибка");
                    msgBox.setText(QString("Запись с ID %1 не найдена!").arg(idValue));
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setButtonText(QMessageBox::Ok, "Ок");
                    msgBox.exec();
                }
                model->select(); // Обновляем таблицу
            } else {
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Critical);
                msgBox.setWindowTitle("Ошибка");
                msgBox.setText("Не удалось удалить запись: " + query.lastError().text());
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.setButtonText(QMessageBox::Ok, "Ок");
                msgBox.exec();
            }
        }

