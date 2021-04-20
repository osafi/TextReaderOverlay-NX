#include <HelpMenu.hpp>

tsl::elm::Element* HelpMenu::createUI() {
    auto *frame = new tsl::elm::OverlayFrame("Controls", "");

    frame->setContent(new tsl::elm::CustomDrawer([](tsl::gfx::Renderer *renderer, u16 x, u16 y, u16 w, u16 h) {
        u32 yOffset, i;

        yOffset = 30 + y, i = 0;
        renderer->drawString("File Browser", false, x, yOffset, 30, a(0xFFFF));
        showKeybind(renderer, x, yOffset, i++, "\uE0A3", "Toggle Favorite");

        yOffset = 140 + y, i = 0;
        renderer->drawString("Reader", false, x, yOffset, 30, a(0xFFFF));
        showKeybind(renderer, x, yOffset, i++, "\uE081", "Scroll");
        showKeybind(renderer, x, yOffset, i++, "\uE085 \uE081", "Scroll Faster");
        showKeybind(renderer, x, yOffset, i++, "\uE086 \uE081 \uE091 \uE090", "Scroll Even Faster");
        showKeybind(renderer, x, yOffset, i++, "\uE086 \uE081 \uE092 \uE093", "Scroll to Top / Bottom");
        showKeybind(renderer, x, yOffset, i++, "\uE07D", "Adjust Font Size");
        showKeybind(renderer, x, yOffset, i++, "\uE082", "Scroll Sideways");
        showKeybind(renderer, x, yOffset, i++, "\uE08B", "Beginning of Line");
        showKeybind(renderer, x, yOffset, i++, "\uE0A3", "Toggle Bookmark");
        showKeybind(renderer, x, yOffset, i++, "\uE0A4 \uE0A5", "Prev/Next Bookmark");
        showKeybind(renderer, x, yOffset, i++, "\uE0A2", "Hide Overlay");
    }));

    return frame;
}

inline void HelpMenu::showKeybind(tsl::gfx::Renderer *renderer, u32 xOffset, u32 yOffset, u32 i, const char* keys, const char* desc) {
    renderer->drawString(keys, false, xOffset, yOffset + 30 + 32 * i, 22, a(0xFFFF));
    renderer->drawString(desc, false, xOffset + 125, yOffset + 30 + 32 * i, 22, a(0xFFFF));
}
