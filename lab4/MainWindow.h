#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "CatalogWindow.h"
#include "SearchForCarsWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindowClass ui;
    CatalogWindow* catalogWindow;
private slots:
    void on_catalogPushButton_clicked();
    void on_exitPushButton_clicked();
    void onSearchPushButtonClicked();
};
