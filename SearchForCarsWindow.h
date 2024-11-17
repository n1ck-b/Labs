#ifndef SEARCHFORCARSWINDOW_H
#define SEARCHFORCARSWINDOW_H

#include <QDialog>
#include <QButtonGroup>
#include <QJsonArray>
#include <QFile>
#include <QMessageBox>
#include <QJsonDocument>

namespace Ui {
    class SearchForCarsWindow;
}

class SearchForCarsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchForCarsWindow(QWidget* parent = nullptr);
    ~SearchForCarsWindow();

private:
    Ui::SearchForCarsWindow* ui;
    QButtonGroup* buttonGroup;
    QJsonArray jsonArray;
private slots:
    void onSearchPushButtonClicked();
    void onCheckBoxEdited();
    void onBackPushButtonClicked();
    void onSavePushButtonClicked();
};

#endif // SEARCHFORCARSWINDOW_H
