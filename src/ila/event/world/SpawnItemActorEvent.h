#include "Global.h"

namespace ila::inline world
{
class SpawnItemActorBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    Vec3&      mPos;
    ItemStack& mItem;
    Actor*&    mSpawner;
    int&       mThrowTime;

public:
    constexpr explicit SpawnItemActorBeforeEvent(
        BlockSource& blockSource,
        Vec3&        pos,
        ItemStack&   item,
        Actor*&      spawner,
        int&         throwTime
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mItem(item)
        , mSpawner(spawner)
        , mThrowTime(throwTime)
    {
    }

    ILAPI Vec3&      getPos() const;
    ILAPI ItemStack& getItem() const;
    ILAPI Actor*&    getSpawner() const;
    ILAPI int&       getThrowTime() const;
};

class SpawnItemActorAfterEvent final : public ll::event::WorldEvent
{
protected:
    Vec3 const&      mPos;
    ItemStack const& mItem;
    Actor* const&    mSpawner;
    int const&       mThrowTime;
    ItemActor*&      mItemActor;

public:
    constexpr explicit SpawnItemActorAfterEvent(
        BlockSource&     blockSource,
        Vec3 const&      pos,
        ItemStack const& item,
        Actor* const&    spawner,
        int const&       throwTime,
        ItemActor*&      itemActor
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mItem(item)
        , mSpawner(spawner)
        , mThrowTime(throwTime)
        , mItemActor(itemActor)
    {
    }

    ILAPI Vec3 const&      getPos() const;
    ILAPI ItemStack const& getItem() const;
    ILAPI Actor* const&    getSpawner() const;
    ILAPI int const&       getThrowTime() const;
    ILAPI ItemActor*&      getItemActor() const;
};
} // namespace ila::inline world