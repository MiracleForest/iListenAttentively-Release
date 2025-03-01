#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>
#include <mc/legacy/ActorUniqueID.h>

namespace ila::mc::inline player
{
class PlayerOpenContainerBeforeEvent final
    : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    BlockPos&                           mPos;
    ContainerID&                        mContainerId;
    SharedTypes::Legacy::ContainerType& mContainerType;
    ActorUniqueID&                      mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerBeforeEvent(
        ServerPlayer&                       player,
        BlockPos&                           pos,
        ContainerID&                        containerId,
        SharedTypes::Legacy::ContainerType& containerType,
        ActorUniqueID&                      containerActorId
    )
        : Cancellable(player)
        , mPos(pos)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mContainerActorId(containerActorId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos&    getContainerBlockPos() const;
    ILNDAPI ContainerID& getContainerId() const;
    ILNDAPI SharedTypes::Legacy::ContainerType& getContainerType() const;
    ILNDAPI ActorUniqueID&                      getContainerActorId() const;
};

class PlayerOpenContainerAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    BlockPos const&                           mPos;
    ContainerID const&                        mContainerId;
    SharedTypes::Legacy::ContainerType const& mContainerType;
    ActorUniqueID const&                      mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerAfterEvent(
        ServerPlayer&                             player,
        BlockPos const&                           pos,
        ContainerID const&                        containerId,
        SharedTypes::Legacy::ContainerType const& containerType,
        ActorUniqueID const&                      containerActorId
    )
        : ServerPlayerEvent(player)
        , mPos(pos)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mContainerActorId(containerActorId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const&    getContainerBlockPos() const;
    ILNDAPI ContainerID const& getContainerId() const;
    ILNDAPI SharedTypes::Legacy::ContainerType const& getContainerType() const;
    ILNDAPI ActorUniqueID const&                      getContainerActorId() const;
};
} // namespace ila::mc::inline player