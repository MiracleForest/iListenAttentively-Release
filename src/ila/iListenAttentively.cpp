#include "iListenAttentively.h"
#include <ll/api/chrono/GameChrono.h>
#include <ll/api/coro/CoroTask.h>
#include <ll/api/mod/RegisterHelper.h>
#include <ll/api/thread/ServerThreadExecutor.h>

namespace ila
{

iListenAttentively& iListenAttentively::getInstance()
{
    static iListenAttentively instance;
    return instance;
}

bool iListenAttentively::load() { return true; }

bool iListenAttentively::enable() { return true; }

bool iListenAttentively::disable() { return true; }

void nextTick(std::function<void()> func)
{
    ll::coro::keepThis([func { std::move(func) }]() -> ll::coro::CoroTask<> {
        co_await ll::chrono::ticks(1);
        func();
        co_return;
    }).launch(ll::thread::ServerThreadExecutor::getDefault());
}
} // namespace ila

LL_REGISTER_MOD(ila::iListenAttentively, ila::iListenAttentively::getInstance());
