#include <QStandardItemModel>
#include <QStandardItem>

#include "searchwidget.h"
#include "ui_searchwidget.h"

#include "mainwindow.h"
#include "widgetmanager.h"

SearchWidget::SearchWidget(WidgetManager *owner, QWidget *parent)
    : QWidget(parent), ui(new Ui::SearchWidget), owner(owner) {
    assert(nullptr != owner);
    ui->setupUi(this);
    initializeRoomsComboBox();
}

SearchWidget::~SearchWidget() {
    delete ui;
}

void SearchWidget::changeEvent(QEvent *e) {
    QWidget::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void SearchWidget::onRoomsClicked() {
}

void SearchWidget::initializeRoomsComboBox() {
    const size_t MAX_ROOMS_COUNT = 6;
    QStandardItemModel *model = new QStandardItemModel(MAX_ROOMS_COUNT, 1);
    model->setItem(0, 0, new QStandardItem("Выберите количество комнат"));

    QString title{ "Студия" };
    for(size_t i = 1; i <= MAX_ROOMS_COUNT; ++i) {
        QStandardItem *item = new QStandardItem(title);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData((i == 1 ? Qt::Checked : Qt::Unchecked), Qt::CheckStateRole);
        model->setItem(i, 0, item);

        title = QString("%0%1комнатная").arg(i + 1)
                .arg(i + 1 == MAX_ROOMS_COUNT ? "+-" : "-");
    }
    ui->roomsComboBox->setModel(model);
}

void SearchWidget::onSpinBoxValueChanged() {
    int from = ui->fromSpinBox->value();
    int to = ui->toSpinBox->value();
    QPalette palette = ui->toSpinBox->palette();
    if(from >= to) {
        palette.setColor(ui->toSpinBox->backgroundRole(), Qt::red);
    } else {
        QColor clr = ui->fromSpinBox->palette().color(ui->fromSpinBox->backgroundRole());
        palette.setColor(ui->toSpinBox->backgroundRole(), clr);
    }
    ui->searchButton->setEnabled(from < to);
    ui->toSpinBox->setPalette(palette);
}

void SearchWidget::onSearchButtonClicked() {
    emit owner->changeWidget(WidgetType::SearchResultsWidgetType);
}
