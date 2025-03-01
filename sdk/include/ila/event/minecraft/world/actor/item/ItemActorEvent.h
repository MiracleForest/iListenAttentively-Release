#include "ila/base/Macro.h"
#include <ll/api/event/entity/ActorEvent.h>
#include <mc/world/actor/item/ItemActor.h>

namespace ila::event::inline actor::itemActor
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

} // namespace ila::event::inline actor::itemActor