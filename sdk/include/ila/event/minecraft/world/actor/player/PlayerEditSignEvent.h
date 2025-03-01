#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/ServerPlayerEvent.h>
#include <mc/nbt/CompoundTagVariant.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/block/actor/SignTextSide.h>

namespace ila::mc::inline player
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

    ILNDAPI BlockPos&           getPos() const;
    ILNDAPI StringTag&          getText() const;
    ILNDAPI SignTextSide const& getTextSide() const;
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

    ILNDAPI StringTag const&    getText() const;
    ILNDAPI SignTextSide const& getTextSide() const;
    ILNDAPI BlockPos const&     getPos() const;
};
} // namespace ila::mc::inline player