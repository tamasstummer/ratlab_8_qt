#ifndef SERIALCONNECTOR_H
#define SERIALCONNECTOR_H

#include <QObject>
#include <QVariant>
#include "serialsimulator.h"

class SerialConnector : public QObject
{
    Q_OBJECT
public:
    explicit SerialConnector(QObject *parent = nullptr);
    SerialSimulator *serialsimulator;
    QByteArray *buffer;
    bool connectSerial();
    bool disconnectSerial();

private:
    void getMessage();
    void decodeMessage(QString);

signals:
    void tempChanged(QVariant);
    void tiltChanged(QVariant);
    void alarmChanged(QVariant);

private slots:
    void serial_data_available_from_simulator();

};

#endif // SERIALCONNECTOR_H
