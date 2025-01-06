#include "ila/event/minecraft/actor/DeathMessageEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/common/ActorUniqueID.h>
#include <mc/nbt/CompoundTagVariant.h>
#include <mc/world/actor/ActorDamageByActorSource.h>
#include <mc/world/actor/ActorDamageByBlockSource.h>
#include <mc/world/actor/ActorDamageByChildActorSource.h>

namespace ila::mc::inline actor
{

using DEATH_MESSAGE = std::pair<std::string, std::vector<std::string>>;

void DeathMessageBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["sourceUniqueId"] = getDamageSource().getEntityUniqueID().rawID;
    nbt["cause"]          = magic_enum::enum_name(getDamageSource().getCause());
    nbt["result"]         = { { "key", getResult().first }, { "params", ListTag {} } };
    for (auto& param : getResult().second) { nbt["result"]["params"].push_back(param); }
}
void DeathMessageBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getResult().first = nbt["result"]["key"];
    for (auto& param : nbt["result"]["params"].get<ListTag>()) { getResult().second.push_back(param); }
}
ActorDamageSource& DeathMessageBeforeEvent::getDamageSource() const { return mDamageSource; }
DEATH_MESSAGE&     DeathMessageBeforeEvent::getResult() const { return mResult; }

void DeathMessageAfterEvent::serialize(CompoundTag& nbt) const
{
    ActorEvent::serialize(nbt);
    nbt["sourceUniqueId"] = getDamageSource().getEntityUniqueID().rawID;
    nbt["cause"]          = magic_enum::enum_name(getDamageSource().getCause());
    nbt["result"]         = { { "key", getResult().first }, { "params", ListTag {} } };
    for (auto& param : getResult().second) { nbt["result"]["params"].push_back(param); }
}
ActorDamageSource const& DeathMessageAfterEvent::getDamageSource() const { return mDamageSource; }
DEATH_MESSAGE const&     DeathMessageAfterEvent::getResult() const { return mResult; }

#define DeathMessageHookMacro(name, type)                                                                    \
    LL_TYPE_INSTANCE_HOOK(                                                                                   \
        name,                                                                                                \
        HookPriority::Normal,                                                                                \
        type,                                                                                                \
        &type::$getDeathMessage,                                                                             \
        DEATH_MESSAGE,                                                                                       \
        std::string pDeadName,                                                                               \
        Actor*      pDeadActor                                                                               \
    )                                                                                                        \
    {                                                                                                        \
        auto result = origin(pDeadName, pDeadActor);                                                         \
        if (pDeadActor == nullptr || result.first.empty()) { return result; }                                \
        auto beforeEvent = DeathMessageBeforeEvent(*pDeadActor, *this, result);                              \
        LLEventBus.publish(beforeEvent);                                                                     \
        if (beforeEvent.isCancelled()) { return DEATH_MESSAGE(); }                                           \
        LLEventBus.publish(DeathMessageAfterEvent(*pDeadActor, *this, result));                              \
        return result;                                                                                       \
    }

DeathMessageHookMacro(DeathMessageEventHook1, ActorDamageSource);

DeathMessageHookMacro(DeathMessageEventHook2, ActorDamageByActorSource);

DeathMessageHookMacro(DeathMessageEventHook3, ActorDamageByBlockSource);

DeathMessageHookMacro(DeathMessageEventHook4, ActorDamageByChildActorSource);

Event_Hook_Factory(DeathMessage, <DeathMessageEventHook1, DeathMessageEventHook2, DeathMessageEventHook3, DeathMessageEventHook4>);

} // namespace ila::mc::inline actor