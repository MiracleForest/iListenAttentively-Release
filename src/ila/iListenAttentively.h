#include <ll/api/mod/NativeMod.h>

namespace ila
{

class iListenAttentively
{

public:
    static iListenAttentively& getInstance();

    iListenAttentively()
        : mSelf(*ll::mod::NativeMod::current())
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