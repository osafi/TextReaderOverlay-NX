#include <tesla.hpp>

class StandardOverlayFrame : public tsl::elm::OverlayFrame {

public:
    static const s32 FRAME_WIDTH = 448;
    static const s32 FRAME_HEIGHT = 720;

    explicit StandardOverlayFrame(
        const std::string& title,
        const std::string& subtitle = " ",
        const std::string& footer = "\uE0E1  Back     \uE0E0  OK"
    ) : OverlayFrame(title, subtitle), m_footer(footer) {}

    void draw(tsl::gfx::Renderer *renderer) override;
    void layout(u16 parentX, u16 parentY, u16 parentWidth, u16 parentHeight) override;

protected:
    std::string m_footer;
};