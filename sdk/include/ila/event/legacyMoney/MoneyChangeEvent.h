#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>

namespace ila::legacyMoney
{
enum class LLMoneyEventType
{
    Set    = 0x0,
    Add    = 0x1,
    Reduce = 0x2,
    Trans  = 0x3,
};

class MoneyChangeBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    LLMoneyEventType const& mType;
    std::string&            mFromXuid;
    std::string&            mToXuid;
    llong&                  mValue;

public:
    constexpr explicit MoneyChangeBeforeEvent(
        LLMoneyEventType const& type,
        std::string&            fromXuid,
        std::string&            toXuid,
        llong&                  value
    )
        : Cancellable()
        , mType(type)
        , mFromXuid(fromXuid)
        , mToXuid(toXuid)
        , mValue(value)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI LLMoneyEventType const& type() const;
    ILNDAPI std::string& fromXuid() const;
    ILNDAPI std::string& toXuid() const;
    ILNDAPI llong&       value() const;
}; // class MoneyChangEvent

class MoneyChangeAfterEvent final : public ll::event::Event
{
protected:
    LLMoneyEventType const& mType;
    std::string const&      mFromXuid;
    std::string const&      mToXuid;
    llong const&            mValue;

public:
    constexpr explicit MoneyChangeAfterEvent(
        LLMoneyEventType const& type,
        std::string const&      fromXuid,
        std::string const&      toXuid,
        llong const&            value
    )
        : mType(type)
        , mFromXuid(fromXuid)
        , mToXuid(toXuid)
        , mValue(value)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI LLMoneyEventType const& type() const;
    ILNDAPI std::string const& fromXuid() const;
    ILNDAPI std::string const& toXuid() const;
    ILNDAPI llong const&       value() const;
}; // class MoneyChangEvent
} // namespace ila::legacyMoney