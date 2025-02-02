#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline player
{
class PlayerAttackBlockBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit PlayerAttackBlockBeforeEvent(Player& player, BlockPos& pos)
        : Cancellable(player)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
};

class PlayerAttackBlockAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit PlayerAttackBlockAfterEvent(Player& player, BlockPos const& pos)
        : PlayerEvent(player)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
};
} // namespace ila::mc::inline player