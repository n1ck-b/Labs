#ifndef SEARCHFORCARSWINDOW_H
#define SEARCHFORCARSWINDOW_H

#include <QDialog>
#include <QButtonGroup>


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
private slots:
    void onSearchPushButtonClicked();
    void onCheckBoxEdited();
    void onBackPushButtonClicked();
};

#endif // SEARCHFORCARSWINDOW_H
