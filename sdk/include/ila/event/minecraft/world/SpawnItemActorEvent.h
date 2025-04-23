#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>

// clang-format off
class Vec3;
class Actor;
class ItemStack;
class ItemActor;
// clang-format on

namespace ila::mc::inline world
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

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI Vec3&      pos() const;
    ILNDAPI ItemStack& item() const;
    ILNDAPI Actor*&    spawner() const;
    ILNDAPI int&       throwTime() const;
};

class SpawnItemActorAfterEvent final : public ll::event::WorldEvent
{
protected:
    Vec3 const&      mPos;
    ItemStack const& mItem;
    Actor* const&    mSpawner;
    int const&       mThrowTime;
    ItemActor&       mItemActor;

public:
    constexpr explicit SpawnItemActorAfterEvent(
        BlockSource&     blockSource,
        Vec3 const&      pos,
        ItemStack const& item,
        Actor* const&    spawner,
        int const&       throwTime,
        ItemActor&       itemActor
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mItem(item)
        , mSpawner(spawner)
        , mThrowTime(throwTime)
        , mItemActor(itemActor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Vec3 const&      pos() const;
    ILNDAPI ItemStack const& item() const;
    ILNDAPI Actor* const&    spawner() const;
    ILNDAPI int const&       throwTime() const;
    ILNDAPI ItemActor&       itemActor() const;
};
} // namespace ila::mc::inline world