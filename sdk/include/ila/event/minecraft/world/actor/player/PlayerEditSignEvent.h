#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <mc/world/level/block/actor/SignTextSide.h>
#include <ll/api/event/player/ServerPlayerEvent.h>

// clang-format off
class BlockPos;
class StringTag;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerEditSignBeforeEvent final : public ll::event::Cancellable<ll::event::player::ServerPlayerEvent>
{
protected:
    BlockPos&           mPos;
    StringTag&          mText;
    SignTextSide const& mTextSide;

public:
    constexpr explicit PlayerEditSignBeforeEvent(
        ServerPlayer&       player,
        BlockPos&           pos,
        StringTag&          text,
        SignTextSide const& textSide
    )
        : Cancellable(player)
        , mPos(pos)
        , mText(text)
        , mTextSide(textSide)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos&           pos() const;
    ILNDAPI StringTag&          text() const;
    ILNDAPI SignTextSide const& textSide() const;
};

class PlayerEditSignAfterEvent final : public ll::event::player::ServerPlayerEvent
{
protected:
    BlockPos const&     mPos;
    StringTag const&    mText;
    SignTextSide const& mTextSide;

public:
    constexpr explicit PlayerEditSignAfterEvent(
        ServerPlayer&       player,
        BlockPos const&     pos,
        StringTag const&    text,
        SignTextSide const& textSide
    )
        : ServerPlayerEvent(player)
        , mPos(pos)
        , mText(text)
        , mTextSide(textSide)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI StringTag const&    text() const;
    ILNDAPI SignTextSide const& textSide() const;
    ILNDAPI BlockPos const&     pos() const;
};
} // namespace ila::mc::inline world::inline actor::inline player