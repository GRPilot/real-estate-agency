#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QWidget>
#include <memory>
#include <map>
#include <singleton.h>

using WidgetPtr = std::shared_ptr<QWidget>;

enum class WidgetType {
    SearchWidgetType,
    SearchResultsWidgetType,
};

class WidgetManager : public QObject {
    Q_OBJECT
public:

    explicit WidgetManager(MainWindow *parent);

    QWidget *getWidget(WidgetType type);
    QWidget *getCurrentWidget();

signals:
    void changeWidget(WidgetType type);

private:
    std::unordered_map<WidgetType, WidgetPtr>  widgets;
    MainWindow *parent;
    WidgetType current;

    WidgetPtr createWidget(WidgetType type);
};

#endif // WIDGETMANAGER_H
