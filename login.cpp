#include "mainwindow.h"
#include "login.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>

login::login(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}
void exec()
{
    //void setNick();
    void confirm();
}

void on_confirmButton_clicked()
{
    void loginWindowConfirmed();
}
