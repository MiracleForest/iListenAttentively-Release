#include "DeathMessageEvent.h"
#include <mc/world/actor/ActorDamageByActorSource.h>
#include <mc/world/actor/ActorDamageByBlockSource.h>
#include <mc/world/actor/ActorDamageByChildActorSource.h>

namespace ila::inline actor
{

using DEATH_MESSAGE = std::pair<std::string, std::vector<std::string>>;

ActorDamageSource& DeathMessageBeforeEvent::getDamageSource() const { return mDamageSource; }

ActorDamageSource const& DeathMessageAfterEvent::getDamageSource() const { return mDamageSource; }
DEATH_MESSAGE&           DeathMessageAfterEvent::getResult() { return mResult; }

#define DeathMessageHookMacro(name, type, symbol)                                                            \
    LL_TYPE_INSTANCE_HOOK(                                                                                   \
        name,                                                                                                \
        HookPriority::Normal,                                                                                \
        type,                                                                                                \
        symbol,                                                                                              \
        DEATH_MESSAGE,                                                                                       \
        std::string pDeadName,                                                                               \
        Actor*      pDeadActor                                                                               \
    )                                                                                                        \
    {                                                                                                        \
        if (pDeadActor == nullptr) return origin(pDeadName, pDeadActor);                                     \
        auto beforeEvent = DeathMessageBeforeEvent(*pDeadActor, *this);                                      \
        eventBus.publish(beforeEvent);                                                                       \
        if (beforeEvent.isCancelled()) return DEATH_MESSAGE();                                               \
        auto result = origin(pDeadName, pDeadActor);                                                         \
        eventBus.publish(DeathMessageAfterEvent(*pDeadActor, *this, result));                                \
        return result;                                                                                       \
    }

DeathMessageHookMacro(
    DeathMessageEventHook1,
    ActorDamageSource,
    "?getDeathMessage@ActorDamageSource@@UEBA?AU?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@"
    "2@@std@@V?"
    "$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$"
    "char_"
    "traits@D@std@@V?$allocator@D@2@@std@@@2@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@"
    "2@@3@"
    "PEAVActor@@@Z"
);

DeathMessageHookMacro(
    DeathMessageEventHook2,
    ActorDamageByActorSource,
    "?getDeathMessage@ActorDamageByActorSource@@UEBA?AU?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@D@2@@"
    "std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_"
    "string@DU?$"
    "char_traits@D@std@@V?$allocator@D@2@@std@@@2@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@D@2@@3@"
    "PEAVActor@@@Z"
);

DeathMessageHookMacro(
    DeathMessageEventHook3,
    ActorDamageByBlockSource,
    "?getDeathMessage@ActorDamageByBlockSource@@UEBA?AU?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@D@2@@"
    "std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_"
    "string@DU?$"
    "char_traits@D@std@@V?$allocator@D@2@@std@@@2@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@D@2@@3@"
    "PEAVActor@@@Z"
);

DeathMessageHookMacro(
    DeathMessageEventHook4,
    ActorDamageByChildActorSource,
    "?getDeathMessage@ActorDamageByChildActorSource@@UEBA?AU?$pair@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@"
    "D@2@@std@@V?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_"
    "string@DU?"
    "$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@2@@std@@V?$basic_string@DU?$char_traits@D@std@@V?$"
    "allocator@D@2@@3@"
    "PEAVActor@@@Z"
);

Event_Factory(DeathMessage, <DeathMessageEventHook1, DeathMessageEventHook2, DeathMessageEventHook3, DeathMessageEventHook4>);

} // namespace ila::inline actor