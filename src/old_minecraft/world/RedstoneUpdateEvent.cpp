#include "ila/event/minecraft/world/RedstoneUpdateEvent.h"
#include <mc/world/redstone/circuit/CircuitSystem.h>

namespace ila::mc::inline world
{

BlockPos const& RedstoneUpdateBeforeEvent::getPos() const { return mPos; }
int const&      RedstoneUpdateBeforeEvent::getStrength() const { return mStrength; }

BlockPos const& RedstoneUpdateAfterEvent::getPos() const { return mPos; }
int const&      RedstoneUpdateAfterEvent::getStrength() const { return mStrength; }

// LL_TYPE_INSTANCE_HOOK(
//     RedstoneUpdateEventHook,
//     HookPriority::Normal,
//     CircuitSystem,
//     &CircuitSystem::updateIndividualBlock,
//     void,
//     gsl::not_null<BaseCircuitComponent*> pComponent,
//     BlockPos const&                      pChunkPos,
//     BlockPos const&                      pPos,
//     BlockSource&                         pRegion
// )
// {
//     auto beforeEvent = RedstoneUpdateBeforeEvent(pRegion, pPos, pComponent->getStrength());
//     eventBus.publish(beforeEvent);
//     if (beforeEvent.isCancelled()) return;
//     origin(pComponent, pChunkPos, pPos, pRegion);
//     eventBus.publish(RedstoneUpdateAfterEvent(pRegion, pPos, pComponent->getStrength()));
// }

// Event_Factory(RedstoneUpdate, <RedstoneUpdateEventHook>);

} // namespace ila::mc::inline world