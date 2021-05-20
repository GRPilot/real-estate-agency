#include <QObject>

#include "mainwindow.h"
#include "widgetmanager.h"

#include "searchwidget.h"
#include "searchresultswidget.h"

WidgetManager::WidgetManager(MainWindow *parent)
    : parent(parent), current(WidgetType::SearchWidgetType) {
    QObject::connect(
        this, &WidgetManager::changeWidget,
        parent, &MainWindow::onChangedWidget
    );
}

QWidget *WidgetManager::getWidget(WidgetType type) {
    WidgetPtr &widget = widgets[type];
    if(nullptr == widget) {
        widget = createWidget(type);
    }
    current = type;
    return widget.get();
}

QWidget *WidgetManager::getCurrentWidget() {
    return getWidget(current);
}

WidgetPtr WidgetManager::createWidget(WidgetType type) {
    switch(type) {
        case WidgetType::SearchWidgetType:
            return std::make_shared<SearchWidget>(this, parent);
        case WidgetType::SearchResultsWidgetType:
            return std::make_shared<SearchResultsWidget>(this, parent);
    }
    return nullptr;
}
