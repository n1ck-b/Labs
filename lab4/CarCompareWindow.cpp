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
