#include "Global.h"

namespace ila::mc::inline world
{
class RedstoneUpdateBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    int const       mStrength;

public:
    constexpr explicit RedstoneUpdateBeforeEvent(BlockSource& blockSource, BlockPos const& pos, int strength)
        : Cancellable(blockSource)
        , mPos(pos)
        , mStrength(strength)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI int const&      getStrength() const;
};

class RedstoneUpdateAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    int const       mStrength;

public:
    constexpr explicit RedstoneUpdateAfterEvent(BlockSource& blockSource, BlockPos const& pos, int strength)
        : WorldEvent(blockSource)
        , mPos(pos)
        , mStrength(strength)
    {
    }

    ILAPI BlockPos const& getPos() const;
    ILAPI int const&      getStrength() const;
};
} // namespace ila::mc::inline world