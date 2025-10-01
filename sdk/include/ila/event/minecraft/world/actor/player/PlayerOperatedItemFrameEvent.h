#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
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
public:
    using Type = PlayerOperatedItemFrameEvent::Type;

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

    ILNDAPI BlockPos const& blockPos() const;
    ILNDAPI PlayerOperatedItemFrameEvent::Type const& type() const;
};

class PlayerOperatedItemFrameAfterEvent final : public ll::event::PlayerEvent
{
public:
    using Type = PlayerOperatedItemFrameEvent::Type;

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

    ILNDAPI BlockPos const& blockPos() const;
    ILNDAPI PlayerOperatedItemFrameEvent::Type const& type() const;
};
} // namespace ila::mc::inline world::inline actor::inline player