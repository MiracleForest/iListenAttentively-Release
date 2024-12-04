#include "Global.h"
#include "ll/api/event/Event.h"
#include "mc/world/actor/item/ItemActor.h"

namespace ila::event::inline actor
{

class ItemActorEvent : public ll::event::Event
{
    ItemActor& mSelf;

protected:
    constexpr explicit ItemActorEvent(ItemActor& actor)
        : mSelf(actor)
    {
    }

public:
    [[maybe_unused]] ILAPI void serialize(CompoundTag&) const override;

    [[nodiscard]] ILAPI ItemActor& self() const;
};
} // namespace ila::event::inline actor
