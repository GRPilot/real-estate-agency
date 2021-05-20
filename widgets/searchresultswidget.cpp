#include "mainwindow.h"
#include "widgetmanager.h"

#include "searchresultswidget.h"
#include "ui_searchresultswidget.h"

SearchResultsWidget::SearchResultsWidget(WidgetManager *owner, QWidget *parent) :
    QWidget(parent), ui(new Ui::SearchResultsWidget), owner(owner),
    builder(std::make_unique<RecordBuilder>()) {
    assert(nullptr != owner);
    ui->setupUi(this);
}

SearchResultsWidget::~SearchResultsWidget() {
    delete ui;
}

void SearchResultsWidget::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void SearchResultsWidget::onBackButtonClicked() {
    emit owner->changeWidget(WidgetType::SearchWidgetType);
}
