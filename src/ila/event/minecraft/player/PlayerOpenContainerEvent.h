#include "ila/Global.h"

namespace ila::mc::inline player
{
class PlayerOpenContainerBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos&      mPos;
    ContainerID&   mContainerId;
    ContainerType& mContainerType;
    ActorUniqueID& mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerBeforeEvent(
        Player&        player,
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

    ILAPI BlockPos&      getContainerBlockPos() const;
    ILAPI ContainerID&   getContainerId() const;
    ILAPI ContainerType& getContainerType() const;
    ILAPI ActorUniqueID& getContainerActorId() const;
};

class PlayerOpenContainerAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const&      mPos;
    ContainerID const&   mContainerId;
    ContainerType const& mContainerType;
    ActorUniqueID const& mContainerActorId;

public:
    constexpr explicit PlayerOpenContainerAfterEvent(
        Player&              player,
        BlockPos const&      pos,
        ContainerID const&   containerId,
        ContainerType const& containerType,
        ActorUniqueID const& containerActorId
    )
        : PlayerEvent(player)
        , mPos(pos)
        , mContainerId(containerId)
        , mContainerType(containerType)
        , mContainerActorId(containerActorId)
    {
    }

    ILAPI BlockPos const&      getContainerBlockPos() const;
    ILAPI ContainerID const&   getContainerId() const;
    ILAPI ContainerType const& getContainerType() const;
    ILAPI ActorUniqueID const& getContainerActorId() const;
};
} // namespace ila::mc::inline player