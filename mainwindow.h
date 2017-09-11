#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIODevice>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QList>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void readData();

    void on_checkBox_2_clicked();

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort port;
    int K;
    QByteArray tempBufferaux;
    QByteArray tempBuffer;
    QByteArray  CRLF={0x0D,0x0A};
    QString sRespGPS;
    int  _auxBytesRecibidos;
    int  _BytesRecibidos;


};

#endif // MAINWINDOW_H
