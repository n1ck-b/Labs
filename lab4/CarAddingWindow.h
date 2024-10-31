#pragma once
#ifndef CARADDINGWINDOW_H
#define CARADDINGWINDOW_H

#include <QString>
#include <QListWidget>
#include <QDialog>
#include <QInputDialog>

namespace Ui {
    class CarAddingWindow;
}

class CarAddingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CarAddingWindow(QWidget* parent = nullptr);
    ~CarAddingWindow();
    void carAdding();
private:
    Ui::CarAddingWindow* ui;
private slots:
    void on_backPushButton_clicked();
    void on_addPushButton_clicked();
    void editedAnyLineEdit();
   /* void editedMileageLineEdit();*/
};

#endif // CARADDINGWINDOW_H
