#include "Global.h"

namespace ila::mc::inline player
{
class PlayerAttackBlockBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit PlayerAttackBlockBeforeEvent(Player& player, BlockPos const& pos)
        : Cancellable(player)
        , mPos(pos)
    {
    }

    ILAPI BlockPos const& getPos() const;
};

class PlayerAttackBlockAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const& mPos;
    bool&           mResult;

public:
    constexpr explicit PlayerAttackBlockAfterEvent(Player& player, BlockPos const& pos, bool& result)
        : PlayerEvent(player)
        , mPos(pos)
        , mResult(result)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI bool&           getResult() const;
};
} // namespace ila::mc::inline player