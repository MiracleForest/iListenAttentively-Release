#include "MoneyChangeEvent.h"
#include <windows.h>

namespace ila::legacyMoney
{

LLMoneyEventType const& MoneyChangBeforeEvent::getType() const { return mType; }
std::string const&      MoneyChangBeforeEvent::getFromXuid() const { return mFromXuid; }
std::string const&      MoneyChangBeforeEvent::getToXuid() const { return mToXuid; }
llong const&            MoneyChangBeforeEvent::getValue() const { return mValue; }

LLMoneyEventType const& MoneyChangAfterEvent::getType() const { return mType; }
std::string const&      MoneyChangAfterEvent::getFromXuid() const { return mFromXuid; }
std::string const&      MoneyChangAfterEvent::getToXuid() const { return mToXuid; }
llong const&            MoneyChangAfterEvent::getValue() const { return mValue; }

bool MoneyBeforeEventCallback(LLMoneyEventType type, std::string from, std::string to, llong value)
{
    auto beforeEvent = MoneyChangBeforeEvent(type, from, to, value);
    eventBus.publish(beforeEvent);
    return !beforeEvent.isCancelled();
}

void MoneyAfterEventCallback(LLMoneyEventType type, std::string from, std::string to, llong value)
{
    eventBus.publish(MoneyChangAfterEvent(type, from, to, value));
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class MoneyChangBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, MoneyChangBeforeEvent>
{
private:
    static bool mCreated;

public:
    MoneyChangBeforeEventEmitter()
    {
        if (!mCreated)
        {
            // clang-format off
            if (auto func = GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), "LLMoney_ListenBeforeEvent"); func != nullptr)
            {
                ((void (*)(bool (*)(LLMoneyEventType, std::string, std::string, llong)))func)(MoneyBeforeEventCallback);
            }
            // clang-format on
            mCreated = true;
        }
    }
    ~MoneyChangBeforeEventEmitter()
    {
        // Unable to uninstall
    }
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<MoneyChangBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class MoneyChangAfterEventEmitter : public ll::event::Emitter<emitterFactory2, MoneyChangAfterEvent>
{
private:
    static bool mCreated;

public:
    MoneyChangAfterEventEmitter() {
        if (!mCreated)
        {
            // clang-format off
            if (auto func = GetProcAddress(GetModuleHandleW(L"LegacyMoney.dll"), "LLMoney_ListenAfterEvent"); func != nullptr)
            {
                ((void (*)(void (*)(LLMoneyEventType, std::string, std::string, llong)))func)(MoneyAfterEventCallback);
            }
            // clang-format on
            mCreated = true;
        }
    }
    ~MoneyChangAfterEventEmitter()
    {
        // Unable to uninstall
    }
};
static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<MoneyChangAfterEventEmitter>();
};
} // namespace ila::legacyMoney