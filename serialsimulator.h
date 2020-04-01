#ifndef SERIALSIMULATOR_H
#define SERIALSIMULATOR_H

#include <QObject>
#include <QIODevice>
#include <QTimer>
#include <QElapsedTimer>


class SerialSimulator : public QObject
{
    Q_OBJECT

private:

    QTimer timer;
    QElapsedTimer elapsedTimer;

    QByteArray buffer;
    quint32 temp;
    quint32 tilt;
    quint32 alert;

    QByteArray fetchBuffer(int index);

public:
    explicit SerialSimulator(QObject *parent = nullptr);

    QByteArray readAll();
    bool open(QIODevice::OpenMode);
    void close();

signals:
    void readyRead();

public slots:

private slots:
    void timerTimeout();
};

#endif // SERIALSIMULATOR_H
