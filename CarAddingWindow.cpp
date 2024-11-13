#include "caraddingwindow.h"
#include "ui_caraddingwindow.h"
#include "MainWindow.h"
#include "Functions.h"
#include <QMessageBox>

CarAddingWindow::CarAddingWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CarAddingWindow)
{
    ui->setupUi(this);
    ui->addPushButton->setDisabled(true);
    ui->addPushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 10px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
    ui->warningLabel->setText(QString::fromUtf8("Заполните все поля"));
    connect(ui->engineTypeComboBox, &QComboBox::currentIndexChanged, this, &CarAddingWindow::carAdding);
    connect(ui->backPushButton, &QPushButton::clicked, this, &CarAddingWindow::on_backPushButton_clicked);
    connect(ui->addPushButton, &QPushButton::clicked, this, &CarAddingWindow::onAddPushButtonClicked);
    connect(ui->yearLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->mileageLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->priceLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->brandLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->modelLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->fuelLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    connect(ui->batteryLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::editedAnyLineEdit);
    /*connect(ui->yearLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->mileageLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->priceLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->brandLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->modelLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->fuelLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);
    connect(ui->batteryLineEdit, &QLineEdit::textChanged, this, &CarAddingWindow::checkForInput);*/
    carAdding();
}
CarAddingWindow::~CarAddingWindow()
{
    delete ui;
}
void CarAddingWindow::onAddPushButtonClicked()
{
    ElectricEngineCar electricCar;
    CombustionEngineCar combustionCar;
    HybridEngineCar hybridCar;
    const char* SQL;
    int engineType = ui->engineTypeComboBox->currentIndex() + 1;
    if (engineType == 1)
    {
        Repository<ElectricEngineCar> rep1;
        QString temp = ui->yearLineEdit->text();
        electricCar.setYear(temp.toInt());
        temp = ui->mileageLineEdit->text();
        electricCar.setMileage(temp.toInt());
        temp = ui->priceLineEdit->text();
        electricCar.setPrice(temp.toFloat());
        temp = ui->brandLineEdit->text();
        electricCar.setBrand(temp.toStdString());
        temp = ui->modelLineEdit->text();
        electricCar.setModel(temp.toStdString());
        temp = ui->batteryLineEdit->text();
        float batteryCapacity = temp.toFloat();
        SQL = "INSERT INTO electric_cars (year_of_production, mileage, price, brand, model, battery_capacity)"
            "VALUES (?, ?, ?, ?, ?, ?);";
        try
        {
            rep1.addCar(electricCar, SQL, engineType, 0, batteryCapacity);
        }
        catch (Exception& ex)
        {
            /*QString qstr = QString::fromStdString(ex.getContext() + ": " + ex.what());*/
            QMessageBox::critical(this, "Error", QString::fromStdString(ex.whatAndContext()));
        }
    }
    if (engineType == 2)
    {
        Repository<CombustionEngineCar> rep2;
        QString temp = ui->yearLineEdit->text();
        combustionCar.setYear(temp.toInt());
        temp = ui->mileageLineEdit->text();
        combustionCar.setMileage(temp.toInt());
        temp = ui->priceLineEdit->text();
        combustionCar.setPrice(temp.toFloat());
        temp = ui->brandLineEdit->text();
        combustionCar.setBrand(temp.toStdString());
        temp = ui->modelLineEdit->text();
        combustionCar.setModel(temp.toStdString());
        temp = ui->fuelLineEdit->text();
        float flueTankCapacity = temp.toFloat();
        SQL = "INSERT INTO combustion_cars (year_of_production, mileage, price, brand, model, fuel_tank_capacity)"
            "VALUES (?, ?, ?, ?, ?, ?);";
        try
        {
            rep2.addCar(combustionCar, SQL, engineType, flueTankCapacity);
        }
        catch (Exception& ex)
        {
            QMessageBox::critical(this, "Error", QString::fromStdString(ex.whatAndContext()));
        }
    }
    if (engineType == 3)
    {
        Repository<HybridEngineCar> rep3;
        QString temp = ui->yearLineEdit->text();
        hybridCar.setYear(temp.toInt());
        temp = ui->mileageLineEdit->text();
        hybridCar.setMileage(temp.toInt());
        temp = ui->priceLineEdit->text();
        hybridCar.setPrice(temp.toFloat());
        temp = ui->brandLineEdit->text();
        hybridCar.setBrand(temp.toStdString());
        temp = ui->modelLineEdit->text();
        hybridCar.setModel(temp.toStdString());
        temp = ui->fuelLineEdit->text();
        float fuelTankCapacity = temp.toFloat();
        temp = ui->batteryLineEdit->text();
        float batteryCapacity = temp.toFloat();
        int hybridType = ui->hybridTypeComboBox->currentIndex();
        SQL = "INSERT INTO hybrid_cars (year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type)"
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
        try
        {
            rep3.addCar(hybridCar, SQL, engineType, fuelTankCapacity, batteryCapacity, hybridType);
        }
        catch (Exception& ex)
        {
            QMessageBox::critical(this, "Error", QString::fromStdString(ex.whatAndContext()));
        }
    }
    close();
}
void CarAddingWindow::carAdding() 
{
    ui->fuelLineEdit->setEnabled(true);
    ui->batteryLineEdit->setEnabled(true);
    ui->hybridTypeComboBox->setEnabled(true);
    ui->fuelLineEdit->setStyleSheet("color: rgb(55, 51, 53); border-style: solid; border-width: 0px; background-color: rgb(200, 215, 210); padding: 5px");
    ui->hybridTypeComboBox->setStyleSheet("QComboBox::drop-down { border:none; } QComboBox::down-arrow { image: url(:/rcs/free-icon-down-arrow-2985150.png); wigth: 30px; height:30px; margin-right: 5px; } QComboBox { color: rgb(55, 51, 53); border-style: solid; border-width: 0px; background-color: rgb(200, 215, 210); padding: 5px }");
    ui->batteryLineEdit->setStyleSheet("color: rgb(55, 51, 53); border-style: solid; border-width: 0px; background-color: rgb(200, 215, 210); padding: 5px");
    int engineType = ui->engineTypeComboBox->currentIndex() + 1;
    if (engineType == 1)
    {
        ui->fuelLineEdit->setDisabled(true);
        ui->fuelLineEdit->setStyleSheet("QLineEdit:disabled { background-color: #9AB6AC; border: none; }");
        ui->hybridTypeComboBox->setDisabled(true);
        ui->hybridTypeComboBox->setStyleSheet("QComboBox::drop-down { border:none; } QComboBox::down-arrow { image: url(:/rcs/free-icon-down-arrow-2985150.png); wigth: 30px; height:30px; margin-right: 5px; } QComboBox:disabled { background-color: #9AB6AC; border: none; }");
    }
    if (engineType == 2)
    {
        ui->batteryLineEdit->setDisabled(true);
        ui->batteryLineEdit->setStyleSheet("QLineEdit:disabled { background-color: #9AB6AC; border: none; }");
        ui->hybridTypeComboBox->setDisabled(true);
        ui->hybridTypeComboBox->setStyleSheet("QComboBox::drop-down { border:none; } QComboBox::down-arrow { image: url(:/rcs/free-icon-down-arrow-2985150.png); wigth: 30px; height:30px; margin-right: 5px; }QComboBox:disabled { background-color: #9AB6AC; border: none; }");
    }
}
void CarAddingWindow::on_backPushButton_clicked()
{
    close();
}
void CarAddingWindow::editedAnyLineEdit()
{
    ui->addPushButton->setEnabled(true);
    ui->addPushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 10px; border-style: solid; border-width: 0px; background-color: rgb(215, 67, 57); padding: 5px }");
   /* if (ui->yearLineEdit->text().isEmpty() || ui->mileageLineEdit->text().isEmpty() || ui->priceLineEdit->text().isEmpty() || ui->brandLineEdit->text().isEmpty() || ui->modelLineEdit->text().isEmpty() || (ui->fuelLineEdit->text().isEmpty() && ui->fuelLineEdit->isEnabled()) || (ui->batteryLineEdit->text().isEmpty() && ui->batteryLineEdit->isEnabled()))
    {
        ui->addPushButton->setDisabled(true);
        ui->addPushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 10px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
    }*/
    try
    {
        if (ui->yearLineEdit->text().isEmpty() || ui->mileageLineEdit->text().isEmpty() || ui->priceLineEdit->text().isEmpty() || ui->brandLineEdit->text().isEmpty() || ui->modelLineEdit->text().isEmpty() || (ui->batteryLineEdit->text().isEmpty() && ui->batteryLineEdit->isEnabled()) || (ui->fuelLineEdit->text().isEmpty() && ui->fuelLineEdit->isEnabled()))
        {
            ui->addPushButton->setDisabled(true);
            ui->addPushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 10px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
            throw Exception("Заполните все поля");
        }
        else
            ui->warningLabel->setText("");
        if (!ui->yearLineEdit->text().toInt() || !ui->mileageLineEdit->text().toInt() || !ui->priceLineEdit->text().toFloat() || (!ui->batteryLineEdit->text().toFloat() && ui->batteryLineEdit->isEnabled()) || (!ui->fuelLineEdit->text().toFloat() && ui->fuelLineEdit->isEnabled()))
        {
            ui->addPushButton->setDisabled(true);
            ui->addPushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 10px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
            throw Exception("Введена строка вместо числа");
        }
        else
            ui->warningLabel->setText("");
    }
    catch (Exception& ex)
    {
        ui->warningLabel->setText(QString::fromUtf8(ex.what()));
    }
}
void CarAddingWindow::closeEvent(QCloseEvent* event)
{
    emit carAddingWindowClosed();
    QDialog::closeEvent(event);
}
//void CarAddingWindow::checkForInput()
//{
//    try
//    {
//        if (ui->yearLineEdit->text().isEmpty() || ui->mileageLineEdit->text().isEmpty() || ui->priceLineEdit->text().isEmpty() || ui->brandLineEdit->text().isEmpty() || ui->modelLineEdit->text().isEmpty() || (ui->batteryLineEdit->text().isEmpty() && ui->batteryLineEdit->isEnabled()) || (ui->fuelLineEdit->text().isEmpty() && ui->fuelLineEdit->isEnabled()))
//            throw Exception("Заполните все поля");
//        else
//            ui->warningLabel->setText("");
//        if (!ui->yearLineEdit->text().toInt() || !ui->mileageLineEdit->text().toInt() || !ui->priceLineEdit->text().toFloat() || (!ui->batteryLineEdit->text().toFloat() && ui->batteryLineEdit->isEnabled()) || (!ui->fuelLineEdit->text().toFloat() && ui->fuelLineEdit->isEnabled()))
//            throw Exception("Введена строка вместо числа");
//        else
//            ui->warningLabel->setText("");
//    }
//    catch (Exception& ex)
//    {
//        ui->warningLabel->setText(QString::fromLocal8Bit(ex.what()));
//    }
//}