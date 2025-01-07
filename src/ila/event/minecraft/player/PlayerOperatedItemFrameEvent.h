#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{

namespace PlayerOperatedItemFrameEvent
{
    enum class Type
    {
        Place,
        Take,
        Rotate
    };
}; // namespace PlayerOperatedItemFrameEvent

class PlayerOperatedItemFrameBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    BlockPos const&                          mBlockPos;
    PlayerOperatedItemFrameEvent::Type const mType;

public:
    constexpr explicit PlayerOperatedItemFrameBeforeEvent(
        Player&                            player,
        BlockPos const&                    blockPos,
        PlayerOperatedItemFrameEvent::Type type
    )
        : Cancellable(player)
        , mBlockPos(blockPos)
        , mType(type)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getBlockPos() const;
    ILNDAPI PlayerOperatedItemFrameEvent::Type const& getType() const;
};

class PlayerOperatedItemFrameAfterEvent final : public ll::event::PlayerEvent
{
protected:
    BlockPos const&                           mBlockPos;
    PlayerOperatedItemFrameEvent::Type const& mType;

public:
    constexpr explicit PlayerOperatedItemFrameAfterEvent(
        Player&                                   player,
        BlockPos const&                           blockPos,
        PlayerOperatedItemFrameEvent::Type const& type
    )
        : PlayerEvent(player)
        , mBlockPos(blockPos)
        , mType(type)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getBlockPos() const;
    ILNDAPI PlayerOperatedItemFrameEvent::Type const& getType() const;
};
} // namespace ila::mc::inline world