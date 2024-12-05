#include "ila/Global.h"

namespace ila::legacyMoney
{
enum class LLMoneyEventType
{
    Set    = 0x0,
    Add    = 0x1,
    Reduce = 0x2,
    Trans  = 0x3,
};

class MoneyChangBeforeEvent final : public ll::event::Cancellable<ll::event::Event>
{
protected:
    LLMoneyEventType const& mType;
    std::string const&      mFromXuid;
    std::string const&      mToXuid;
    llong const&            mValue;

public:
    constexpr explicit MoneyChangBeforeEvent(
        LLMoneyEventType const& type,
        std::string const&      fromXuid,
        std::string const&      toXuid,
        llong const&            value
    )
        : Cancellable()
        , mType(type)
        , mFromXuid(fromXuid)
        , mToXuid(toXuid)
        , mValue(value)
    {
    }

    ILAPI LLMoneyEventType const& getType() const;
    ILAPI std::string const& getFromXuid() const;
    ILAPI std::string const& getToXuid() const;
    ILAPI llong const&       getValue() const;
}; // class MoneyChangEvent

class MoneyChangAfterEvent final : public ll::event::Event
{
protected:
    LLMoneyEventType const& mType;
    std::string const&      mFromXuid;
    std::string const&      mToXuid;
    llong const&            mValue;

public:
    constexpr explicit MoneyChangAfterEvent(
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

    ILAPI LLMoneyEventType const& getType() const;
    ILAPI std::string const& getFromXuid() const;
    ILAPI std::string const& getToXuid() const;
    ILAPI llong const&       getValue() const;
}; // class MoneyChangEvent
} // namespace ila::legacyMoney