#pragma once
#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QString>
#include <QListWidget>
#include <QDialog>
#include <QInputDialog>
#include "CarAddingWindow.h"
#include "Functions.h"
#include "List.h"

namespace Ui {
    class CatalogWindow;
}

template <typename T>
class List;

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
    List<CombustionEngineCar> combustionCarsList;
    List<ElectricEngineCar> electricCarsList;
    List<HybridEngineCar> hybridCarsList;
    void addItemsToLists();
private slots:
    void onBackPushButtonClicked();
    void onAddPushButtonClicked();
    void choosedItemInList();
    void onDeletePushButtonClicked();
    void onComparePushButtonClicked();
    void onCarAddingWindowClosed();
    void onFilterComboBoxChanged();
};

#endif // CATALOGWINDOW_H