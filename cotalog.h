#ifndef COTALOG_H
#define COTALOG_H

#include <QMainWindow>

namespace Ui {
class Cotalog;
}

class Cotalog : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cotalog(QWidget *parent = nullptr);
    ~Cotalog();

private:
    Ui::Cotalog *ui;
};

#endif // COTALOG_H
