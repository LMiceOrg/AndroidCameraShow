#include "mbclient.h"

MBClient::MBClient(QObject *parent) : QObject(parent)
{
    pic_data = new char[10*1024*1024];
    pic_pos = 0;
    pic_size = 0;

    udpSocket = new QUdpSocket(this);
    bool b= udpSocket->bind(QHostAddress::AnyIPv4, 8809);

    QObject::connect(udpSocket, SIGNAL(readyRead()),
                     this, SLOT(readPendingDatagrams()));


    std::cout<<"inited="<<b<<"\n";

    tcpSocket = new QTcpSocket(this);
    tcpSocket->abort();
    isTcpReady = false;
}

bool MBClient::state()
{
    return tcpSocket->state() == QTcpSocket::ConnectedState;
}

void MBClient::getPicture(const QString &name)
{
    if(state()) {
        auto iter = m_piclist.find(name);
        if(iter != m_piclist.end()) {
            const pic_struct& ps = iter->second;
            pic_name = ps.name;
            pic_size = ps.size;
            pic_pos = 0;
            qint64 i = tcpSocket->write(name.toStdString().c_str(), name.size());
            qDebug()<<"send tcp:"<<i;
            return;
        }

    } else {
        //No Tcp connection
    }
}

void MBClient::readPendingDatagrams()
{
    std::cout<<"reading begin\n";
    //while(true) {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        std::cout<<"sender:"<<sender.toString().toStdString().c_str();
        if(tcpSocket->state() != QTcpSocket::ConnectedState) {
            tcpSocket->abort();
            tcpSocket->connectToHost(sender,8809);
            connect(tcpSocket,SIGNAL(connected()),this,SLOT(readyTcpMesg()));
        }
        QStringList pics = QString(datagram).split("\n");
        for(int i=0; i< pics.size(); ++i) {
            QString str = pics.at(i);
            QStringList sl = str.split(" ");
            qDebug()<<":"<<str;

            if(sl.size() < 4)
                return;

            QString pname = sl[2];
            QString sz = sl.at(3);
            sz.replace("size:", "");

            pic_struct ps;
            ps.size = sz.toInt();
            ps.date = sl.at(0);
            ps.time = sl.at(1);
            ps.name = sl.at(2);

            //sscanf(sl.at(3).toStdString().c_str(), "size:%d", pic_size);
            qDebug()<<pname<<ps.size<<"\n";

            if(m_piclist.find(pname) == m_piclist.end()) {
                emit newPhoto2(ps);
                emit newPhoto(pname);
            }
            m_piclist[pname] = ps;


        }//for-i
    }

}

void MBClient::readyTcpMesg()
{
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readTcpMessage()));
}

void MBClient::readTcpMessage()
{
    QByteArray qba= tcpSocket->readAll(); //读取
    //qDebug()<<"tcp:"<<qba.size();
    memcpy(pic_data+pic_pos, qba.data(), qba.size());
    pic_pos += qba.size();
    if(pic_pos >= pic_size) {
//        FILE* fp = fopen(pic_name.toStdString().c_str(), "wb");
//        fwrite(pic_data, 1, pic_pos, fp);
//        fclose(fp);


        pic_img.loadFromData((const uchar*)pic_data, pic_pos);
        emit newPicture(pic_img);
        qDebug()<<"image:"<<pic_img.width()<<pic_img.height();

        pic_pos = 0;
    }
}

