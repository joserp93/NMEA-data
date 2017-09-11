#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Llenamos BaudRate
    ui->comboBox->addItem("1200");
    ui->comboBox->addItem("2400");
    ui->comboBox->addItem("4800");
    ui->comboBox->addItem("9600");
    ui->comboBox->addItem("19200");
    ui->comboBox->addItem("38400");
    ui->comboBox->addItem("57600");
    ui->comboBox->addItem("115200");

    //Llenamos StopBits
    ui->comboBox_2->addItem("OneStop");
    ui->comboBox_2->addItem("OneAndHalfStop");
    ui->comboBox_2->addItem("TwoStop");

    //Llenamos DataBits
    ui->comboBox_3->addItem("Data5");
    ui->comboBox_3->addItem("Data6");
    ui->comboBox_3->addItem("Data7");
    ui->comboBox_3->addItem("Data8");

    //Llenamos Paridad
    ui->comboBox_4->addItem("NoParity");
    ui->comboBox_4->addItem("EvenParity");
    ui->comboBox_4->addItem("OddParity");
    ui->comboBox_4->addItem("SpaceParity");
    ui->comboBox_4->addItem("MarkParity");

    //Llenamos los tipos de tramas
    ui->comboBox_6->addItem("GPVTG");
    ui->comboBox_6->addItem("GPRMC");
    ui->comboBox_6->addItem("GPGLL");
    ui->comboBox_6->addItem("GPAPB");
    ui->comboBox_6->addItem("GPZDA");
    ui->comboBox_6->addItem("GPRMB");

     //Llenamos los puertos encontrados.
    if(QSerialPortInfo::availablePorts().count()>0)
        {
                foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
                {
                     ui->comboBox_5->addItem(serialPortInfo.portName());

                 }
        }

    QFile file_for_writing("temp.txt");
          file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
            QTextStream text_stream_for_writing(&file_for_writing);

            text_stream_for_writing << "";

            file_for_writing.close();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    ui->plainTextEdit->clear();//limpiamos el plaintext

    QFile file_for_writing("temp.txt");
          file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
            QTextStream text_stream_for_writing(&file_for_writing);

            text_stream_for_writing << "";

            file_for_writing.close();

}

void MainWindow::on_pushButton_2_clicked()
{
     K=0;//Para para salir de recibir datos

}

void MainWindow::on_pushButton_3_clicked()
{
         K=1; // esta funcion permite empezar a recibir las tramas del gps
         tempBufferaux = QByteArray();
         _auxBytesRecibidos=0;
}

void MainWindow::on_pushButton_4_clicked()
{

    QString File = QFileDialog::getSaveFileName(this,"Guardar Tramas","tramas.txt","Text files (*.txt)");

    if(!File.isEmpty()){

        QFile file_for_reading("temp.txt");
           file_for_reading.open(QIODevice::ReadOnly);
           QTextStream text_stream_for_reading(&file_for_reading);
      QString Resp = text_stream_for_reading.readAll();
           file_for_reading.close();



    QFile file_for_writing(File);
          file_for_writing.open(QIODevice::WriteOnly | QIODevice::Truncate); //
            QTextStream text_stream_for_writing(&file_for_writing);

            text_stream_for_writing << Resp;

            file_for_writing.close();
        }

}

void MainWindow::on_pushButton_5_clicked()
{
            ui->pushButton_5->setEnabled(false); //inabilitamos en boton de abrir puerto

            QString Baud1 = ui->comboBox->currentText();
            int Baud = Baud1.toInt(); //pasamos los baudios a de string a int

            port.setBaudRate(Baud,QSerialPort::AllDirections); //seteamos los baudios

            //se setear los StopBits de acuerdo al seleccionado

           if(ui->comboBox_2->currentIndex()==0)
            port.setStopBits(QSerialPort::OneStop);
           if(ui->comboBox_2->currentIndex()==1)
            port.setStopBits(QSerialPort::OneAndHalfStop);
           if(ui->comboBox_2->currentIndex()==2)
            port.setStopBits(QSerialPort::TwoStop);

           //se setear los DataBits de acuerdo al seleccionado

          if(ui->comboBox_3->currentIndex()==0)
            port.setDataBits(QSerialPort::Data5);
          if(ui->comboBox_3->currentIndex()==1)
            port.setDataBits(QSerialPort::Data6);
          if(ui->comboBox_3->currentIndex()==2)
            port.setDataBits(QSerialPort::Data7);
          if(ui->comboBox_3->currentIndex()==3)
            port.setDataBits(QSerialPort::Data8);

          //se setear los Parity de acuerdo al seleccionado

          if(ui->comboBox_4->currentIndex()==0)
            port.setParity(QSerialPort::NoParity);
          if(ui->comboBox_4->currentIndex()==1)
            port.setParity(QSerialPort::EvenParity);
          if(ui->comboBox_4->currentIndex()==2)
            port.setParity(QSerialPort::OddParity);
          if(ui->comboBox_4->currentIndex()==3)
            port.setParity(QSerialPort::SpaceParity);
          if(ui->comboBox_4->currentIndex()==4)
            port.setParity(QSerialPort::MarkParity);


           port.setFlowControl(QSerialPort::HardwareControl);


                   port.setPortName(ui->comboBox_5->currentText());
                    if(port.open(QIODevice::ReadWrite)){
                                }
                    else{

                    }

    connect(&port, SIGNAL(readyRead()), this, SLOT(readData())); //Habilitamos un SLOT para que vaya a readData cada vez que haya datos por el puerto
    K=0;
}

void MainWindow::on_pushButton_8_clicked()
{
    ui->pushButton_5->setEnabled(true);

       if(port.isOpen()){
       port.close();
      }

}

void MainWindow::readData() //Funcion para Recibir Los datos Cada vez que llega un dato por el puerto Serial
{


    if (!port.isOpen())
                    {
                        return;
                    }



       if(K==1){


                    _BytesRecibidos = port.bytesAvailable();

                    tempBuffer = QByteArray();
                    tempBuffer =  port.readAll();
                    qDebug() <<  tempBuffer;
                    if( tempBuffer[_BytesRecibidos-1]!=0x0A){
                    tempBufferaux.append(tempBuffer);

                    }
                    else{

                    tempBufferaux.append(tempBuffer);

                    sRespGPS = QString::fromUtf8(tempBufferaux);



                    if(ui->checkBox->isChecked()){
                    ui->plainTextEdit->appendPlainText(sRespGPS);

                    tempBufferaux = QByteArray();


                    QFile file_for_writing("temp.txt");
                          file_for_writing.open(QIODevice::WriteOnly | QIODevice::Append); //
                            QTextStream text_stream_for_writing(&file_for_writing);

                            text_stream_for_writing << sRespGPS;

                            file_for_writing.close();

                    }

                    if(ui->checkBox_2->isChecked()){
                        QStringList strList;
                        strList = sRespGPS.split(0x0A);

                        for(int i=0; i<strList.length(); i++){
                             if(strList[i].contains(ui->comboBox_6->currentText())){

                                  ui->plainTextEdit->appendPlainText(strList[i]);
                                    tempBufferaux = QByteArray();

                                    QFile file_for_writing("temp.txt");
                                          file_for_writing.open(QIODevice::WriteOnly | QIODevice::Append); //
                                            QTextStream text_stream_for_writing(&file_for_writing);

                                            text_stream_for_writing << strList[i].append(0x0A);

                                            file_for_writing.close();

                              }
                        }
                    }
                     tempBufferaux = QByteArray();
                     sRespGPS="";
                    }


              }

}

void MainWindow::on_checkBox_2_clicked()
{
    ui->checkBox->setCheckable(false);
    ui->checkBox_2->setCheckable(true);

}

void MainWindow::on_checkBox_clicked()
{
     ui->checkBox_2->setCheckable(false);
    ui->checkBox->setCheckable(true);

}
