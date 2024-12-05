#include "ila/Global.h"

namespace ila::mc::inline level
{
class LevelTickBeforeEvent final : public ll::event::Cancellable<ll::event::LevelEvent>
{
public:
    constexpr explicit LevelTickBeforeEvent(Level& level)
        : Cancellable(level)
    {
    }
};

class LevelTickAfterEvent final : public ll::event::LevelEvent
{
public:
    constexpr explicit LevelTickAfterEvent(Level& level)
        : LevelEvent(level)
    {
    }
};
} // namespace ila::mc::inline level