#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace land
{
class LandMemberChangeBeforeEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    std::string const& mTargetPlayer;
    uint64_t           mLandId;
    bool               mIsAdd;

public:
    constexpr explicit LandMemberChangeBeforeEvent(
        Player&            player,
        std::string const& targetPlayer,
        uint64_t           landID,
        bool               isAdd
    )
        : Cancellable(player)
        , mTargetPlayer(targetPlayer)
        , mLandId(landID)
        , mIsAdd(isAdd)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::string const& getTargetPlayer() const;
    ILNDAPI uint64_t           getLandId() const;
    ILNDAPI bool               getIsAdd() const;
};
class LandMemberChangeAfterEvent final : public ll::event::PlayerEvent
{
protected:
    std::string const& mTargetPlayer;
    uint64_t           mLandId;
    bool               mIsAdd;

public:
    constexpr explicit LandMemberChangeAfterEvent(
        Player&            player,
        std::string const& targetPlayer,
        uint64_t           landID,
        bool               isAdd
    )
        : PlayerEvent(player)
        , mTargetPlayer(targetPlayer)
        , mLandId(landID)
        , mIsAdd(isAdd)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI std::string const& getTargetPlayer() const;
    ILNDAPI uint64_t           getLandId() const;
    ILNDAPI bool               getIsAdd() const;
};

} // namespace land