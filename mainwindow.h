#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    /**
     * @brief socket of connection
     */
    QTcpSocket *socketClient;
    Ui::MainWindow *ui;
    //QString nick = " ";
    QString nameLineEdit = " ";
    login* loginWindow;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //static MainWindow* setNick();
    static MainWindow* confirm();

private slots:

    void execButtonAction();

    void readSocket();

    void on_sig_in_triggered();

    void openLoginWindow();
};

class loginWindow : public login
{

};

#endif // MAINWINDOW_H
