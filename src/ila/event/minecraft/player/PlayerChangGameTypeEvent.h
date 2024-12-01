#include "Global.h"

namespace ila::mc::inline player
{
class PlayerChangGameTypeBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    GameType const& mOldGameType;
    GameType&       mNewGameType;

public:
    constexpr explicit PlayerChangGameTypeBeforeEvent(
        Player&         player,
        GameType const& oldGameType,
        GameType&       newGameType
    )
        : Cancellable(player)
        , mOldGameType(oldGameType)
        , mNewGameType(newGameType)
    {
    }

    ILAPI GameType const& getOldGameType() const;
    ILAPI GameType&       getNewGameType() const;
};

class PlayerChangGameTypeAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    GameType const& mOldGameType;
    GameType const& mNewGameType;

public:
    constexpr explicit PlayerChangGameTypeAfterEvent(
        Player&         player,
        GameType const& oldGameType,
        GameType const& newGameType
    )
        : PlayerEvent(player)
        , mOldGameType(oldGameType)
        , mNewGameType(newGameType)
    {
    }

    ILAPI GameType const& getOldGameType() const;
    ILAPI GameType const& getNewGameType() const;
};
} // namespace ila::mc::inline player