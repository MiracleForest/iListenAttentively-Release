#include "ila/base/Macro.h"
#include <ll/api/event/entity/ActorEvent.h>
#include <mc/world/actor/item/ItemActor.h>

namespace ila::mc::inline world::inline actor::inline item
{

class ItemActorEvent : public ll::event::ActorEvent
{
public:
    constexpr explicit ItemActorEvent(ItemActor& actor)
        : ActorEvent(actor)
    {
    }

    void serialize(CompoundTag&) const override;

    ILNDAPI ItemActor& self() const;
};

} // namespace ila::mc::inline world::inline actor::inline item