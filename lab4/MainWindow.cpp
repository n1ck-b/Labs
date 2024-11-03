#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setStyles();
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
void MainWindow::setStyles()
{
   /* QPropertyAnimation* animation = new QPropertyAnimation(ui.catalogPushButton, "BackgroundColor", this);
    animation->setDuration(300);
    QColor color("#cce8f4");
    animation->setStartValue(color);
    color = "#92AEBE";
    animation->setEndValue(color);*/
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    shadowEffect->setColor(QColor(215, 67, 57));
    shadowEffect->setXOffset(0);
    shadowEffect->setYOffset(0);
    shadowEffect->setBlurRadius(10);
    ui.loginPushButton->setGraphicsEffect(shadowEffect);
}