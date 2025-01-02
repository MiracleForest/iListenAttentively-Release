#include "iListenAttentively.h"
#include <ll/api/mod/RegisterHelper.h>

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

} // namespace ila

LL_REGISTER_MOD(ila::iListenAttentively, ila::iListenAttentively::getInstance());