#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

// clang-format off
class Container;
class ItemStack;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerChangeSlotEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    Container&       mContainer;
    int&             mSlot;
    ItemStack const& mOldItem;
    ItemStack const& mNewItem;
    bool&            mForceBalanced;

public:
    constexpr explicit PlayerChangeSlotEvent(
        Player&          pPlayer,
        Container&       pContainer,
        int&             pSlot,
        ItemStack const& pOldItem,
        ItemStack const& pNewItem,
        bool&            pForceBalanced
    )
        : ll::event::Cancellable<ll::event::player::PlayerEvent>(pPlayer)
        , mContainer(pContainer)
        , mSlot(pSlot)
        , mOldItem(pOldItem)
        , mNewItem(pNewItem)
        , mForceBalanced(pForceBalanced)
    {
    }

public:
    ILAPI void serialize(CompoundTag& pNbt) const override;

public:
    ILNDAPI Container&       container() const;
    ILNDAPI int&             slot() const;
    ILNDAPI ItemStack const& oldItem() const;
    ILNDAPI ItemStack const& newItem() const;
    ILNDAPI bool&            forceBalanced() const;
};
} // namespace ila::mc::inline world::inline actor::inline player