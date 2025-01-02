#include "ila/Global.h"
#include <mc/world/level/block/actor/SignTextSide.h>
#include <mc/nbt/CompoundTagVariant.h>

namespace ila::mc::inline player
{
class PlayerEditSignBeforeEvent final : public ll::event::Cancellable<ll::event::player::PlayerEvent>
{
protected:
    BlockPos const&     mPos;
    StringTag&          mText;
    SignTextSide const& mTextSide;

public:
    constexpr explicit PlayerEditSignBeforeEvent(
        Player&             player,
        BlockPos const&     pos,
        StringTag&          text,
        SignTextSide const& textSide
    )
        : Cancellable(player)
        , mPos(pos)
        , mText(text)
        , mTextSide(textSide)
    {
    }

    ILAPI StringTag&          getText() const;
    ILAPI SignTextSide const& getTextSide() const;
    ILAPI BlockPos const&     getPos() const;
};

class PlayerEditSignAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    BlockPos const&     mPos;
    StringTag const&    mText;
    SignTextSide const& mTextSide;

public:
    constexpr explicit PlayerEditSignAfterEvent(
        Player&             player,
        BlockPos const&     pos,
        StringTag const&    text,
        SignTextSide const& textSide
    )
        : PlayerEvent(player)
        , mPos(pos)
        , mText(text)
        , mTextSide(textSide)
    {
    }

    ILAPI StringTag const&    getText() const;
    ILAPI SignTextSide const& getTextSide() const;
    ILAPI BlockPos const&     getPos() const;
};
} // namespace ila::mc::inline player