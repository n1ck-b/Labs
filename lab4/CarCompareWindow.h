#ifndef CARCOMPAREWINDOW_H
#define CARCOMPAREWINDOW_H

#include <vector>
#include <QDialog>
#include <QString>
#include <QListWidget>
#include <QInputDialog>
#include "ui_carcomparewindow.h"
#include "Functions.h"

namespace Ui {
    class CarCompareWindow;
}

class CarCompareWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CarCompareWindow(QWidget* parent = nullptr);
    ~CarCompareWindow();
    template<typename T>
    void infoAboutFirstCar(T car, float fuelTankCapacity = 0, float batteryCapacity = 0, int hybridType = 0)
    {
        ui->CarYearLabel1->setText(QString::number(car.getYear()));
        ui->CarMileageLabel1->setText(QString::number(car.getMileage()));
        ui->CarPriceLabel1->setText(QString::number(car.getPrice()));
        ui->CarBrandLabel1->setText(QString::fromStdString(car.getBrand()));
        ui->CarModelLabel1->setText(QString::fromStdString(car.getModel()));
        std::string str = typeid(car).name();
        if (str == "class ElectricEngineCar" || str == "class HybridEngineCar")
            ui->CarBatteryLabel1->setText(QString::number(batteryCapacity));
        if (str == "class CombustionEngineCar" || str == "class HybridEngineCar")
            ui->CarFuelLabel1->setText(QString::number(fuelTankCapacity));
        if (str == "class HybridEngineCar")
        {
            if (hybridType == 0)
                ui->CarHybridTypeLabel1->setText(QString::fromLocal8Bit("Последовательный"));
            if (hybridType == 1)
                ui->CarHybridTypeLabel1->setText(QString::fromLocal8Bit("Параллельный"));
        }
    }
    template<typename T>
    void infoAboutSecondCar(T car, float fuelTankCapacity = 0, float batteryCapacity = 0, int hybridType = 0)
    {
        ui->CarYearLabel2->setText(QString::number(car.getYear()));
        ui->CarMileageLabel2->setText(QString::number(car.getMileage()));
        ui->CarPriceLabel2->setText(QString::number(car.getPrice()));
        ui->CarBrandLabel2->setText(QString::fromStdString(car.getBrand()));
        ui->CarModelLabel2->setText(QString::fromStdString(car.getModel()));
        std::string str = typeid(car).name();
        if (str == "class ElectricEngineCar" || str == "class HybridEngineCar")
            ui->CarBatteryLabel2->setText(QString::number(batteryCapacity));
        if (str == "class CombustionEngineCar" || str == "class HybridEngineCar")
            ui->CarFuelLabel2->setText(QString::number(fuelTankCapacity));
        if (str == "class HybridEngineCar")
        {
            if (hybridType == 0)
            {
                ui->CarHybridTypeLabel2->setText(QString::fromLocal8Bit("Последовательный"));
            }
            if (hybridType == 1)
            {
                ui->CarHybridTypeLabel2->setText(QString::fromLocal8Bit("Параллельный"));
            }
        }

    }
private:
    Ui::CarCompareWindow* ui;
private slots:
    void onBackPushButtonClicked();
};

#endif // CARCOMPAREWINDOW_H
