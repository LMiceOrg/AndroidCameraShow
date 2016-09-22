#include "myudp.h"
#include <QFileInfo>
#include <QDir>
#include <QDateTime>
#include <QThread>

struct cam_s {
    int pos;
    int count;
    int size;
    int totalsize;
    char name[32];
    char data[8];
};

struct tcpheader_s {
    char time[16];
    char name[16];
    int size;
    int pos;
};

MyUdp::MyUdp(QObject* parent):QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    tcpSocket = NULL;
    tcpServer = new QTcpServer(this);
    //监听任何连上8809端口的ip
    tcpServer->listen(QHostAddress::Any,8809);
    //新连接信号触发，调用newConnect()槽函数
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(newTcpConnect()));
}

MyUdp::~MyUdp()
{

}

void MyUdp::onsend()
{
    const int max_count = 10;
    QDir dir("/storage/sdcard0/DCIM/Camera");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    QFileInfoList list = dir.entryInfoList();

    QString ba;
    for (int i = 0; i < list.size(); ++i) {
        //Top 10
        if(i>=max_count)
            break;

        QFileInfo fileInfo = list.at(i);
//        QString created = fileInfo.created().toString("yyyy-M-d hh:mm:ss");
//        if(m_history.find(created) != m_history.end()) {
//            continue;
//        }
//        m_history[created] = fileInfo.absoluteFilePath();

        int state = 0;
        if(tcpSocket)
            state = tcpSocket->state();

        QString data = QString("%1 %2 size:%3 tcp:%4\n").arg(fileInfo.created().toString("yyyy-M-d hh:mm:ss"))
                .arg(fileInfo.fileName())
                .arg(fileInfo.size())
                .arg(state);

        ba.append(data);

    }

    if(ba.size()> 0 )
        send(ba);

}

void MyUdp::send(const QString &data)
{
    //UDP 广播
    QHostAddress server_addr = QHostAddress::Broadcast;
    quint16 server_port = 8809;
    QByteArray ba;
    ba.append(data);
    udpSocket->writeDatagram(ba,server_addr, server_port);
}

void MyUdp::newTcpConnect()
{
    //得到每个连进来的socket
    tcpSocket = tcpServer->nextPendingConnection();
    //有可读的信息，触发读函数槽
    QObject::connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readTcpMessage()));
    //插入列表
    //tcpLists.push_back(tcpSocket);
}

void MyUdp::readTcpMessage()
{
    //读取 请求文件名
    QByteArray qba= tcpSocket->readAll();
    QString name = QString::fromStdString(qba.toStdString());



    //QString s=QString("sending_file:%1").arg(name);
    //send(s);

    QDir dir("/storage/sdcard0/DCIM/Camera");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().compare(name) != 0)
            continue;

        QString data = QString("%1 %2 size:%3 tcp:%4").arg(fileInfo.created().toString("yyyy-M-d hh:mm:ss"))
                .arg(fileInfo.fileName())
                .arg(fileInfo.size())
                .arg(3);
        send(data);

        QByteArray ba;
        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        ba = file.readAll();
        file.close();
        tcpSocket->write(ba);
        break;
    }

}
