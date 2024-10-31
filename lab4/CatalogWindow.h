#pragma once
#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QString>
#include <QListWidget>
#include <QDialog>
#include <QInputDialog>

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
private:
    Ui::CatalogWindow* ui;
    int clickCountForComparison = 0;
    int carIndexForComparison1 = 0;
    int carIndexForComparison2 = 0;
private slots:
    void on_backPushButton_clicked();
    void on_addPushButton_clicked();
    void choosedItemInList();
    void onDeletePushButtonClicked();
    void onComparePushButtonClicked();
};

#endif // CATALOGWINDOW_H