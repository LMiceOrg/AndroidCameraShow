#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QDebug>

#ifdef Q_OS_ANDROID
//#include <QAndroidJniObject>
//#include <QtAndroid>
#endif

#include <QTimer>
#include "myudp.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    if (QCoreApplication::arguments().count() > 1){
        /**
         * When service start, create a 5sec timer to broadcast photo status
         */
        qDebug() << "I am the service";
        QTimer *tm = new QTimer();
        MyUdp *client = new MyUdp();
        tm->start(5000);
        QObject::connect(tm, SIGNAL(timeout()), client, SLOT(onsend()) );
    }
    else{
        /**
         * Here is the application entry point, for now do nothing
         */
        qDebug() << "I am the application";
//        QQmlApplicationEngine engine;
//        engine.addImportPath(QStringLiteral("qrc:/"));
//        engine.load(QUrl(QStringLiteral("qrc:/source/qml/main.qml")));
        return 0;
    }
    return app.exec();
}
