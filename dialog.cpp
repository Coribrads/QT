#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QtSerialPort>
#include "qserialportinfo.h"
#include <QDebug>
#include <QtWidgets>
#include <Windows.h>


int check = 0;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
//Checking for a specific arduino.
    arduino_is_available = false;
    arduino_port_name = "";
    arduino = new QSerialPort;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            //if(serialPortInfo.venderIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id){

                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;

                }
           // }
        }
    }
//Initializing Sequence
    if(arduino_is_available){
        // open and configure the port
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::WriteOnly);
        arduino->setBaudRate(QSerialPort::Baud9600); // make sure the baudrate is set in arduino sketch to 9600
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

    }
    else{
        // give error message if not available
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino");
    }

}
// This is the destructor function when the program ends. It closes the arduino and the gui.
Dialog::~Dialog()
{
    if(arduino->isOpen()){
        arduino->close();
    }
    delete ui;
}
// This function starts the program when the Start button is pressed
void Dialog::on_Start_button_pressed()
{

    //int i = 0;
    //int result;
  Dialog::updateArduino("t");
  //To rotate the stage automatically 36 times on second intervals
  // this code works except it will not stop until i reaches 36. There needs a command inside to break the while loop.
 /* check = 1;
  while(check != 0){
   if(i < 36){
     result = system("C:\\..."); // execute the program
     Sleep(1000); // sleep for 1000 miliseconds or 1 second
     i++;
    }
  }*/

}

// This function stops the program when the Stop button is pressed
void Dialog::on_Stop_button_pressed()
{

  Dialog::updateArduino("f");
 // check = 0;
}
// This function updates the arduino on whether or not the Start or Stop button was pressed
void Dialog::updateArduino(QString command){

    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());

    }
    else{
        qDebug() << "Couldn't write to serial port";
    }


}
// This function will rotate the stage by a system call whenever the "Rotate Stage" button is pressed.
// *make sure to change the path to your specific stage_0.exe
void Dialog::on_Rotate_stage_pressed()
{

    int result;

    result = system("C:\\....."); // This is not the best way to implement opening an executable; Not as secure as other code but fast for checking


}

/*int Dialog::checkforstop(){
    return check;

}*/
