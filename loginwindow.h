#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QSqlDatabase>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();   // Слот для кнопки входа
    void togglePasswordVisibility(); // Переключение видимости пароля

    void on_pushButton_register_clicked();

private:
    Ui::LoginWindow *ui;
    bool isUsernameExists(const QString &username);
    // Добавляем объявления новых функций
    bool connectToDatabase(); // Подключение к базе данных
    bool checkCredentials(const QString &username, const QString &password); // Проверка логина и пароля
};

#endif // LOGINWINDOW_H
