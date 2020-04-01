#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serialconnector.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    // példányosítjuk az osztályt, majd elinditjuk a kommunikációt
   SerialConnector  *mySerialConnector = new SerialConnector();
   bool return_data = mySerialConnector->connectSerial();
   if(return_data == false)
   {
    qDebug() << "Connect to the serialport was not successful" << endl;
   }

    QObject *tempMeter = engine.rootObjects().first()->findChild<QObject*>("TempMeter");
    QObject *tiltMeter = engine.rootObjects().first()->findChild<QObject*>("TiltMeter");

    QObject::connect(mySerialConnector, SIGNAL(tempChanged(QVariant)), tempMeter, SLOT(valueChanged(QVariant)));
    QObject::connect(mySerialConnector, SIGNAL(tiltChanged(QVariant)), tiltMeter, SLOT(valueChanged(QVariant)));

    QObject::connect(mySerialConnector, SIGNAL(alarmChanged(QVariant)), tempMeter, SLOT(alarmStateChanged(QVariant)));
    QObject::connect(mySerialConnector, SIGNAL(alarmChanged(QVariant)), tiltMeter, SLOT(alarmStateChanged(QVariant)));



    return app.exec();
}
