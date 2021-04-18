#include <CustomFooterOverlayFrame.hpp>

void CustomFooterOverlayFrame::draw(tsl::gfx::Renderer *renderer) {
    renderer->fillScreen(a(tsl::style::color::ColorFrameBackground));
    renderer->drawRect(tsl::cfg::FramebufferWidth - 1, 0, 1, tsl::cfg::FramebufferHeight, a(0xF222));

    renderer->drawString(this->m_title.c_str(), false, 20, 50, 30, a(tsl::style::color::ColorText));
    renderer->drawString(this->m_subtitle.c_str(), false, 20, 70, 15, a(tsl::style::color::ColorDescription));

    renderer->drawRect(15, tsl::cfg::FramebufferHeight - 73, tsl::cfg::FramebufferWidth - 30, 1, a(tsl::style::color::ColorText));

    renderer->drawString(this->m_footer.c_str(), false, 30, 693, 23, a(tsl::style::color::ColorText));

    if (this->m_contentElement != nullptr)
        this->m_contentElement->frame(renderer);
}
