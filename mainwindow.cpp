#include "login.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginWindow = new login(this);
    //connect(loginWindow, &login::loginWindowConfirmed, this, &MainWindow::setNick);
    connect(loginWindow, &login::loginWindowConfirmed, this, &MainWindow::confirm);
    connect(ui->sig_in, &QAction::triggered, this, &MainWindow::openLoginWindow);
    socketClient = new QTcpSocket(this);
    socketClient->connectToHost("localhost", 1337, QTcpSocket::ReadWrite);
    if(socketClient->waitForConnected(30000)) {
        qInfo() << "Подключение успешно";
        qInfo() << socketClient->peerAddress();
    } else
    {
         QMessageBox::information(NULL,QObject::tr("Нет подключения к серверу"));
    }

    connect(socketClient, &QTcpSocket::readyRead,
            this, &MainWindow::readSocket);
    connect(ui->sendMessage, &QPushButton::clicked,
            this, &MainWindow::execButtonAction);
    connect(ui->confirm, &QPushButton::clicked,
            //this, &MainWindow::setNick);
            this, &MainWindow::confirm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openLoginWindow()
{
    loginWindow->show();
}

void MainWindow::execButtonAction()
{
    //if(ui->nameLineEdit->text().toUtf8() == "" || nick == " ") {
    if(ui->nameLineEdit->text().toUtf8() == "" || nameLineEdit == " ") {
        QMessageBox::information(NULL,QObject::tr("Ошибка"),tr("Введите имя"));
        return;
    } else if (ui->messageLineEdit->text().toUtf8() == "") {
        QMessageBox::information(NULL,QObject::tr("Ошибка"),tr("Введите сообщение"));
        return;
    } else {
        QString nickName = loginWindow->ui->nameLineEdit->text();
        if (nickName.isEmpty()) {
            nickName = ui->nameLineEdit->text();
        }
        socketClient->write(nickName.toUtf8() + " " + ui->messageLineEdit->text().toUtf8());
        ui->messageLineEdit->clear();
    }
}

void MainWindow::readSocket()
{
    QString data = QString(socketClient->readAll());
    ui->commonChatBrowser->append(data);
}

//void login::setNick()
void login::confirm()
{
    //nick = ui->nameLineEdit->displayText();
    nameLineEdit = ui->nameLineEdit->displayText();
    ui->nameLineEdit->setReadOnly("True");
}

void MainWindow::on_sig_in_triggered()
{
    loginWindow->show();
}
