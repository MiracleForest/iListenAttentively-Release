#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>
#include <mc/common/ActorUniqueID.h>

namespace ila::mc::inline player
{
class PlayerOpenContainerBeforeEvent final
    : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    BlockPos&      mPos;
    ContainerID&   mContainerId;
    ContainerType& mContainerType;
    ActorUniqueID& mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerBeforeEvent(
        ServerPlayer&  player,
        BlockPos&      pos,
        ContainerID&   containerId,
        ContainerType& containerType,
        ActorUniqueID& containerActorId
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

    ILNDAPI BlockPos&      getContainerBlockPos() const;
    ILNDAPI ContainerID&   getContainerId() const;
    ILNDAPI ContainerType& getContainerType() const;
    ILNDAPI ActorUniqueID& getContainerActorId() const;
};

class PlayerOpenContainerAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    BlockPos const&      mPos;
    ContainerID const&   mContainerId;
    ContainerType const& mContainerType;
    ActorUniqueID const& mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerAfterEvent(
        ServerPlayer&        player,
        BlockPos const&      pos,
        ContainerID const&   containerId,
        ContainerType const& containerType,
        ActorUniqueID const& containerActorId
    )
        : ServerPlayerEvent(player)
        , mPos(pos)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mContainerActorId(containerActorId)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const&      getContainerBlockPos() const;
    ILNDAPI ContainerID const&   getContainerId() const;
    ILNDAPI ContainerType const& getContainerType() const;
    ILNDAPI ActorUniqueID const& getContainerActorId() const;
};
} // namespace ila::mc::inline player