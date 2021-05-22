#ifndef SEARCHRESULTSWIDGET_H
#define SEARCHRESULTSWIDGET_H

#include <QWidget>
#include <QBoxLayout>

namespace Ui {
class SearchResultsWidget;
}

class WidgetManager;
class ResultsPageBuilder;

class SearchResultsWidget : public QWidget {
    Q_OBJECT

public:
    explicit SearchResultsWidget(WidgetManager *owner, QWidget *parent = nullptr);
    ~SearchResultsWidget();

protected:
    void changeEvent(QEvent *e);

private slots:
    void onBackButtonClicked();
    void onNewRecordAppend(QHBoxLayout *record);

private:
    Ui::SearchResultsWidget *ui;
    WidgetManager *owner;
    std::unique_ptr<ResultsPageBuilder> builder;
};

#endif // SEARCHRESULTSWIDGET_H
