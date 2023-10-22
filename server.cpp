#include "server.h"
#include "ui_server.h"
#include <QDebug>
#include <QMessageBox>
#include <QWidget>

server::server(QWidget *parent) : QMainWindow(parent), ui(new Ui::server)
{
    ui->setupUi(this);

    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection,
            this, &server::connectUser);
    connect(ui->banButton, &QPushButton::clicked,
            this, &server::banUser);

    if (tcpServer->listen(QHostAddress::Any, 1337)) {
        qInfo() << "Сервер запущен";
    } else {
        qWarning() << "Не удается запустить сервер";
    }
    connect(this, &server::serverClose,
            this, &QCoreApplication::quit);
    clients.clear();
    list.clear();
}

server::~server()
{
    delete ui;
}

void server::connectUser()
{
    ui->textBrowser->append("Подключение нового клиента");
    foreach (client, clients) {
            QTcpSocket* clientSock = (QTcpSocket*) client;
            QTextStream str (clientSock);
            str << " подключился";
        }

    client = tcpServer->nextPendingConnection();
    clients.push_back(client);
    this->send10Message();

    connect(client, &QTcpSocket::readyRead,
            this, &server::runClientAction);
    connect(client, &QTcpSocket::disconnected,
            this, &server::disconnectUser);
}

void server::runClientAction()
{
    k++;
    QTcpSocket* clientSocket = (QTcpSocket*) sender();
    QTextStream stream (clientSocket);
    QString nickname;
    QString message;
    for (int i = 0;i < 2;i++){
        if (i == 0)
            stream >> nickname;
        if (i == 1)
            stream >> message;
    }
    QString logMsg = "Сообщение от " + nickname + ": " + message;
    ui->textBrowser->append(logMsg);

    foreach (client, clients){
        QTcpSocket* clSock = (QTcpSocket*) client;
        QTextStream str (clSock);
        str << nickname + ": " + message;
    }

    f.setFileName("messages.txt");
    list.push_back(nickname + " " + message);

    if(!f.open(QIODevice::WriteOnly)){
        qInfo() << "Файл невозможно прочесть";
    }

    if (k > 10){
        list.removeFirst();
    }

    QTextStream _stream(&f);
    foreach(QString str, list){
        if (str != ""){
           _stream << str << endl;
       }
    }
    f.close();
}

void server::disconnectUser() {
    ui->textBrowser->append("Пользователь отключился");

    foreach (client, clients) {
        QTcpSocket* clientSock = (QTcpSocket*) client;
        QTextStream str (clientSock);
        str << "    вышел из чата";
    }
    clients.removeOne(client);
    client->disconnect();
    if(clients.size() == 0){
        qInfo() << "Сервер отключен";
        emit serverClose();
    }
}

void server::send10Message() {
    f.setFileName("messages.txt");
    if(!f.open(QIODevice::ReadOnly)){
    ui->textBrowser->append("Файл невозможно прочесть");
    }

    QTcpSocket* clSock = (QTcpSocket*) client;
    QTextStream str (clSock);
    QTextStream _stream(&f);
    int i = 0;
    while(!_stream.atEnd()){
        QString st;
        i++;
        _stream >> st;
        if (((i % 2) == 1)&&(st != ""))
            str << st + ": ";
        else {
            str << st;
            if(!_stream.atEnd())
                str<<endl;
        }
    }
    if(k == 0)
        k += i/2;
    f.close();
}

void server::banUser()
{
    QString username = ui->lineEdit->text();
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя");
        return;
    }

    QTextStream stream(client);
    stream << "ban:" << username;

    ui->textBrowser->append("Пользователь " + username + " был забанен");

    disconnectUser();
}
