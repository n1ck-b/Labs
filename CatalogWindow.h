#pragma once
#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QString>
#include <QListWidget>
#include <QDialog>
#include <QInputDialog>
#include "CarAddingWindow.h"

namespace Ui {
    class CatalogWindow;
}

class CatalogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget* parent = nullptr);
    ~CatalogWindow();
    void addItemsToList();
    void getDataForComparison();
    CarAddingWindow* carAddingWindow;
private:
    Ui::CatalogWindow* ui;
    int clickCountForComparison = 0;
    int carIndexForComparison1 = 0;
    int carIndexForComparison2 = 0;
private slots:
    void onBackPushButtonClicked();
    void onAddPushButtonClicked();
    void choosedItemInList();
    void onDeletePushButtonClicked();
    void onComparePushButtonClicked();
    void onCarAddingWindowClosed();
};

#endif // CATALOGWINDOW_H