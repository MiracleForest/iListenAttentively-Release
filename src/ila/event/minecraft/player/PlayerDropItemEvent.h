#include "Global.h"

namespace ila::mc::inline player
{
class PlayerDropItemBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    ItemStack const& mItem;

public:
    constexpr explicit PlayerDropItemBeforeEvent(Player& player, ItemStack const& item)
        : Cancellable(player)
        , mItem(item)
    {
    }

    ILAPI ItemStack const& getItem() const;
};

class PlayerDropItemAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    ItemStack const& mItem;
    bool             mResult;

public:
    constexpr explicit PlayerDropItemAfterEvent(Player& player, ItemStack const& item, bool const result)
        : PlayerEvent(player)
        , mItem(item)
        , mResult(result)
    {
    }

    ILAPI ItemStack const& getItem() const;
    ILAPI bool             getResult() const;
};
} // namespace ila::mc::inline player