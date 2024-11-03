#include "Functions.h"
#include "catalogwindow.h"
#include "ui_catalogwindow.h"
#include "MainWindow.h"
#include "CarAddingWindow.h"
#include "CarCompareWindow.h"

CatalogWindow::CatalogWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CatalogWindow)
{
    ui->setupUi(this);
    ui->deletePushButton->setDisabled(true);
    ui->deletePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
    connect(ui->backPushButton, SIGNAL(clicked()), this, SLOT(on_backPushButton_clicked));
    connect(ui->addPushButton, &QPushButton::clicked, this, &CatalogWindow::onAddPushButtonClicked);
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &CatalogWindow::choosedItemInList);
    connect(ui->deletePushButton, &QPushButton::clicked, this, &CatalogWindow::onDeletePushButtonClicked);
    connect(ui->comparePushButton, &QPushButton::clicked, this, &CatalogWindow::onComparePushButtonClicked);
    addItemsToList();
    ui->listWidget->setStyleSheet("QListWidget::item:selected { background-color: #E0E8E6; border-radius: 12px; padding: 2px; border: none; outline: none; margin-right: 10px; }");
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
}
CatalogWindow::~CatalogWindow()
{
    delete ui;
}
void CatalogWindow::on_backPushButton_clicked()
{
    close();
    MainWindow* mainWindow = new MainWindow(this);
    mainWindow->show();
}
void CatalogWindow::onAddPushButtonClicked()
{
    carAddingWindow = new CarAddingWindow(this);
    carAddingWindow->show();
    connect(carAddingWindow, &CarAddingWindow::carAddingWindowClosed, this, &CatalogWindow::onCarAddingWindowClosed);
}
void CatalogWindow::addItemsToList()
{
    int count = 1;
    Repository<ElectricEngineCar> rep;
    const char* SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity "
        "FROM combustion_cars;";
    rep.print(SQL, 2, ui->listWidget, count);
    SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity "
        "FROM electric_cars;";
    rep.print(SQL, 1, ui->listWidget, count);
    SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type "
        "FROM hybrid_cars;";
    rep.print(SQL, 3, ui->listWidget, count);
}
void CatalogWindow::choosedItemInList()
{
    ui->deletePushButton->setEnabled(true);
    ui->deletePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: rgb(215, 67, 57); padding: 5px }");
    if (ui->listWidget->selectedItems().size() == 0)
    {
        ui->deletePushButton->setDisabled(true);
        ui->deletePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
    }
}
void CatalogWindow::onDeletePushButtonClicked()
{
   int index = ui->listWidget->currentIndex().row() + 1;
   ui->listWidget->takeItem(index - 1);
   Repository<ElectricEngineCar> rep;
   int rowsCountInElectricCarsTable;
   int rowsCountInCombustionCarsTable;
   int rowsCountInHybridCarsTable;
   dbRowsCount(rowsCountInHybridCarsTable, rowsCountInCombustionCarsTable, rowsCountInElectricCarsTable);
   string tableName;
   if (index <= rowsCountInCombustionCarsTable)
       tableName = "combustion_cars";
   if (index > rowsCountInCombustionCarsTable && index <= rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
   {
       tableName = "electric_cars";
       index -= rowsCountInCombustionCarsTable;
   }
   if (index > rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
   {
       tableName = "hybrid_cars";
       index -= (rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable);
   }
   rep.deleteCar(index, tableName);
   ui->listWidget->clear();
   ui->deletePushButton->setDisabled(true);
   ui->deletePushButton->setStyleSheet("QPushButton:hover { background-color: #CC3329; } QPushButton { color: rgb(244, 240, 239); border-radius: 12px; border-style: solid; border-width: 0px; background-color: #A62921; padding: 5px }");
   addItemsToList();
}
void CatalogWindow::getDataForComparison()
{
    int rowsCountInElectricCarsTable;
    int rowsCountInCombustionCarsTable;
    int rowsCountInHybridCarsTable;
    vector<ElectricEngineCar>electricCar(2);
    vector<CombustionEngineCar>combustionCar(2);
    vector<HybridEngineCar>hybridCar(2);
    vector<float>fuelTankCapacity(2);
    vector<float>batteryCapacity(2);
    vector<int>hybridType(2);
    Repository <ElectricEngineCar> rep1;
    Repository<CombustionEngineCar> rep2;
    Repository<ElectricEngineCar> rep3;
    dbRowsCount(rowsCountInHybridCarsTable, rowsCountInCombustionCarsTable, rowsCountInElectricCarsTable);
    string tableName;
    vector<int>engineType(2);
    char const* SQL;
    CarCompareWindow* window = new CarCompareWindow(this);
    window->show();
    if (carIndexForComparison1 <= rowsCountInCombustionCarsTable)
    {
        tableName = "combustion_cars";
        engineType[0] = 2;
        SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity FROM combustion_cars WHERE id = ?;";
        rep2.getCar(carIndexForComparison1, tableName, SQL, engineType[0], combustionCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    }
    if (carIndexForComparison1 > rowsCountInCombustionCarsTable && carIndexForComparison1 <= rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
    {
        tableName = "electric_cars";
        engineType[0] = 1;
        SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity FROM electric_cars WHERE id = ?;";
        carIndexForComparison1 -= rowsCountInCombustionCarsTable;
        rep1.getCar(carIndexForComparison1, tableName, SQL, engineType[0], electricCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    }
    if (carIndexForComparison1 > rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
    {
        tableName = "hybrid_cars";
        engineType[0] = 3;
        carIndexForComparison1 -= (rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable);
        SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type FROM hybrid_cars WHERE id = ?;";
        rep3.getCar(carIndexForComparison1, tableName, SQL, engineType[0], hybridCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    }
    if (carIndexForComparison2 <= rowsCountInCombustionCarsTable)
    {
        tableName = "combustion_cars";
        engineType[1] = 2;
        SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity FROM combustion_cars WHERE id = ?;";
        rep2.getCar(carIndexForComparison2, tableName, SQL, engineType[1], combustionCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    }
    if (carIndexForComparison2 > rowsCountInCombustionCarsTable && carIndexForComparison2 <= rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
    {
        tableName = "electric_cars";
        engineType[1] = 1;
        carIndexForComparison2 -= rowsCountInCombustionCarsTable;
        SQL = "SELECT year_of_production, mileage, price, brand, model, battery_capacity FROM electric_cars WHERE id = ?;";
        rep1.getCar(carIndexForComparison2, tableName, SQL, engineType[1], electricCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    }
    if (carIndexForComparison2 > rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable)
    {
        tableName = "hybrid_cars";
        engineType[1] = 3;
        carIndexForComparison2 -= (rowsCountInCombustionCarsTable + rowsCountInElectricCarsTable);
        SQL = "SELECT year_of_production, mileage, price, brand, model, fuel_tank_capacity, battery_capacity, hybrid_type FROM hybrid_cars WHERE id = ?;";
        rep3.getCar(carIndexForComparison2, tableName, SQL, engineType[1], hybridCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    }
    if (engineType[0] == 1)
    {
        window->infoAboutFirstCar(electricCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    }
    if (engineType[0] == 2)
        window->infoAboutFirstCar(combustionCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    if (engineType[0] == 3)
        window->infoAboutFirstCar(hybridCar[0], fuelTankCapacity[0], batteryCapacity[0], hybridType[0]);
    if (engineType[1] == 1)
        window->infoAboutSecondCar(electricCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    if (engineType[1] == 2)
        window->infoAboutSecondCar(combustionCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    if (engineType[1] == 3)
        window->infoAboutSecondCar(hybridCar[1], fuelTankCapacity[1], batteryCapacity[1], hybridType[1]);
    window->compareCars();
    ui->compareLabel->setText("Чтобы сравнить\nдва автомобиля,\nвыберите первый,\nнажмите кнопку,\nзатем выберите\nвторой и нажмите\nснова.");
}
void CatalogWindow::onComparePushButtonClicked()
{
    clickCountForComparison++;
    if (clickCountForComparison == 1)
    {
        ui->compareLabel->setText("Теперь выберите\n2-ой автомобиль");
        carIndexForComparison1 = ui->listWidget->currentIndex().row() + 1;
    }
    if (clickCountForComparison == 2)
    {
        carIndexForComparison2 = ui->listWidget->currentIndex().row() + 1;
        clickCountForComparison = 0;
        getDataForComparison();
    }
}
void CatalogWindow::onCarAddingWindowClosed()
{
    carAddingWindow->close();
    ui->listWidget->clear();
    addItemsToList();
}