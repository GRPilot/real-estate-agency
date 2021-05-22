#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QPushButton>

#include "searchresultbuilder.h"

///
/// @brief The RecordPanelBuilder::ImageBuilder class
///
class RecordPanelBuilder::ImageBuilder {
    const size_t MAX_IMAGE_HEIGHT = 140;
public:
    QHBoxLayout *construct(const ObjectData &data) {
        QPixmap img{ QString(data.img) };
        if(img.isNull()) {
            return nullptr;
        }
        QLabel *frame{ new QLabel() };
        frame->setPixmap(img.scaled(MAX_IMAGE_HEIGHT, MAX_IMAGE_HEIGHT));
        frame->setSizePolicy(QSizePolicy{
            QSizePolicy::Policy::Minimum,
            QSizePolicy::Policy::Minimum
        });
        QHBoxLayout *layout{ new QHBoxLayout() };
        layout->addWidget(frame);
        return layout;
    }
};

///
/// @brief The RecordPanelBuilder::DescriptionBuilder class
///
class RecordPanelBuilder::DescriptionBuilder {
public:
    QVBoxLayout *construct(const ObjectData::Info &data) {
        QLabel *title = new QLabel{ data.title };
        QLabel *description = new QLabel{ data.description };
        QLabel *location = new QLabel{ data.location };
        QVBoxLayout *layout{ new QVBoxLayout() };
        layout->addWidget(title);
        layout->addWidget(location);
        layout->addWidget(description, 1);
        return layout;
    }
};

class RecordPanelBuilder::ContactsBuilder {
public:
    class OwnerDataLayout : public QVBoxLayout {
        const QString showInfoTitle{ "Показать информацию" };
        const QString hideInfoTitle{ "Скрыть информацию" };
    public:
        explicit OwnerDataLayout(const ObjectData::Owner &data) : button(showInfoTitle), hidden(true) {
            labels[FULLNAME] = std::make_shared<QLabel>(data.fullname);
            labels[PHONE] = std::make_shared<QLabel>(data.phone);
            labels[EMAIL] = std::make_shared<QLabel>(data.email);
            addWidget(&button);
            for(auto &label : labels) {
                label->hide();
                addWidget(label.get());
            }
            button.connect(&button, &QPushButton::pressed, this, &OwnerDataLayout::onButtonClicked);
        }
    private slots:
        void onButtonClicked() {
            if(hidden) {
                for(auto &label : labels) {
                    label->show();
                }
            } else {
                for(auto &label : labels) {
                    label->hide();
                }
            }
            button.setText(hidden ? hideInfoTitle : showInfoTitle);
            hidden = !hidden;
        }
    private:
        enum LabelTypes {
            FULLNAME, PHONE, EMAIL,
            NUMBER_OF_LABELS ///< Always last
        };
        std::array<std::shared_ptr<QLabel>, NUMBER_OF_LABELS> labels;
        QPushButton button;
        bool hidden;
    };

    QVBoxLayout *construct(const ObjectData::Owner &data) {
        return new OwnerDataLayout{ data };
    }
};

///
/// @class RecordPanelBuilder
///
RecordPanelBuilder::RecordPanelBuilder()
    : imageBuilder{ std::make_unique<ImageBuilder>() },
      descrBuilder{ std::make_unique<DescriptionBuilder>() },
      contactsBuilder{ std::make_unique<ContactsBuilder>() } {
}

BuilderStatus RecordPanelBuilder::construct(const ObjectData &data) {
    layout.reset(new QHBoxLayout());
    layout->addLayout(imageBuilder->construct(data));
    layout->addLayout(descrBuilder->construct(data.objectInfo), 1);
    layout->addLayout(contactsBuilder->construct(data.ownerInfo));
    return BuilderStatus::OK;
}

QHBoxLayout *RecordPanelBuilder::getResult() {
    return layout.release();
}

BuilderStatus ResultsPageBuilder::construct(const ObjectDataList &objects) {
    RecordPanelBuilder builder;
    for(const auto &object : objects) {
        BuilderStatus status = builder.construct(object);
        if(BuilderStatus::OK == status) {
            QHBoxLayout *layout = builder.getResult();
            emit recordCreated(layout);
        }
    }
    return BuilderStatus::OK;
}

