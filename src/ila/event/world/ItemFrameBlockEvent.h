#include "Global.h"

namespace ila::inline world
{

enum class ItemFrameBlockEventType
{
    Place,
    Take,
    Rotate
};

class ItemFrameBlockBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const&               mPos;
    Player&                       mPlayer;
    ItemFrameBlockEventType const mType;

public:
    constexpr explicit ItemFrameBlockBeforeEvent(
        BlockSource&            blockSource,
        BlockPos const&         pos,
        Player&                 player,
        ItemFrameBlockEventType type
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mPlayer(player)
        , mType(type)
    {
    }

    ILAPI BlockPos const&                getPos() const;
    ILAPI Player&                        getPlayer() const;
    ILAPI ItemFrameBlockEventType const& getType() const;
};

class ItemFrameBlockAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const&               mPos;
    Player const&                 mPlayer;
    ItemFrameBlockEventType const mType;
    bool&                         mResult;

public:
    constexpr explicit ItemFrameBlockAfterEvent(
        BlockSource&            blockSource,
        BlockPos const&         pos,
        Player&                 player,
        ItemFrameBlockEventType type,
        bool&                   result
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mPlayer(player)
        , mType(type)
        , mResult(result)
    {
    }

    ILAPI BlockPos const&                getPos() const;
    ILAPI Player const&                  getPlayer() const;
    ILAPI ItemFrameBlockEventType const& getType() const;
    ILAPI bool&                          getResult() const;
};
} // namespace ila::inline world