#include "Global.h"

namespace ila::inline actor
{
class DragonRespawnBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
public:
    constexpr explicit DragonRespawnBeforeEvent()
        : Cancellable()
    {
    }
};

class DragonRespawnAfterEvent final : public ll::event::Event
{
public:
    constexpr explicit DragonRespawnAfterEvent() {}
};
} // namespace ila::inline actor