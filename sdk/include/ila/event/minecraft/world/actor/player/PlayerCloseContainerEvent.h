#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerCloseContainerBeforeEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    ContainerID&                        mContainerId;
    SharedTypes::Legacy::ContainerType& mContainerType;
    bool&                               mServerInitiatedClose;

public:
    constexpr explicit PlayerCloseContainerBeforeEvent(
        ServerPlayer&                       player,
        ContainerID&                        containerId,
        SharedTypes::Legacy::ContainerType& containerType,
        bool&                               serverInitiatedClose
    )
        : ServerPlayerEvent(player)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mServerInitiatedClose(serverInitiatedClose)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ContainerID& containerId() const;
    ILNDAPI SharedTypes::Legacy::ContainerType& containerType() const;
    ILNDAPI bool&                               serverInitiatedClose() const;
};

class PlayerCloseContainerAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    ContainerID const&                        mContainerId;
    SharedTypes::Legacy::ContainerType const& mContainerType;
    bool const&                               mServerInitiatedClose;

public:
    constexpr explicit PlayerCloseContainerAfterEvent(
        ServerPlayer&                             player,
        ContainerID const&                        containerId,
        SharedTypes::Legacy::ContainerType const& containerType,
        bool const&                               serverInitiatedClose
    )
        : ServerPlayerEvent(player)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mServerInitiatedClose(serverInitiatedClose)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ContainerID const& containerId() const;
    ILNDAPI SharedTypes::Legacy::ContainerType const& containerType() const;
    ILNDAPI bool const&                               serverInitiatedClose() const;
};
} // namespace ila::mc::inline world::inline actor::inline player