#ifndef MBCLIENT_H
#define MBCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <map>
#include <string>
#include <iostream>
#include <QString>
#include <QTcpSocket>
#include <QImage>

struct pic_struct {
    QString name;
    QString date;
    QString time;
    int  size;
};

class MBClient : public QObject
{
    Q_OBJECT
public:
    explicit MBClient(QObject *parent = 0);

    bool state();
    void getPicture(const QString& name);


signals:
    void newPicture(const QImage& img);
    void newPhoto(const QString& pic);
    void newPhoto2(const pic_struct& ps);
public slots:
    void readPendingDatagrams();
    void readyTcpMesg();
    void readTcpMessage();

private:
    QUdpSocket* udpSocket;
    QTcpSocket *tcpSocket;
    bool isTcpReady;
    QString pic_name;
    char * pic_data;
    int pic_pos;
    int pic_size;
    QImage pic_img;

    std::map<QString, pic_struct> m_piclist;
};

#endif // MBCLIENT_H
