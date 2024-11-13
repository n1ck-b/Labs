#include "carcomparewindow.h"
#include "ui_carcomparewindow.h"
#include "MainWindow.h"
#include "Functions.h"


CarCompareWindow::CarCompareWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CarCompareWindow)
{
    ui->setupUi(this);
    connect(ui->backPushButton, &QPushButton::clicked, this, &CarCompareWindow::onBackPushButtonClicked);
}
CarCompareWindow::~CarCompareWindow()
{
    delete ui;
}
void CarCompareWindow::onBackPushButtonClicked()
{
    close();
}
void CarCompareWindow::compareCars()
{
    if (ui->CarYearLabel1->text().toInt() > ui->CarYearLabel2->text().toInt())
    {
        ui->CarYearLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
        ui->CarYearLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
    }
    if (ui->CarYearLabel1->text().toInt() < ui->CarYearLabel2->text().toInt())
    {
        ui->CarYearLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
        ui->CarYearLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
    }
    if (ui->CarMileageLabel1->text().toInt() < ui->CarMileageLabel2->text().toInt())
    {
        ui->CarMileageLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
        ui->CarMileageLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
    }
    if (ui->CarMileageLabel1->text().toInt() > ui->CarMileageLabel2->text().toInt())
    {
        ui->CarMileageLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
        ui->CarMileageLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
    }
    if (ui->CarPriceLabel1->text().toFloat() < ui->CarPriceLabel2->text().toFloat())
    {
        ui->CarPriceLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
        ui->CarPriceLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
    }
    if (ui->CarPriceLabel1->text().toFloat() > ui->CarPriceLabel2->text().toFloat())
    {
        ui->CarPriceLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
        ui->CarPriceLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
    }
    if (ui->CarBatteryLabel1->text() != "-" && ui->CarBatteryLabel2->text() != "-")
    {
        if (ui->CarBatteryLabel1->text().toFloat() > ui->CarBatteryLabel2->text().toFloat())
        {
            ui->CarBatteryLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
            ui->CarBatteryLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
        }
        if (ui->CarBatteryLabel1->text().toFloat() < ui->CarBatteryLabel2->text().toFloat())
        {
            ui->CarBatteryLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
            ui->CarBatteryLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
        }
    }
    if (ui->CarFuelLabel1->text() != "-" && ui->CarFuelLabel2->text() != "-")
    {
        if (ui->CarFuelLabel1->text().toFloat() > ui->CarFuelLabel2->text().toFloat())
        {
            ui->CarFuelLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
            ui->CarFuelLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
        }
        if (ui->CarFuelLabel1->text().toFloat() < ui->CarFuelLabel2->text().toFloat())
        {
            ui->CarFuelLabel1->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #CE4238;");
            ui->CarFuelLabel2->setStyleSheet("color: rgb(244, 240, 239); border-style: solid; border-width: 0px; padding: 5px; background-color: #79AC80;");
        }
    }
}