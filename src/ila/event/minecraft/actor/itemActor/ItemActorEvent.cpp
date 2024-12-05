#include "ila/event/minecraft/actor/itemActor/ItemActorEvent.h"
#include <mc/nbt/CompoundTag.h>

namespace ila::event::inline actor::itemActor
{
ItemActor& ItemActorEvent::self() const { return mSelf; }

void ItemActorEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["self"] = (uintptr_t)&self();
}

} // namespace ila::event::inline actor