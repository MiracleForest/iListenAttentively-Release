#include "ila/event/legacyMoney/MoneyChangeEvent.h"
#include "ila/base/Gloabl.h"
#define _AMD64_
#include <libloaderapi.h>

namespace ila::legacyMoney
{

void MoneyChangBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["type"]  = magic_enum::enum_name(getType());
    nbt["from"]  = getFromXuid();
    nbt["to"]    = getToXuid();
    nbt["value"] = getValue();
}
LLMoneyEventType const& MoneyChangBeforeEvent::getType() const { return mType; }
std::string const&      MoneyChangBeforeEvent::getFromXuid() const { return mFromXuid; }
std::string const&      MoneyChangBeforeEvent::getToXuid() const { return mToXuid; }
llong const&            MoneyChangBeforeEvent::getValue() const { return mValue; }

void MoneyChangAfterEvent::serialize(CompoundTag& nbt) const
{
    nbt["type"]  = magic_enum::enum_name(getType());
    nbt["from"]  = getFromXuid();
    nbt["to"]    = getToXuid();
    nbt["value"] = getValue();
}
LLMoneyEventType const& MoneyChangAfterEvent::getType() const { return mType; }
std::string const&      MoneyChangAfterEvent::getFromXuid() const { return mFromXuid; }
std::string const&      MoneyChangAfterEvent::getToXuid() const { return mToXuid; }
llong const&            MoneyChangAfterEvent::getValue() const { return mValue; }

bool MoneyBeforeEventCallback(LLMoneyEventType type, std::string from, std::string to, llong value)
{
    auto beforeEvent = MoneyChangBeforeEvent(type, from, to, value);
    LLEventBus.publish(beforeEvent);
    return !beforeEvent.isCancelled();
}

void MoneyAfterEventCallback(LLMoneyEventType type, std::string from, std::string to, llong value)
{
    LLEventBus.publish(MoneyChangAfterEvent(type, from, to, value));
}

static std::unique_ptr<ll::event::EmitterBase> eventBeforeEmitterFactory();
class MoneyChangBeforeEventEmitter
    : public ll::event::Emitter<eventBeforeEmitterFactory, MoneyChangBeforeEvent>
{
public:
    MoneyChangBeforeEventEmitter()
    {
        static bool mCreated = false;
        if (mCreated) { return; }
        if (auto func = GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), "LLMoney_ListenBeforeEvent");
            func != nullptr)
        {
            reinterpret_cast<void (*)(bool (*)(LLMoneyEventType, std::string, std::string, llong))>(func)(
                MoneyBeforeEventCallback
            );
        }
        mCreated = true;
    }
    ~MoneyChangBeforeEventEmitter()
    {
        // Unable to uninstall
    }
};
static std::unique_ptr<ll::event::EmitterBase> eventBeforeEmitterFactory()
{
    return std::make_unique<MoneyChangBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> eventAfterEmitterFactory();
class MoneyChangAfterEventEmitter : public ll::event::Emitter<eventAfterEmitterFactory, MoneyChangAfterEvent>
{
public:
    MoneyChangAfterEventEmitter()
    {
        static bool mCreated = false;
        if (mCreated) { return; }
        if (auto func = GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), "LLMoney_ListenAfterEvent");
            func != nullptr)
        {
            reinterpret_cast<void (*)(void (*)(LLMoneyEventType, std::string, std::string, llong))>(func)(
                MoneyAfterEventCallback
            );
        }
        mCreated = true;
    }
    ~MoneyChangAfterEventEmitter()
    {
        // Unable to uninstall
    }
};
static std::unique_ptr<ll::event::EmitterBase> eventAfterEmitterFactory()
{
    return std::make_unique<MoneyChangAfterEventEmitter>();
};
} // namespace ila::legacyMoney