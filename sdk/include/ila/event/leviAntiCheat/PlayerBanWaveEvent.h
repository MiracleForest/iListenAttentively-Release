#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace ila::lac
{

enum class BanWaveType
{
    Kick,
    Ban
};

class PlayerBanWaveEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    BanWaveType mType;

public:
    constexpr explicit PlayerBanWaveEvent(Player& player, BanWaveType type)
        : Cancellable(player)
        , mType(type)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BanWaveType type() const;
};

} // namespace ila::lac