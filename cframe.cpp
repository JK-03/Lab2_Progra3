#include "cframe.h"
#include "ui_cframe.h"
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <string>
#include <sstream>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);

    //Abrir en Menú
    ui->tabWidget->setCurrentIndex(0);

    //Window
    this->setWindowTitle("Laboratorio #2");

    //Restrincción de Line Edit para Tarjeta
    QRegularExpression regExp("^\\d{0,16}$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(regExp, this);
    ui->TE_Tarjeta->setValidator(validator);
    ui->TE_Tarjeta->setMaxLength(16);
}

cframe::~cframe()
{
    delete ui;
}

void cframe::on_pushButton_clicked()
{
    std::string opcion = "";

    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion5 = msgBox.addButton("Salir", QMessageBox::ActionRole);
    QPushButton *opcion4 = msgBox.addButton("Ejercicio 4", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Ejercicio 3", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Ejercicio 2", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion2) {
        ui->tabWidget->setCurrentIndex(1);
    } else if (msgBox.clickedButton() == opcion3) {
        ui->tabWidget->setCurrentIndex(2);
    } else if (msgBox.clickedButton() == opcion4) {
        ui->tabWidget->setCurrentIndex(3);
    } else if (msgBox.clickedButton() == opcion5) {
        this->close();
    }
}

//EJERCICIO 2
void cframe::on_pushButton_2_clicked()
{
    int height = ui->SPB_Piramide->value();

    QString triangulo;
    int width = 2 * height - 1;

    for (int i = 1; i <= height; ++i) {
        int numAsteriscos = 2 * i - 1;

        int numEspacios = (width - numAsteriscos) / 2;

        triangulo += QString(numEspacios, ' ');
        triangulo += QString(numAsteriscos, '*');
        triangulo += '\n';
    }

    ui->TE_Piramide->setText(triangulo);
}


//EJERCICIO 3
bool cframe::esTarjetaValida(const QString& numeroTarjeta) {
    int suma = 0;
    int longitud = numeroTarjeta.size();
    bool duplicar = false;

    for (int i = longitud - 1; i >= 0; --i) {
        char caracter = numeroTarjeta[i].toLatin1();

        int digito = caracter - '0';

        if (duplicar) {
            digito *= 2;
            if (digito > 9) {
                digito -= 9;
            }
        }

        suma += digito;
        duplicar = !duplicar;
    }

    return (suma % 10 == 0);
}

void cframe::on_pushButton_3_clicked() {
    QString numeroTarjeta = ui->TE_Tarjeta->text();

    if (numeroTarjeta.isEmpty() || numeroTarjeta.size() != 16) {
        ui->LE_Tarjeta->setText("Ingrese un número de tarjeta de 16 dígitos.");
        return;
    }

    bool valida = esTarjetaValida(numeroTarjeta);

    if (valida) {
        ui->LE_Tarjeta->setText("La tarjeta de crédito es válida.");
    } else {
        ui->LE_Tarjeta->setText("La tarjeta de crédito es inválida.");
    }
}

//EJERCICIO 4
void cframe::on_pushButton_4_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Por favor, seleccione una opción:");

    QPushButton *opcion7 = msgBox.addButton("Hexadecimal a Letra", QMessageBox::ActionRole);
    QPushButton *opcion6 = msgBox.addButton("Decimal a Letra", QMessageBox::ActionRole);
    QPushButton *opcion5 = msgBox.addButton("Binario a Letra", QMessageBox::ActionRole);
    QPushButton *opcion4 = msgBox.addButton("Letra a Hexadecimal", QMessageBox::ActionRole);
    QPushButton *opcion3 = msgBox.addButton("Letra a Decimal", QMessageBox::ActionRole);
    QPushButton *opcion2 = msgBox.addButton("Letra a Binario", QMessageBox::ActionRole);

    msgBox.exec();

    if (msgBox.clickedButton() == opcion2) {
        LetraABinario();
    } else if (msgBox.clickedButton() == opcion3) {
        LetraADecimal();
    } else if (msgBox.clickedButton() == opcion4) {
        LetraAHexadecimal();
    } else if (msgBox.clickedButton() == opcion5) {
        BinarioALetra();
    } else if (msgBox.clickedButton() == opcion6) {
        DecimalALetra();
    } else if (msgBox.clickedButton() == opcion7) {
        HexadecimalALetra();
    }
}

//Funcines para Conversiones de Ejercicio 4
void cframe::LetraABinario()
{
    QString input = ui->TE_Conversiones->text();
    if (input.isEmpty() || input.length() != 1) {
        ui->LE_Conversiones->setText("Por favor, ingrese una sola letra.");
        return;
    }

    char letra = input.toStdString()[0];
    int decimal = static_cast<int>(letra);

    std::string binario;
    for (int i = 7; i >= 0; --i) {
        binario += (decimal & (1 << i)) ? '1' : '0';
    }

    ui->LE_Conversiones->setText(QString("Binario: %1").arg(QString::fromStdString(binario)));
}

void cframe::LetraADecimal()
{
    QString input = ui->TE_Conversiones->text();
    if (input.isEmpty() || input.length() != 1) {
        ui->LE_Conversiones->setText("Por favor, ingrese una sola letra.");
        return;
    }

    char letra = input.toStdString()[0];
    int decimal = static_cast<int>(letra);
    ui->LE_Conversiones->setText(QString("Decimal: %1").arg(decimal));
}

void cframe::LetraAHexadecimal()
{
    QString input = ui->TE_Conversiones->text();
    if (input.isEmpty() || input.length() != 1) {
        ui->LE_Conversiones->setText("Por favor, ingrese una sola letra.");
        return;
    }

    char letra = input.toStdString()[0];
    int decimal = static_cast<int>(letra);
    std::stringstream ss;
    ss << std::hex << std::uppercase << decimal;
    ui->LE_Conversiones->setText(QString("Hexadecimal: %1").arg(QString::fromStdString(ss.str())));
}

void cframe::BinarioALetra()
{
    QString input = ui->TE_Conversiones->text();
    if (input.isEmpty() || input.length() != 8) {
        ui->LE_Conversiones->setText("Por favor, ingrese un número binario de 8 bits.");
        return;
    }

    std::string binario = input.toStdString();
    int decimal = 0;

    for (char bit : binario) {
        decimal = (decimal << 1) | (bit == '1' ? 1 : 0);
    }

    char letra = static_cast<char>(decimal);
    ui->LE_Conversiones->setText(QString("Letra: %1").arg(QString(letra)));
}

void cframe::DecimalALetra()
{
    QString input = ui->TE_Conversiones->text();
    bool ok;
    int decimal = input.toInt(&ok);

    if (!ok || decimal < 0 || decimal > 255) {
        ui->LE_Conversiones->setText("Número decimal no válido. Ingrese un valor entre 0 y 255.");
    } else {
        char letra = static_cast<char>(decimal);
        ui->LE_Conversiones->setText(QString("Letra: %1").arg(QString(letra)));
    }
}

void cframe::HexadecimalALetra()
{
    QString input = ui->TE_Conversiones->text();
    bool ok;
    int decimal = input.toInt(&ok, 16);

    if (!ok || decimal < 0 || decimal > 255) {
        ui->LE_Conversiones->setText("Número hexadecimal no válido. Ingrese un valor correcto.");
    } else {
        char letra = static_cast<char>(decimal);
        ui->LE_Conversiones->setText(QString("Letra: %1").arg(QString(letra)));
    }
}
