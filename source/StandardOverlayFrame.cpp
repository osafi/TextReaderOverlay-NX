#include <StandardOverlayFrame.hpp>

void StandardOverlayFrame::draw(tsl::gfx::Renderer *renderer) {
    renderer->clearScreen();
    renderer->drawRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT, a(tsl::style::color::ColorFrameBackground));
    renderer->drawRect(FRAME_WIDTH - 1, 0, 1, FRAME_HEIGHT, a(0xF222));

    renderer->drawString(this->m_title.c_str(), false, 20, 50, 30, a(tsl::style::color::ColorText));
    renderer->drawString(this->m_subtitle.c_str(), false, 20, 70, 15, a(tsl::style::color::ColorDescription));

    renderer->drawRect(15, FRAME_HEIGHT - 73, FRAME_WIDTH - 30, 1, a(tsl::style::color::ColorText));

    renderer->drawString(this->m_footer.c_str(), false, 30, 693, 23, a(tsl::style::color::ColorText));

    if (this->m_contentElement != nullptr)
        this->m_contentElement->frame(renderer);
}

void StandardOverlayFrame::layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) {
    this->setBoundaries(parentX, parentY, FRAME_WIDTH, FRAME_HEIGHT);

    if (this->m_contentElement != nullptr) {
         this->m_contentElement->setBoundaries(parentX + 35, parentY + 125, FRAME_WIDTH - 85, FRAME_HEIGHT - 73 - 125);
        this->m_contentElement->invalidate();
    }
}