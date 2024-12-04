#include "Global.h"

namespace ila::mc::inline player
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

    ILAPI Actor& getTarget() const;
    ILAPI Vec3&  getPos() const;
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

    ILAPI Actor const& getTarget() const;
    ILAPI Vec3 const&  getPos() const;
    ILAPI bool&        getResult() const;
};
} // namespace ila::mc::inline player