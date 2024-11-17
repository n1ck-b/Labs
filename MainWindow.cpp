#include "MainWindow.h"
#include "Functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    setStyles();
    connect(ui->catalogPushButton, &QPushButton::clicked, this, &MainWindow::onCatalogPushButtonClicked);
    connect(ui->exitPushButton, &QPushButton::clicked, this, &MainWindow::onExitPushButtonClicked);
    connect(ui->searchPushButton, &QPushButton::clicked, this, &MainWindow::onSearchPushButtonClicked);
}

MainWindow::~MainWindow()
{
    delete catalogWindow;
    delete ui;
}

void MainWindow::onCatalogPushButtonClicked()
{
    close();
    catalogWindow = new CatalogWindow(this);
    catalogWindow->show();
}

void MainWindow::onExitPushButtonClicked()
{
    exit(0);
}
void MainWindow::onSearchPushButtonClicked()
{
    SearchForCarsWindow* window = new SearchForCarsWindow(this);
    window->show();
}
void MainWindow::setStyles()
{
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(QColor(215, 67, 57));
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setBlurRadius(10);
    ui->loginPushButton->setGraphicsEffect(shadowEffect);
}
