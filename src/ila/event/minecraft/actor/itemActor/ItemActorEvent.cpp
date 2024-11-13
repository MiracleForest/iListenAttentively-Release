#include "ItemActorEvent.h"
#include <mc/nbt/CompoundTag.h>

namespace ila::event::inline actor
{
ItemActor& ItemActorEvent::self() const { return mSelf; }

void ItemActorEvent::serialize(CompoundTag& nbt) const
{
    Event::serialize(nbt);
    nbt["self"] = (uintptr_t)&self();
}

} // namespace ila::event::inline actor