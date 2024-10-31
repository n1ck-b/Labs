#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.catalogPushButton, SIGNAL(clicked()), this, SLOT(on_catalogPushButton_clicked));
    connect(ui.exitPushButton, SIGNAL(clicked()), this, SLOT(on_exitPushButton_clicked));
    connect(ui.searchPushButton, &QPushButton::clicked, this, &MainWindow::onSearchPushButtonClicked);
}

MainWindow::~MainWindow()
{
    delete catalogWindow;
}

void MainWindow::on_catalogPushButton_clicked()
{
    close();
    catalogWindow = new CatalogWindow(this);
    catalogWindow->show();
}

void MainWindow::on_exitPushButton_clicked()
{
    exit(0);
}
void MainWindow::onSearchPushButtonClicked()
{
    SearchForCarsWindow* window = new SearchForCarsWindow(this);
    window->show();
}