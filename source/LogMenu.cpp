#include <LogMenu.hpp>

#include <Log.hpp>
#include <StandardOverlayFrame.hpp>

tsl::elm::Element* LogMenu::createUI() {
    auto *frame = new StandardOverlayFrame("Log Menu");

    frame->setContent(new tsl::elm::CustomDrawer([](tsl::gfx::Renderer *renderer, u16 x, u16 y, u16 w, u16 h) {
        Log::forEach([renderer, x, y](std::string const &msg, int i) {
            renderer->drawString(msg.c_str(), false, x, y + 12 + i*12, 12, a(0xFFFF));
        });
    }));

    return frame;
}
