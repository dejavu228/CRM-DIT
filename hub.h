#ifndef HUB_H
#define HUB_H

#include <QWidget>
#include <workers.h>

namespace Ui {
class Hub;
}

class Hub : public QWidget
{
    Q_OBJECT

public:
    explicit Hub(QWidget *parent = nullptr);
    ~Hub();


private slots:
    void on_pushButtonWorkers_clicked();

    void on_Exit_clicked();



    void on_SkladButton_clicked();



    void on_CotalogButton_clicked();

private:
    Ui::Hub *ui;
};

#endif // HUB_H
