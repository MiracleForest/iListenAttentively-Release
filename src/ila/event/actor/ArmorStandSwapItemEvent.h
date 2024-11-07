#include "Global.h"

namespace ila::inline actor
{
class ArmorStandSwapItemBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Player&                     mPlayer;
    Puv::Legacy::EquipmentSlot& mSlot;

public:
    constexpr explicit ArmorStandSwapItemBeforeEvent(
        Actor&                      acotr,
        Player&                     player,
        Puv::Legacy::EquipmentSlot& slot
    )
        : Cancellable(acotr)
        , mPlayer(player)
        , mSlot(slot)
    {
    }

    ILAPI Player& getPlayer() const { return mPlayer; }
    ILAPI Puv::Legacy::EquipmentSlot& getSlot() const { return mSlot; }
};

class ArmorStandSwapItemAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    Player const&                     mPlayer;
    Puv::Legacy::EquipmentSlot const& mSlot;
    bool&                             mResult;

public:
    constexpr explicit ArmorStandSwapItemAfterEvent(
        Actor&                            acotr,
        Player const&                     player,
        Puv::Legacy::EquipmentSlot const& slot,
        bool&                             result
    )
        : ActorEvent(acotr)
        , mPlayer(player)
        , mSlot(slot)
        , mResult(result)
    {
    }

    ILAPI Player const& getPlayer() const { return mPlayer; }
    ILAPI Puv::Legacy::EquipmentSlot const& getSlot() const { return mSlot; }
    ILAPI bool&                             getResult() const { return mResult; }
};
} // namespace ila::inline actor