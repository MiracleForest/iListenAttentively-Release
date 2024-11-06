#include "Global.h"
#include <mc/world/actor/player/Player.h>

namespace ila::inline player
{
class PlayerInteractEntityBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    Actor& mTarget;
    Vec3&  mPos;

public:
    constexpr explicit PlayerInteractEntityBeforeEvent(Player& player, Actor& target, Vec3& pos)
        : Cancellable(player)
        , mTarget(target)
        , mPos(pos)
    {
    }

    Actor& getTarget() const { return mTarget; };
    Vec3&  getPos() const { return mPos; };
};

class PlayerInteractEntityAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    Actor const& mTarget;
    Vec3 const&  mPos;
    bool&        mResult;

public:
    constexpr explicit PlayerInteractEntityAfterEvent(
        Player&      player,
        Actor const& target,
        Vec3 const&  pos,
        bool&        result
    )
        : PlayerEvent(player)
        , mTarget(target)
        , mPos(pos)
        , mResult(result)
    {
    }

    Actor const& getTarget() const { return mTarget; };
    Vec3 const&  getPos() const { return mPos; };
    bool&        getResult() const { return mResult; };
};
} // namespace ila::inline player