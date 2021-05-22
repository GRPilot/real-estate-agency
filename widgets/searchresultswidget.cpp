#include "mainwindow.h"
#include "widgetmanager.h"

#include "searchresultswidget.h"
#include "ui_searchresultswidget.h"

#include "searchresultbuilder.h"

ObjectDataList getTests();

SearchResultsWidget::SearchResultsWidget(WidgetManager *owner, QWidget *parent) :
    QWidget(parent), ui(new Ui::SearchResultsWidget), owner(owner),
    builder(std::make_unique<ResultsPageBuilder>()) {
    assert(nullptr != owner);
    ui->setupUi(this);
    connect(builder.get(), &ResultsPageBuilder::recordCreated,
            this, &SearchResultsWidget::onNewRecordAppend);

    builder->construct(getTests());
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

void SearchResultsWidget::onNewRecordAppend(QHBoxLayout *record) {
    if(nullptr == record) {
        return;
    }
    if(nullptr != ui->resultsLayout) {
        ui->resultsLayout->addLayout(record);
    }
}

ObjectDataList getTests() {
    return {
        ObjectData{
            "/home/gollan/Pictures/Logos/mask_001.jpeg",
            ObjectData::Info{
                "First record",
                "This is the first test record",
                "Somewhere"
            },
            ObjectData::Owner {
                "Owner owner ownererer",
                "8 (888)-888-8888",
                "owner@owner.owner"
            }
        },
        ObjectData{
            "/home/gollan/Pictures/Logos/Logo_0021.webp",
            ObjectData::Info{
                "Second record",
                "This is the first test record",
                "Somewhere"
            },
            ObjectData::Owner {
                "Owner owner ownererer",
                "8 (888)-888-8888",
                "owner@owner.owner"
            }
        },
        ObjectData{
            "/home/gollan/Pictures/Logos/woman.png",
            ObjectData::Info{
                "Third record",
                "This is the first test record",
                "Somewhere"
            },
            ObjectData::Owner {
                "Owner owner ownererer",
                "8 (888)-888-8888",
                "owner@owner.owner"
            }
        },
        ObjectData{
            "/home/gollan/Pictures/8-bit-anime-city.jpg",
            ObjectData::Info{
                "Third record",
                "This is the first test record",
                "Somewhere"
            },
            ObjectData::Owner {
                "Owner owner ownererer",
                "8 (888)-888-8888",
                "owner@owner.owner"
            }
        },
        ObjectData{
            "/home/gollan/Pictures/kaitlyn-dougon-carbon-valley.jpg",
            ObjectData::Info{
                "Third record",
                "This is the first test record",
                "Somewhere"
            },
            ObjectData::Owner {
                "Owner owner ownererer",
                "8 (888)-888-8888",
                "owner@owner.owner"
            }
        }
    };
}
