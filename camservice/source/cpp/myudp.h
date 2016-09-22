#ifndef MYUDP_H
#define MYUDP_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

#include <QTcpSocket>
#include <QTcpServer>

#include <vector>
#include <map>
#include <QString>

class MyUdp : public QObject
{
    Q_OBJECT
public:
    MyUdp(QObject* parent = 0);
    ~MyUdp();

public slots:
    void onsend();
    void send(const QString& data);
    void newTcpConnect();
    void readTcpMessage();
private:
    QUdpSocket *udpSocket;
    //created --> name
    std::map<QString, QString> m_history;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    std::vector<QTcpSocket*> tcpLists;


};
#endif // MYUDP_H
