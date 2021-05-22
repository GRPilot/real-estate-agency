#ifndef SEARCHRESULTBUILDER_H
#define SEARCHRESULTBUILDER_H

#include <QBoxLayout>
#include <memory>
#include <string>

enum class BuilderStatus {
    OK = 0,
    InvalidArguments,
    InvalidJSON,
};

struct ObjectData {
    QByteArray img;
    struct Info {
        QString title;
        QString description;
        QString location;
    } objectInfo;
    struct Owner {
        QString fullname;
        QString phone;
        QString email;
    } ownerInfo;
};

using ObjectDataList = std::vector<ObjectData>;


/**
 * @brief The search result builder
 */
class RecordPanelBuilder {
    class ImageBuilder;
    class DescriptionBuilder;
    class ContactsBuilder;
public:

    explicit RecordPanelBuilder();

    BuilderStatus construct(const ObjectData &data);
    QHBoxLayout *getResult();

private:
    std::unique_ptr<QHBoxLayout> layout;
    std::unique_ptr<ImageBuilder> imageBuilder;
    std::unique_ptr<DescriptionBuilder> descrBuilder;
    std::unique_ptr<ContactsBuilder> contactsBuilder;
};

class ResultsPageBuilder : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construct the objects data visualization and place it in target
     * @param[in] objects The information obout objects for building. @see ObjectData
     * @param[out] target The widget where will be placed objects visualization
     * @return status of constructing. @see BuilderStatus
     */
    BuilderStatus construct(const ObjectDataList &objects);

signals:
    void recordCreated(QHBoxLayout *record);
};

#endif // SEARCHRESULTBUILDER_H

