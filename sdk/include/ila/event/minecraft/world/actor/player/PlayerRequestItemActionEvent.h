#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/inventory/network/ItemStackNetResult.h>
#include <mc/world/inventory/network/ItemStackRequestActionTransferBase.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerRequestItemActionBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    ItemStackRequestActionTransferBase& mRequestAction;

public:
    constexpr explicit PlayerRequestItemActionBeforeEvent(
        Player&                             player,
        ItemStackRequestActionTransferBase& requestAction
    )
        : Cancellable(player)
        , mRequestAction(requestAction)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ItemStackRequestActionTransferBase& requestAction() const;
};

class PlayerRequestItemActionAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    ItemStackRequestActionTransferBase const& mRequestAction;
    ItemStackNetResult&                       mResult;

public:
    constexpr explicit PlayerRequestItemActionAfterEvent(
        Player&                                   player,
        ItemStackRequestActionTransferBase const& requestAction,
        ItemStackNetResult&                       result
    )
        : PlayerEvent(player)
        , mRequestAction(requestAction)
        , mResult(result)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ItemStackRequestActionTransferBase const& requestAction() const;
    ILNDAPI ItemStackNetResult&                       result() const;
};
} // namespace ila::mc::inline world::inline actor::inline player