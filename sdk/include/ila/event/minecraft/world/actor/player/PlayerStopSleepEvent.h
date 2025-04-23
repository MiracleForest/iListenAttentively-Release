#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <mc/world/actor/player/BedSleepingResult.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline actor::inline player
{
class PlayerStopSleepBeforeEvent final : public ll::event::player::PlayerEvent
{
protected:
    bool& mForcefulWakeUp;
    bool& mUpdateLevelList;

public:
    constexpr explicit PlayerStopSleepBeforeEvent(Player& player, bool& forcefulWakeUp, bool& updateLevelList)
        : PlayerEvent(player)
        , mForcefulWakeUp(forcefulWakeUp)
        , mUpdateLevelList(updateLevelList)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI bool& forcefulWakeUp() const;
    ILNDAPI bool& updateLevelList() const;
};

class PlayerStopSleepAfterEvent final : public ll::event::player::PlayerEvent
{
protected:
    bool const& mForcefulWakeUp;
    bool const& mUpdateLevelList;

public:
    constexpr explicit PlayerStopSleepAfterEvent(
        Player&     player,
        bool const& forcefulWakeUp,
        bool const& updateLevelList
    )
        : PlayerEvent(player)
        , mForcefulWakeUp(forcefulWakeUp)
        , mUpdateLevelList(updateLevelList)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI bool const& forcefulWakeUp() const;
    ILNDAPI bool const& updateLevelList() const;
};
} // namespace ila::mc::inline world::inline actor::inline player