#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerChangGameTypeBeforeEvent final
    : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    GameType const& mOldGameType;
    GameType&       mNewGameType;

public:
    constexpr explicit PlayerChangGameTypeBeforeEvent(
        ServerPlayer&   player,
        GameType const& oldGameType,
        GameType&       newGameType
    )
        : Cancellable(player)
        , mOldGameType(oldGameType)
        , mNewGameType(newGameType)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI GameType const& oldGameType() const;
    ILNDAPI GameType&       newGameType() const;
};

class PlayerChangGameTypeAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    GameType const& mOldGameType;
    GameType const& mNewGameType;

public:
    constexpr explicit PlayerChangGameTypeAfterEvent(
        ServerPlayer&   player,
        GameType const& oldGameType,
        GameType const& newGameType
    )
        : ServerPlayerEvent(player)
        , mOldGameType(oldGameType)
        , mNewGameType(newGameType)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI GameType const& oldGameType() const;
    ILNDAPI GameType const& newGameType() const;
};
} // namespace ila::mc::inline world::inline actor::inline player