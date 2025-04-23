#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/inventory/network/ItemStackRequestActionType.h>
#include <mc/world/inventory/network/ItemStackNetResult.h>

// clang-format off
struct ItemStackRequestSlotInfo;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerRequestItemActionBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    ItemStackRequestActionType& mActionType;
    bool&                       mIsDstSerialized;
    bool&                       mIsAmountSerialized;
    uchar&                      mAmount;
    ItemStackRequestSlotInfo&   mSrc;
    ItemStackRequestSlotInfo&   mDst;

public:
    constexpr explicit PlayerRequestItemActionBeforeEvent(
        Player&                     player,
        ItemStackRequestActionType& actionType,
        bool&                       isDstSerialized,
        bool&                       isAmountSerialized,
        uchar&                      amount,
        ItemStackRequestSlotInfo&   src,
        ItemStackRequestSlotInfo&   dst
    )
        : Cancellable(player)
        , mActionType(actionType)
        , mIsDstSerialized(isDstSerialized)
        , mIsAmountSerialized(isAmountSerialized)
        , mAmount(amount)
        , mSrc(src)
        , mDst(dst)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ItemStackRequestActionType& actionType() const;
    ILNDAPI bool&                       isDstSerialized() const;
    ILNDAPI bool&                       isAmountSerialized() const;
    ILNDAPI uchar&                      amount() const;
    ILNDAPI ItemStackRequestSlotInfo&   src() const;
    ILNDAPI ItemStackRequestSlotInfo&   dst() const;
};

class PlayerRequestItemActionAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    ItemStackRequestActionType const& mActionType;
    bool const&                       mIsDstSerialized;
    bool const&                       mIsAmountSerialized;
    uchar const&                      mAmount;
    ItemStackRequestSlotInfo const&   mSrc;
    ItemStackRequestSlotInfo const&   mDst;
    ItemStackNetResult&               mResult;

public:
    constexpr explicit PlayerRequestItemActionAfterEvent(
        Player&                           player,
        ItemStackRequestActionType const& actionType,
        bool const&                       isDstSerialized,
        bool const&                       isAmountSerialized,
        uchar const&                      amount,
        ItemStackRequestSlotInfo const&   src,
        ItemStackRequestSlotInfo const&   dst,
        ItemStackNetResult&               result
    )
        : PlayerEvent(player)
        , mActionType(actionType)
        , mIsDstSerialized(isDstSerialized)
        , mIsAmountSerialized(isAmountSerialized)
        , mAmount(amount)
        , mSrc(src)
        , mDst(dst)
        , mResult(result)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ItemStackRequestActionType const& actionType() const;
    ILNDAPI bool const&                       isDstSerialized() const;
    ILNDAPI bool const&                       isAmountSerialized() const;
    ILNDAPI uchar const&                      amount() const;
    ILNDAPI ItemStackRequestSlotInfo const&   src() const;
    ILNDAPI ItemStackRequestSlotInfo const&   dst() const;
    ILNDAPI ItemStackNetResult&               result() const;
};
} // namespace ila::mc::inline world::inline actor::inline player