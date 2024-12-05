#include "ila/Global.h"
#include <mc/world/inventory/network/ItemStackRequestActionTransferBase.h>
#include <mc/world/item/components/ItemStackNetResult.h>

namespace ila::mc::inline player
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

    ILAPI ItemStackRequestActionTransferBase& getRequestAction() const;
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

    ILAPI ItemStackRequestActionTransferBase const& getRequestAction() const;
    ILAPI ItemStackNetResult&                       getResult() const;
};
} // namespace ila::mc::inline player