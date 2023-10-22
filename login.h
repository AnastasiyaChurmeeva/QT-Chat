#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QtNetwork>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT

private:
    QTcpSocket *socketClient;
    Ui::MainWindow *ui;
    //QString nick = " ";
    QString nameLineEdit = " ";

public:
    login(QWidget *parent = nullptr);
    ~login();
    void exec();

private slots:

    void execButtonAction();

    void readSocket();

    //void setNick();
    void confirm();

    signals:
    void loginWindowConfirmed();
};

#endif // LOGIN_H
