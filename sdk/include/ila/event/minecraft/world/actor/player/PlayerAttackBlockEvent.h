#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>
#include <mc/common/FacingID.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline player
{
class PlayerAttackBlockBeforeEvent final : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    BlockPos& mPos;
    FacingID& mFace;

public:
    constexpr explicit PlayerAttackBlockBeforeEvent(ServerPlayer& player, BlockPos& pos, FacingID& face)
        : Cancellable(player)
        , mPos(pos)
        , mFace(face)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI FacingID& getFace() const;
};

class PlayerAttackBlockAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    BlockPos const& mPos;
    FacingID const& mFace;

public:
    constexpr explicit PlayerAttackBlockAfterEvent(
        ServerPlayer&   player,
        BlockPos const& pos,
        FacingID const& face
    )
        : ServerPlayerEvent(player)
        , mPos(pos)
        , mFace(face)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI FacingID const& getFace() const;
};
} // namespace ila::mc::inline player