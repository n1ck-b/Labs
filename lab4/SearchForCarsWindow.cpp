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
}
SearchForCarsWindow::~SearchForCarsWindow()
{
    delete ui;
}
void SearchForCarsWindow::onSearchPushButtonClicked()
{
    ui->listWidget->clear();
    std::string sql = "";
    std::string tableName = " ";
    bool isFirst = true;
    QString qstr;
    int engineType = 0;
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
        qstr = ui->yearLineEditFrom->text();
        sql += " (year_of_production >= " + qstr.toStdString();
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
        qstr = ui->mileageLineEditFrom->text();
        sql += " (mileage >= " + qstr.toStdString();
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
        {
            isFirst = false;
            qstr = ui->priceLineEditFrom->text();
            sql += " (price >= " + qstr.toStdString();
            qstr = ui->priceLineEditTo->text();
            sql += " AND price <= " + qstr.toStdString() + " )";
        }
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
        qstr = ui->fuelLineEditFrom->text();
        sql += " (fuel_tank_capacity >= " + qstr.toStdString();
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
        qstr = ui->batteryLineEditFrom->text();
        sql += " (battery_capacity >= " + qstr.toStdString();
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
        rep.searchForCarInDB(SQL.c_str(), engineType, count, ui->listWidget);
        ui->listWidget->repaint();
    }
    else
    {
        SQL += "combustion_cars WHERE" + sql;
        rep.searchForCarInDB(SQL.c_str(), 2, count, ui->listWidget);
        SQL = "SELECT * FROM electric_cars WHERE" + sql;
        rep.searchForCarInDB(SQL.c_str(), 1, count, ui->listWidget);
        SQL = "SELECT * FROM hybrid_cars WHERE" + sql;
        rep.searchForCarInDB(SQL.c_str(), 3, count, ui->listWidget);
        ui->listWidget->repaint();
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