#include "workers.h"
#include "ui_workers.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Workers::Workers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Workers)
{
    ui->setupUi(this);

    // Подключение к базе данных Access
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ=C:/Users/deja vu/Desktop/crmDIT/БД/workers.accdb");

    if (db.open()) {
        qDebug("База данных успешно открыта.");
    }
    else
    {
        qDebug("Ошибка подключения к базе данных:");
    }

    // Настройка модели для отображения данных в QTableView
    model = new QSqlTableModel(this, db);
    model->setTable("Workers");
    model->select();

    ui->tableView->setModel(model);

    // Подключаем кнопки к слотам
    connect(ui->pushButton_add, &QPushButton::clicked, this, &Workers::on_pushButton_add_clicked);
    connect(ui->pushButton_delete, &QPushButton::clicked, this, &Workers::on_pushButton_delete_clicked);
}

Workers::~Workers()
{
    delete ui;
}

void Workers::on_pushButton_add_clicked()
{
    // Получаем данные из QLineEdit
    QString lastName = ui->lineEdit_lastName->text();
    QString firstName = ui->lineEdit_firstName->text();
    QString position = ui->lineEdit_position->text();

    if (lastName.isEmpty() || firstName.isEmpty() || position.isEmpty()) {
        ui->lineEdit_message->setText("Все поля должны быть заполнены!");
        return;
    }

    // SQL-запрос для получения текущего максимального ID
    QSqlQuery query;
    if (!query.exec("SELECT MAX(ID) FROM Workers")) {
        ui->lineEdit_message->setText("Ошибка: Не удалось получить текущий максимальный ID. " + query.lastError().text());
        return;
    }

    // Получаем максимальный ID и увеличиваем на 1
    int newID = 1; // По умолчанию, если таблица пуста, начинаем с 1
    if (query.next()) {
        newID = query.value(0).toInt() + 1;
    }

    // SQL-запрос для добавления новой записи с вычисленным ID
    query.prepare("INSERT INTO Workers (ID, LastName, FirstName, Position) VALUES (?, ?, ?, ?)");
    query.addBindValue(newID);
    query.addBindValue(lastName);
    query.addBindValue(firstName);
    query.addBindValue(position);

    if (query.exec()) {
        ui->lineEdit_message->setText("Успех: Запись добавлена.");

        // Обновляем таблицу
        model->select();

        // Очищаем поля
        ui->lineEdit_lastName->clear();
        ui->lineEdit_firstName->clear();
        ui->lineEdit_position->clear();
    } else {
        ui->lineEdit_message->setText("Ошибка: Не удалось добавить запись. " + query.lastError().text());
    }
}

void Workers::on_pushButton_delete_clicked()
{
    // Получаем ID из QLineEdit
    QString idToDelete = ui->lineEdit_idToDelete->text(); // Предположим, QLineEdit называется lineEdit_idToDelete

    if (idToDelete.isEmpty()) {
        ui->lineEdit_message->setText("Ошибка: Введите ID для удаления.");
        return;
    }

    // Проверка: является ли ID числом
    bool ok;
    int id = idToDelete.toInt(&ok);
    if (!ok) {
        ui->lineEdit_message->setText("Ошибка: ID должен быть числом.");
        return;
    }

    // Подтверждение удаления
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setWindowTitle("Подтверждение");
    msgBox.setText(QString("Вы уверены, что хотите удалить запись с ID %1?").arg(id));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::No, "Нет");


    QMessageBox::StandardButton reply = static_cast<QMessageBox::StandardButton>(msgBox.exec());
    if (reply == QMessageBox::No) {
        return;
    }

    // SQL-запрос для удаления записи с указанным ID
    QSqlQuery query;
    query.prepare("DELETE FROM Workers WHERE ID = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            ui->lineEdit_message->setText(QString("Успех: Запись с ID %1 успешно удалена!").arg(id));
        } else {
            ui->lineEdit_message->setText(QString("Ошибка: Запись с ID %1 не найдена.").arg(id));
        }


        // Обновляем таблицу
        model->select();


        // Очищаем поле ввода
        ui->lineEdit_idToDelete->clear();
    } else {
        ui->lineEdit_message->setText("Ошибка: Не удалось удалить запись. " + query.lastError().text());
    }


}
