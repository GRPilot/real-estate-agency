#include <QPixmap>
#include <QLabel>

#include "searchresultswidget.h"
#include "widgetmanager.h"

namespace {

class ImageBuilder : public IComponentBuilder {
public:
    bool build(const std::string &data, QHBoxLayout *product) override {
        if(nullptr == product || data.empty()) {
            return false;
        }
        QPixmap img(QString{ data.c_str() });
        if(img.isNull()) {
            return false;
        }
        QLabel *imgFrame = new QLabel(nullptr);
        imgFrame->setPixmap(img);
        imgFrame->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        product->addWidget(imgFrame);
        return true;
    }
    bool build(unsigned long long, QHBoxLayout *) override {
        return false;
    }
};

class TitleBuilder : public IComponentBuilder {

};

} // anon namespace

bool RecordBuilder::add(const std::string &data, PartType type) {
    IComponentBuilderPtr builder = getBuilder(type);
    if(nullptr == builder) {
        return false;
    }
    return builder->build(data, record.get());
}

bool RecordBuilder::add(unsigned long long data, PartType type) {
    IComponentBuilderPtr builder = getBuilder(type);
    if(nullptr == builder) {
        return false;
    }
    return builder->build(data, record.get());
}

IComponentBuilderPtr RecordBuilder::getBuilder(PartType type) {
    IComponentBuilderPtr &builder = builders[type];
    if(nullptr != builder) {
        return builder;
    }
    switch(type) {
        case RecordBuilder::IMAGE: return std::make_shared<ImageBuilder>();
        case RecordBuilder::TITLE: return nullptr;
        case RecordBuilder::PLACE: return nullptr;
        case RecordBuilder::AMOUNT: return nullptr;
        case RecordBuilder::OWNER_NAME: return nullptr;
        case RecordBuilder::PHONE: return nullptr;
    }
    return nullptr;
}
