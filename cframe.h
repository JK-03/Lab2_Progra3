
#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

    bool esTarjetaValida(const QString& numeroTarjeta);
    void LetraABinario();
    void LetraADecimal();
    void LetraAHexadecimal();
    void BinarioALetra();
    void DecimalALetra();
    void HexadecimalALetra();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::cframe *ui;
};
#endif // CFRAME_H
