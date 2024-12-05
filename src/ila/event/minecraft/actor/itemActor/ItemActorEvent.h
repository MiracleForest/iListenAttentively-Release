#include "ila/Global.h"
#include <ll/api/event/Event.h>
#include <mc/world/actor/item/ItemActor.h>

namespace ila::event::inline actor::itemActor
{

class ItemActorEvent : public ll::event::Event
{
protected:
    ItemActor& mSelf;

public:
    constexpr explicit ItemActorEvent(ItemActor& actor)
        : mSelf(actor)
    {
    }

    [[maybe_unused]] ILAPI void serialize(CompoundTag&) const override;

    [[nodiscard]] ILAPI ItemActor& self() const;
};
} // namespace ila::event::inline actor::itemActor