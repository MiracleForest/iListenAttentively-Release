// clang-format off
#include <span>
#include <ll/api/mod/NativeMod.h>
// clang-format on

namespace ila
{

class iListenAttentively
{

public:
    static iListenAttentively& getInstance();

    iListenAttentively(ll::mod::NativeMod& self)
        : mSelf(self)
    {
    }

    [[nodiscard]] ll::mod::NativeMod& getSelf() const { return mSelf; }

    bool load();

    bool enable();

    bool disable();

    // bool unload();

private:
    ll::mod::NativeMod& mSelf;
}; // class iListenAttentively

} // namespace ila