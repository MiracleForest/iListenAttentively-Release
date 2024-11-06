#include "Global.h"

namespace ila::inline player
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

    GameType const& getOldGameType() const { return mOldGameType; };
    GameType&       getNewGameType() const { return mNewGameType; };
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

    GameType const& getOldGameType() const { return mOldGameType; };
    GameType const& getNewGameType() const { return mNewGameType; };
};
} // namespace ila::inline player