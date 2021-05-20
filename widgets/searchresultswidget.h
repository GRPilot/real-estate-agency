#ifndef SEARCHRESULTSWIDGET_H
#define SEARCHRESULTSWIDGET_H

#include <QWidget>
#include <QBoxLayout>

namespace Ui {
class SearchResultsWidget;
}

class WidgetManager;

class IComponentBuilder {
public:
    virtual bool build(const std::string &data, QHBoxLayout *product) = 0;
    virtual bool build(unsigned long long data, QHBoxLayout *product) = 0;
};
using IComponentBuilderPtr = std::shared_ptr<IComponentBuilder>;

class RecordBuilder {
public:
    enum PartType {
        IMAGE,
        TITLE,
        PLACE,
        AMOUNT,
        OWNER_NAME,
        PHONE
    };
    bool add(const std::string &data, PartType type);
    bool add(unsigned long long data, PartType type);

    QHBoxLayout *getResult();

private:
    std::unique_ptr<QHBoxLayout> record;
    std::map<PartType, IComponentBuilderPtr> builders;
    IComponentBuilderPtr getBuilder(PartType type);
};

class SearchResultsWidget : public QWidget {
    Q_OBJECT

public:
    explicit SearchResultsWidget(WidgetManager *owner, QWidget *parent = nullptr);
    ~SearchResultsWidget();

protected:
    void changeEvent(QEvent *e);

private slots:
    void onBackButtonClicked();

private:
    Ui::SearchResultsWidget *ui;
    WidgetManager *owner;
    std::unique_ptr<RecordBuilder> builder;
};

#endif // SEARCHRESULTSWIDGET_H
