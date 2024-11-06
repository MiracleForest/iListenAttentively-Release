#include "Global.h"

namespace ila::inline player
{
class PlayerChangGameTypeBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    GameType& mGameType;

public:
    constexpr explicit PlayerChangGameTypeBeforeEvent(Player& player, GameType& gameType)
        : Cancellable(player)
        , mGameType(gameType)
    {
    }

    GameType& getGameType() const { return mGameType; };
};

class PlayerChangGameTypeAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    GameType const& mGameType;

public:
    constexpr explicit PlayerChangGameTypeAfterEvent(Player& player, GameType const& gameType)
        : PlayerEvent(player)
        , mGameType(gameType)
    {
    }

    GameType const& getGameType() const { return mGameType; };
};
} // namespace ila::inline player