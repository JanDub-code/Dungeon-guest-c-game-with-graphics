#ifndef QUEST_H
#define QUEST_H

#include <QObject>
#include <vector>

#include "object.h"

class Quest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ getTitle CONSTANT)
    Q_PROPERTY(QString context READ getContext CONSTANT)
    Q_PROPERTY(QString fin_context READ getFinContext CONSTANT)
    Q_PROPERTY(bool is_main READ getType CONSTANT)
    Q_PROPERTY(bool is_active READ getStatus NOTIFY statusChanged)
    Q_PROPERTY(bool is_claimed READ isClaimed NOTIFY claimedStatusChanged)
    Q_PROPERTY(bool is_prepared READ isPrepared NOTIFY preparedStatusChanged)
    Q_PROPERTY(bool is_previewed READ isPreviewed NOTIFY previewStatusChanged)
    Q_PROPERTY(QVariant target READ getTarget NOTIFY targetChanged)
private:
    bool m_is_active;
    bool m_is_main_quest; // TODO: If is main quest then disable Decline button
    bool m_is_claimed;
    bool m_is_prepared;
    bool m_is_completed;
    bool m_is_previewed;
    std::string m_title;
    std::string m_context;
    std::string m_fin_context;
    Object *m_source; // INFO: Do not delete ever!
    Object *m_target;
    Object *m_price;
    std::string m_quest_object_name;
    QString m_thumbnail; // Path to thumbnail image
public:
    explicit Quest(QObject *parent = nullptr);
    Quest(Object *object, std::string title = "Default Title",
          std::string context = "Default context", std::string fin_context = "Default compleded context", QString thumbnail = "", bool is_main = false);
    ~Quest();
    void setPrepared();
    void setNonPrepared();
    void setActive();
    void setInactive();
    void setAsClaimed();
    void enablePreview();
    void disablePreview();
    bool isClaimed();
    bool isPrepared();
    bool isPreviewed();
    bool getStatus();
    bool getType();
    QString getTitle();
    QString getContext();
    QString getFinContext();
    Q_INVOKABLE void disableObjectQuestState(); // Call if quest inactive or finished
    bool isRequiredObject(const Object *obj);
    bool isRequiredObject(std::string target);
    bool isSourceObject(const Object *obj);
    void setTargetObject(Object *target);
    bool isTargetObjectPresent();
    QVariant getTarget();
    void setTargetName(std::string target);
    void setPrice(Object *price);
    Object *getPrice();
    Q_INVOKABLE float getAngleToTarget();
    //void fixButtons();
    void DEBUGprintAllStates();
    void refreshSourceState();

    enum class QType
    {
        QT_TALK = 0x0,
        QT_KILL = 0x1, // kill entity
        QT_BRING = 0x2  // bring any object (entity, item etc.)
    };
    Q_ENUM(QType)

    void setQuestType(QType type);
    bool actionMatch(QType type);
private:
    QType m_quest_type;
signals:
    void statusChanged();
    void claimedStatusChanged();
    void preparedStatusChanged();
    void previewStatusChanged();
    void targetChanged();
};

#endif // QUEST_H

// TODO: Add EventItem, EventEntity and more.
//         Example operations outside of this class:
//             If quest item collected set prepared to true and call eventChangeObjectQuestState. (test item using isRequiredObjectName and then call setPrepared)
//             If quest item dropped from inventory to ground, reset progress. (test item using isRequiredObjectName and then call setNonPrepared)
//             If quest entity killed or found set prepared to true and call eventChangeObjectQuestState. (similar to above)
//             If quest entity accidentally killed, reset progress. (similar to above and delete quest and/or set to failed and then delete... failed not implemented)
//             If declined, destroy quest and set Object quest to NONE

// DONE: GameEngine::declineQuest()
