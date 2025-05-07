#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>

// Warning:
// When a player joins the server, if existing player data is found in the save file,
// the server will load the player data and trigger this event.
// However, member variables such as the player"s dimension are not yet initialized at this stage.
// You need to implement custom checks accordingly.

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerChangeGameTypeBeforeEvent final
    : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    GameType const& mOldGameType;
    GameType&       mNewGameType;

public:
    constexpr explicit PlayerChangeGameTypeBeforeEvent(
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

class PlayerChangeGameTypeAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    GameType const& mOldGameType;
    GameType const& mNewGameType;

public:
    constexpr explicit PlayerChangeGameTypeAfterEvent(
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