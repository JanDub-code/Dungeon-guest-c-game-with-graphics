#include "quest.h"
//#include "game_engine.h"

Quest::Quest(QObject *parent) : QObject(parent)
{
    m_is_active = true; // don't forget to set all other quests to inactive
    m_is_main_quest = false;
    m_is_claimed = false;
    m_is_prepared = false;
    m_is_completed = false;
    m_is_previewed = false;
    m_title = "Default Title";
    m_context = "Default context";
    m_fin_context = "Default compleded context";
    m_source = nullptr;
    m_target = nullptr;
    m_price = nullptr;
    m_quest_object_name = "Default object";
    m_thumbnail = "";
    m_quest_type = QType::QT_TALK;
}

Quest::Quest(Object *object, std::string title, std::string context, std::string fin_context, QString thumbnail, bool is_main)
{
    m_is_active = true; // don't forget to set all other quests to inactive
    m_is_main_quest = is_main;
    m_is_claimed = false;
    m_is_prepared = false;
    m_is_completed = false;
    m_is_previewed = false;
    m_title = title;
    m_context = context;
    m_fin_context = fin_context;
    m_source = object;
    m_target = nullptr;
    m_price = nullptr;
    m_quest_object_name = "Default object";
    m_thumbnail = thumbnail;
    m_quest_type = QType::QT_TALK;
}

Quest::~Quest()
{

}

void Quest::setPrepared()
{
    m_is_prepared = true;
    emit preparedStatusChanged();
}

void Quest::setNonPrepared() // for example if dropped quest item or killed entity which shouldn't be killed
{
    m_is_prepared = false;
    emit preparedStatusChanged();
}
#include <iostream>
void Quest::setActive()
{
    m_is_active = true;
    if (m_is_prepared)
    {
        m_source->setQuestState(Object::QuestStatus::QS_PREPARED);
    }
    //eventChangeObjectQuestState();
    emit statusChanged();
}

void Quest::setInactive()
{
    m_is_active = false;
    m_source->setQuestState(Object::QuestStatus::QS_NONE);
    emit statusChanged();
}

void Quest::setAsClaimed()
{
    m_is_claimed = true;
    emit claimedStatusChanged();
}

void Quest::enablePreview()
{
    m_is_previewed = true;
    emit previewStatusChanged();
}

void Quest::disablePreview()
{
    m_is_previewed = false;
    emit previewStatusChanged();
}

bool Quest::isClaimed()
{
    return m_is_claimed;
}

bool Quest::isPrepared()
{
    return m_is_prepared;
}

bool Quest::isPreviewed()
{
    return m_is_previewed;
}

bool Quest::getStatus()
{
    return m_is_active;
}

bool Quest::getType()
{
    return m_is_main_quest;
}

QString Quest::getTitle()
{
    return QString::fromStdString(m_title);
}

QString Quest::getContext()
{
    return QString::fromStdString(m_context);
}

QString Quest::getFinContext()
{
    return QString::fromStdString(m_fin_context);
}

void Quest::disableObjectQuestState()
{
    m_source->setQuestState(Object::QuestStatus::QS_NONE);
}

bool Quest::isRequiredObject(const Object *obj)
{
    if (!m_target) // if misused this function when quest has not object pointer as target
    { return false; }
    return m_target == obj;
}

bool Quest::isRequiredObject(std::string target)
{
    return m_quest_object_name == target;
}

bool Quest::isSourceObject(const Object *obj)
{
    return obj == m_source;
}

void Quest::setTargetObject(Object *target)
{
    m_target = target;
    emit targetChanged();
}

bool Quest::isTargetObjectPresent()
{
    return m_target;
}
#if 1
QVariant Quest::getTarget()
{
    if (!m_is_prepared)
    {
        return QVariant::fromValue(m_target);
    }
    // if is prepared, get source to get position back to source
    return QVariant::fromValue(m_source);
}
#endif
void Quest::setTargetName(std::string target)
{
    m_quest_object_name = target;
}

void Quest::setPrice(Object *price)
{
    m_price = price;
}

Object *Quest::getPrice()
{
    return m_price;
}

float Quest::getAngleToTarget()
{
#if 0
    if (!m_target)
    { return 0.0F; }

    Vec2f player_pos = GameEngine::getPlayer()->m_pos;
    Vec2f target_pos = m_target->m_pos;
    Vec2f dist = target_pos - player_pos;
    return (std::atan2(dist.y, dist.x) * 180.0F) / M_PI;
#endif
    return 0.0F;
}
#if 0
void Quest::fixButtons()
{
    emit statusChanged();
    emit claimedStatusChanged();
    emit preparedStatusChanged();
    emit previewStatusChanged();
}
#endif
#include <iostream>
void Quest::DEBUGprintAllStates()
{
    std::cout << "\nm_is_active: " << m_is_active
              << "\nm_is_main_quest: " << m_is_main_quest
              << "\nm_is_claimed: " << m_is_claimed
              << "\nm_is_prepared: " << m_is_prepared
              << "\nm_is_completed: " << m_is_completed
              << "\nm_is_previewed: " << m_is_previewed
              << std::endl;
}

void Quest::refreshSourceState()
{
    if (m_is_prepared)
    {
        m_source->setQuestState(Object::QuestStatus::QS_PREPARED);
        return;
    }

    m_source->setQuestState(Object::QuestStatus::QS_NONE);
}

void Quest::setQuestType(QType type)
{
    m_quest_type = type;
}

// Examples: if killed but quest was talk then false (engine knows to delete quest)
bool Quest::actionMatch(QType type)
{
    return type == m_quest_type;
}
