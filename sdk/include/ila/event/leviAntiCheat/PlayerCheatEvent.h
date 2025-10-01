#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>

namespace ila::lac
{

enum class CheckType
{
    IllegalMovement,
    Timer,
    Spam,
    InvalidFilterString,
    IllegalTrade,
    IllegalBreaking,
    FakeName,
    SpawnXpOrbs,
    Toolbox,
    AutoClick,
    Reach,
    InvalidNbtItem,
    InvalidAnvilEnchant,
    AutoOffhand,
    BanItem,
    InvalidEnchantLevel,
    InvalidGetItem,
    InvalidStackItem,
    MessageTooLong,
    CommandSpam,
    XpHack,
    NoPacket,
    BadPacket,
};

enum class PunishType
{
    Warning = 0,
    Mute    = 1,
    Kick    = 2,
    Ban     = 3,
    Cancel  = 4,
    None    = 5
};

using ExtraInfo =
    std::unordered_map<std::string, std::variant<std::string, int, ullong, llong, std::string_view, float>>;

class PlayerCheatEvent final : public ll::event::Cancellable<ll::event::PlayerEvent>
{
protected:
    CheckType const&  mCheatType;
    ExtraInfo const&  mExtraData;
    int const&        mDuration;
    PunishType const& mType;

public:
    constexpr explicit PlayerCheatEvent(
        Player&           player,
        CheckType const&  cheatType,
        ExtraInfo const&  extraData,
        int const&        duration,
        PunishType const& type
    )
        : Cancellable(player)
        , mCheatType(cheatType)
        , mExtraData(extraData)
        , mDuration(duration)
        , mType(type)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI CheckType const&  cheatType() const;
    ILNDAPI ExtraInfo const&  extraData() const;
    ILNDAPI int const&        duration() const;
    ILNDAPI PunishType const& type() const;
};

} // namespace ila::lac
