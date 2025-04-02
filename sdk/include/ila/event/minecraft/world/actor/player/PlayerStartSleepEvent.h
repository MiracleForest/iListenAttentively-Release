#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/actor/player/BedSleepingResult.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerStartSleepBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit PlayerStartSleepBeforeEvent(Player& player, BlockPos& pos)
        : Cancellable(player)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pos() const;
};

class PlayerStartSleepAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const&    mPos;
    BedSleepingResult& mResult;

public:
    constexpr explicit PlayerStartSleepAfterEvent(
        Player&            player,
        BlockPos const&    pos,
        BedSleepingResult& result
    )
        : PlayerEvent(player)
        , mPos(pos)
        , mResult(result)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos const&    pos() const;
    ILNDAPI BedSleepingResult& result() const;
};
} // namespace ila::mc::inline world::inline actor::inline player