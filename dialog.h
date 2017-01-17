#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_Start_button_pressed();

    void on_Stop_button_pressed();

    void on_Rotate_stage_pressed();

    void updateArduino(QString);

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
   // int check;
   // int checkforstop();
    static const quint16 arduino_uno_vendor_id = 6790; //change this for SPIM arduino
    static const quint16 arduino_uno_product_id = 29987; //change this for SPIM arduino
    QString  arduino_port_name;
    bool arduino_is_available;

};

#endif // DIALOG_H
