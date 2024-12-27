#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <Hub.h>                  // Ваше главное окно
#include <QSqlDatabase>           // Для работы с базой данных
#include <QSqlQuery>              // Для выполнения SQL-запросов
#include <QSqlError>              // Для отлова ошибок SQL
#include <QMessageBox>            // Для уведомлений об ошибках
#include <QDebug>                 // Для отладки

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Устанавливаем режим скрытого текста для поля пароля
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    connect(ui->pushButton_showPassword, &QPushButton::clicked, this, &LoginWindow::togglePasswordVisibility);

    // Подключение к базе данных
    if (!connectToDatabase()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных!");
    }
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::isUsernameExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Users WHERE Username = ?");
    query.addBindValue(username);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();  // Получаем количество записей с таким логином
    return count > 0;  // Если больше 0, значит, логин уже существует
}

bool LoginWindow::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=C:/Users/deja vu/Desktop/crmDIT/БД/log.accdb");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        return false;
    }
    qDebug() << "Подключение к базе данных успешно!";
    return true;
}

void LoginWindow::on_pushButton_clicked()
{
    // Получаем логин и пароль из lineEdit
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // Проверка логина и пароля в базе данных
    if (checkCredentials(username, password)) {
        // Если логин и пароль правильные, открываем главное окно
        Hub *hub = new Hub;
        hub->show();
        this->close();
    } else {
        // Если данные неправильные, показываем ошибку
        ui->label_error->setText("Неверный логин или пароль!");
    }
}

bool LoginWindow::checkCredentials(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Users WHERE Username = ? AND Password = ?");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения SQL-запроса:" << query.lastError().text();
        return false;
    }

    return query.next(); // Если запись найдена, логин и пароль верны
}

void LoginWindow::togglePasswordVisibility()
{
    // Переключаем режим отображения пароля
    if (ui->lineEdit_password->echoMode() == QLineEdit::Password) {
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal); // Показываем пароль
    } else {
        ui->lineEdit_password->setEchoMode(QLineEdit::Password); // Скрываем пароль
    }
}





void LoginWindow::on_pushButton_register_clicked()
{
    // Получаем логин и пароль из lineEdit
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    // Проверяем, что поля не пустые
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Поля логина и пароля не должны быть пустыми!");
        return;
    }
    if (isUsernameExists(username)) {
        ui->label_error->setText("Логин уже зарегистрирован!");
        return;
    }
    // Добавляем пользователя в базу данных
    QSqlQuery query;
    query.prepare("INSERT INTO Users (Username, Password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления пользователя в базу данных:" << query.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось зарегистрировать пользователя!");
        return;
    } else{
        ui->label_error->setText("Вы были успешно добавленны");
    }
}


