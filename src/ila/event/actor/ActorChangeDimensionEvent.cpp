#include "ActorChangeDimensionEvent.h"

namespace ila::inline actor
{

DimensionType const& ActorChangeDimensionBeforeEvent::getFromDimensionId() const { return mFromDimensionId; };
DimensionType&       ActorChangeDimensionBeforeEvent::getToDimensionId() const { return mToDimensionId; };

DimensionType const& ActorChangeDimensionAfterEvent::getFromDimensionId() const { return mFromDimensionId; };
DimensionType const& ActorChangeDimensionAfterEvent::getToDimensionId() const { return mToDimensionId; };

LL_TYPE_INSTANCE_HOOK(
    ActorChangeDimensionEventHook,
    HookPriority::Normal,
    Level,
    &Level::entityChangeDimension,
    void,
    Actor&              pActor,
    DimensionType       pToId,
    std::optional<Vec3> pActorPos
)
{
    auto formId      = pActor.getDimensionId();
    auto beforeEvent = ActorChangeDimensionBeforeEvent(pActor, formId, pToId);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pActor, pToId, pActorPos);
    eventBus.publish(ActorChangeDimensionAfterEvent(pActor, formId, pToId));
}

Event_Factory(ActorChangeDimension, <ActorChangeDimensionEventHook>);

} // namespace ila::inline actor