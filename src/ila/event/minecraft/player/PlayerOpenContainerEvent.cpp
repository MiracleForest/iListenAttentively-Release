#include "PlayerOpenContainerEvent.h"
#include <mc/server/module/VanillaServerGameplayEventListener.h>

namespace ila::mc::inline player
{

BlockPos const& PlayerOpenContainerBeforeEvent::getContainerBlockPos() const { return mPos; }

BlockPos const& PlayerOpenContainerAfterEvent::getContainerBlockPos() const { return mPos; }
EventResult&    PlayerOpenContainerAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PlayerOpenContainerEventHook,
    HookPriority::Normal,
    VanillaServerGameplayEventListener,
    &VanillaServerGameplayEventListener::onEvent,
    EventResult,
    PlayerOpenContainerEvent const& pPlayerOpenContainerEvent
)
{
    auto actor = ((WeakEntityRef&)pPlayerOpenContainerEvent).tryUnwrap<Actor>();
    if (!actor.has_value() || !actor->isPlayer()) return origin(pPlayerOpenContainerEvent);
    auto beforeEvent = PlayerOpenContainerBeforeEvent(
        (Player&)*actor,
        ll::memory::dAccess<BlockPos>(&pPlayerOpenContainerEvent, 28)
    );
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return EventResult::StopProcessing;
    auto result = origin(pPlayerOpenContainerEvent);
    eventBus.publish(PlayerOpenContainerAfterEvent(
        (Player&)*actor,
        ll::memory::dAccess<BlockPos>(&pPlayerOpenContainerEvent, 28),
        result
    ));
    return origin(pPlayerOpenContainerEvent);
}

Event_Factory(PlayerOpenContainer, <PlayerOpenContainerEventHook>);

} // namespace ila::mc::inline player