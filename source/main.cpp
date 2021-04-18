#define TESLA_INIT_IMPL
#include <tesla.hpp>

#include <Overlay.hpp>

int main(int argc, char **argv) {
    fsdevMountSdmc();
    tsl::hlp::ScopeGuard dirGuard([]{ fsdevUnmountDevice("sdmc"); });

    return tsl::loop<TextReaderOverlay>(argc, argv);
}
