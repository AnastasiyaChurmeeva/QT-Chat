#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class server; }
QT_END_NAMESPACE

class server : public QMainWindow
{
    Q_OBJECT

private:
    
    QTcpServer* tcpServer;
    
    QTcpSocket* client;
    
    QList <QTcpSocket*> clients;
    QFile f;
    QStringList list;
    int k = 0;

public:
    server(QWidget *parent = nullptr);
    ~server();

private slots:
    Ui::server *ui;

    void connectUser();
    
    void runClientAction();
    
    void disconnectUser();
    
    void send10Message();

    void banUser();

signals:
    
    void serverClose();
};
#endif // SERVER_H
