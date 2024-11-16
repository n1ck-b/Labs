#include "searchforcarswindow.h"
#include "ui_searchforcarswindow.h"
#include "Functions.h"

SearchForCarsWindow::SearchForCarsWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SearchForCarsWindow)
{
    ui->setupUi(this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(ui->batteryCheckBox);
    buttonGroup->addButton(ui->fuelCheckBox);
    connect(ui->searchPushButton, &QPushButton::clicked, this, &SearchForCarsWindow::onSearchPushButtonClicked);
    connect(ui->hybridTypeCheckBox, &QCheckBox::checkStateChanged, this, &SearchForCarsWindow::onCheckBoxEdited);
    connect(ui->backPushButton, &QPushButton::clicked, this, &SearchForCarsWindow::onBackPushButtonClicked);
    connect(ui->savePushButton, &QPushButton::clicked, this, &SearchForCarsWindow::onSavePushButtonClicked);
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(QColor(215, 67, 57));
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setBlurRadius(10);
    ui->searchPushButton->setGraphicsEffect(shadowEffect);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    ui->savePushButton->setDisabled(true);
    ui->savePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
}
SearchForCarsWindow::~SearchForCarsWindow()
{
    delete ui;
}
void SearchForCarsWindow::onSearchPushButtonClicked()
{
    ui->infoAboutFileLabel->setText("");
    ui->savePushButton->setDisabled(true);
    ui->savePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
    ui->listWidget->clear();
    std::string sql = "";
    std::string tableName = " ";
    bool isFirst = true;
    QString qstr;
    int engineType = 0;
    try
    {
        if (ui->brandCheckBox->isChecked())
        {
            isFirst = false;
            sql += " brand = '";
            qstr = ui->brandLineEdit->text();
            sql = sql + qstr.toStdString() + "'";
        }
        if (ui->modelCheckBox->isChecked())
        {
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            qstr = ui->modelLineEdit->text();
            sql += " model = '" + qstr.toStdString() + "'";
        }
        if (ui->yearCheckBox->isChecked())
        {
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            if (!ui->yearLineEditFrom->text().toInt())
                throw Exception("Введена строка вместо числа в поле \"Год выпуска\"");
            qstr = ui->yearLineEditFrom->text();
            sql += " (year_of_production >= " + qstr.toStdString();
            if (!ui->yearLineEditTo->text().toInt())
                throw Exception("Введена строка вместо числа в поле \"Год выпуска\"");
            qstr = ui->yearLineEditTo->text();
            sql += " AND year_of_production <= " + qstr.toStdString() + " )";
        }
        if (ui->mileageCheckBox->isChecked())
        {
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            if (!ui->mileageLineEditFrom->text().toInt())
                throw Exception("Введена строка вместо числа в поле \"Пробег\"");
            qstr = ui->mileageLineEditFrom->text();
            sql += " (mileage >= " + qstr.toStdString();
            if (!ui->mileageLineEditTo->text().toInt())
                throw Exception("Введена строка вместо числа в поле \"Пробег\"");
            qstr = ui->mileageLineEditTo->text();
            sql += " AND mileage <= " + qstr.toStdString() + " )";
        }
        if (ui->priceCheckBox->isChecked())
        {
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            if (!ui->priceLineEditFrom->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Стоимость\"");
            qstr = ui->priceLineEditFrom->text();
            sql += " (price >= " + qstr.toStdString();
            if (!ui->priceLineEditTo->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Стоимость\"");
            qstr = ui->priceLineEditTo->text();
            sql += " AND price <= " + qstr.toStdString() + " )";
        }
        if (ui->fuelCheckBox->isChecked())
        {
            if (!ui->hybridTypeCheckBox->isChecked())
            {
                tableName = "combustion_cars";
                engineType = 2;
            }
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            if (!ui->fuelLineEditFrom->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Объем топливного бака\"");
            qstr = ui->fuelLineEditFrom->text();
            sql += " (fuel_tank_capacity >= " + qstr.toStdString();
            if (!ui->fuelLineEditTo->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Объем топливного бака\"");
            qstr = ui->fuelLineEditTo->text();
            sql += " AND fuel_tank_capacity <= " + qstr.toStdString() + " )";
        }
        if (ui->batteryCheckBox->isChecked())
        {
            if (!ui->hybridTypeCheckBox->isChecked())
            {
                tableName = "electric_cars";
                engineType = 1;
            }
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            if (!ui->batteryLineEditFrom->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Емкость аккумулятора\"");
            qstr = ui->batteryLineEditFrom->text();
            sql += " (battery_capacity >= " + qstr.toStdString();
            if (!ui->batteryLineEditTo->text().toFloat())
                throw Exception("Введена строка вместо числа в поле \"Емкость аккумулятора\"");
            qstr = ui->batteryLineEditTo->text();
            sql += " AND battery_capacity <= " + qstr.toStdString() + " )";
        }
        if (ui->hybridTypeCheckBox->isChecked())
        {
            tableName = "hybrid_cars";
            engineType = 3;
            if (!isFirst)
            {
                sql += " AND";
            }
            else
                isFirst = false;
            int hybridType = ui->hybridTypeComboBox->currentIndex() + 1;
            sql += " hybrid_type = " + std::to_string(hybridType) + " ";
        }
        sql += ";";
        std::string SQL = "SELECT * FROM ";
        Repository<ElectricEngineCar> rep;
        int count = 1;
        if (tableName != " ")
        {
            SQL += tableName + " WHERE" + sql;
            rep.searchForCarInDB(SQL.c_str(), engineType, count, ui->listWidget, jsonArray);
            ui->listWidget->repaint();
        }
        else
        {
            SQL += "combustion_cars WHERE" + sql;
            rep.searchForCarInDB(SQL.c_str(), 2, count, ui->listWidget, jsonArray);
            SQL = "SELECT * FROM electric_cars WHERE" + sql;
            rep.searchForCarInDB(SQL.c_str(), 1, count, ui->listWidget, jsonArray);
            SQL = "SELECT * FROM hybrid_cars WHERE" + sql;
            rep.searchForCarInDB(SQL.c_str(), 3, count, ui->listWidget, jsonArray);
            ui->listWidget->repaint();
        }
        if (ui->listWidget->count() != 0)
        {
            ui->savePushButton->setEnabled(true);
            ui->savePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: rgb(215, 67, 57); padding: 5px }");
        }
    }
    catch (Exception& ex)
    {
        ui->warningLabel->setText(ex.what());
    }
}
void SearchForCarsWindow::onCheckBoxEdited() //когда не выбран checkbox для гибрида, то нельзя снять выбор с обоих checkbox для топлива и батареи
{
    buttonGroup->setExclusive(false);
    if (!ui->hybridTypeCheckBox->isChecked())
    {
        buttonGroup->setExclusive(true);
    }
}
void SearchForCarsWindow::onBackPushButtonClicked()
{
    close();
}
void SearchForCarsWindow::onSavePushButtonClicked()
{
    QFile jsonFile("SearchResults.json");
    try
    {
        if (!jsonFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            throw Exception("Unable to open/create file", "JSONFile");
        }
    }
    catch (Exception& ex)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.whatAndContext()));
    }
    jsonFile.write(QJsonDocument(jsonArray).toJson());
    jsonFile.close();
    ui->infoAboutFileLabel->setText(QString::fromUtf8("Файл успешно сохранен"));
}