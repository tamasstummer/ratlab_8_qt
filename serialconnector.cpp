#include "serialconnector.h"
#include <QDebug>


SerialConnector::SerialConnector(QObject *parent) : QObject(parent)
{
    this->serialsimulator = new SerialSimulator();
    this->buffer = new QByteArray();
    QObject::connect(this->serialsimulator, SIGNAL(readyRead()), this, SLOT(serial_data_available_from_simulator()));

}

bool SerialConnector::connectSerial()
{
    this->buffer->clear();
    bool wasSuccessful = this->serialsimulator->open(QIODevice::ReadOnly);
    return wasSuccessful;
}

bool SerialConnector::disconnectSerial()
{
    this->serialsimulator->close();
    return true;
}

void SerialConnector::serial_data_available_from_simulator()
{
    QByteArray getted_serial_data = this->serialsimulator->readAll();
    this->buffer->append(getted_serial_data);
    //qDebug() <<getted_serial_data;
    this->getMessage();

}

void SerialConnector::getMessage()
{
    QString local_buffer = QString::fromStdString(this->buffer->toStdString());  // konvertáljuk és másoljuk a buffert
    QStringList pieces = local_buffer.split("\n\r");    //elválasztjuk a \n\r mentén
    QString needed_word = pieces.value(0);  // elmentjük az első apott parancsot
    int stringLength = needed_word.length();
    this->buffer->remove(0,stringLength + 2);  // töröljük a bufferből az kivett adatot (+ a \n\r -t is)
    this->decodeMessage(needed_word);
}

void SerialConnector::decodeMessage(QString getted_string)
{
    QStringList pieces = getted_string.split(":");
    QVariant number_value;
    if(pieces.length() == 2)
    {
        number_value = pieces.value(1);
        if(pieces.value(0).compare("#Temp") == 0) {emit tempChanged(number_value); qDebug() << "temp" << number_value << endl;}
        if(pieces.value(0).compare("#Tilt") == 0) {emit tiltChanged(number_value);qDebug() << "timt" << number_value << endl;}
        if(pieces.value(0).compare("#Alert") == 0){emit alarmChanged(number_value);qDebug() << "Alert" << number_value << endl;}
    }


}
