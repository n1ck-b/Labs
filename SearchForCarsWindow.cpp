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
    ui->listWidget->setStyleSheet("QScrollBar { padding: 0px; margin: 0px; padding-bottom: 10px; background-color: rgb(244, 240, 239); border: 1px solid rgb(55, 51, 53); width: 15px; border-radius: 7px;} QScrollBar::handle:vertical { border: 1px solid rgb(55, 51, 53); background-color: rgb(244, 240, 239); border-radius: 4px; margin: 2px; margin-top: 20px; margin-bottom: 15px; min-height: 25px; }  QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical { background: none; } QScrollBar::add-line:vertical { width: 11px; height: 20px; padding: 0px; margin: 0px; border: none; image: url(:/rcs/free-icon-down-arrow-2985150.png); padding-left: 2px; padding-right: 2px; margin-top: 0px; margin-bottom: 0px; background-size: contain; background-position: center;} QScrollBar::sub-line:vertical { width: 11px; height: 20px; padding: 0px; margin: 0px; border: none; image: url(:/rcs/free-icon-down-arrow-29851501.png); padding-left: 2px; padding-right: 2px; margin-top: 0px; margin-bottom: 0px; background-size: contain; background-position: center;}");
    ui->savePushButton->setDisabled(true);
    ui->savePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
}
SearchForCarsWindow::~SearchForCarsWindow()
{
    delete ui;
}
void SearchForCarsWindow::createSQLQuery(std::string& sql, QString lowerValue, QString upperValue, bool& isFirst, std::string parameterName)
{
    if (!isFirst)
    {
        sql += " AND";
    }
    else
        isFirst = false;
    sql += " ( " + parameterName + " >= " + lowerValue.toStdString();
    sql += " AND " + parameterName + " <= " + upperValue.toStdString() + " )";

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
        createSQLQuery(sql, ui->yearLineEditFrom->text(), ui->yearLineEditTo->text(), isFirst, "year_of_production");
    if (ui->mileageCheckBox->isChecked())
        createSQLQuery(sql, ui->mileageLineEditFrom->text(), ui->mileageLineEditTo->text(), isFirst, "mileage");
    if (ui->priceCheckBox->isChecked())
        createSQLQuery(sql, ui->priceLineEditFrom->text(), ui->priceLineEditTo->text(), isFirst, "price");
    if (ui->fuelCheckBox->isChecked())
    {
        if (!ui->hybridTypeCheckBox->isChecked())
        {
            tableName = "combustion_cars";
            engineType = 2;
        }
        createSQLQuery(sql, ui->fuelLineEditFrom->text(), ui->fuelLineEditTo->text(), isFirst, "fuel_tank_capacity");
    }
    if (ui->batteryCheckBox->isChecked())
    {
        if (!ui->hybridTypeCheckBox->isChecked())
        {
            tableName = "electric_cars";
            engineType = 1;
        }
        createSQLQuery(sql, ui->batteryLineEditFrom->text(), ui->batteryLineEditTo->text(), isFirst, "battery_capacity");
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
        int hybridType = ui->hybridTypeComboBox->currentIndex();
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
            throw Exception("Unable to open/create file", "JSON File");
        }
    }
    catch (Exception& ex)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.whatAndContext()));
    }
    jsonFile.write(QJsonDocument(jsonArray).toJson());
    jsonFile.flush();
    jsonFile.close();
    ui->infoAboutFileLabel->setText(QString::fromUtf8("Файл успешно сохранен"));
}