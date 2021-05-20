#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class SearchWidget;
}

class WidgetManager;

class SearchWidget : public QWidget {
    Q_OBJECT
public:
    explicit SearchWidget(WidgetManager *owner, QWidget *parent = nullptr);
    ~SearchWidget();

protected:
    void changeEvent(QEvent *e);

private slots:
    void onRoomsClicked();
    void onSpinBoxValueChanged();
    void onSearchButtonClicked();

private:
    Ui::SearchWidget *ui;
    WidgetManager *owner;
    void initializeRoomsComboBox();
};

#endif // SEARCHWIDGET_H
