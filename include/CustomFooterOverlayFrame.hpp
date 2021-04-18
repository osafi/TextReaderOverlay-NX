#include <tesla.hpp>

class CustomFooterOverlayFrame : public tsl::elm::OverlayFrame {

public:
    CustomFooterOverlayFrame(
        const std::string& title,
        const std::string& subtitle = "",
        const std::string& footer = "\uE0E1  Back     \uE0E0  OK"
    ) : OverlayFrame(title, subtitle), m_footer(footer) {}

    void draw(tsl::gfx::Renderer *renderer) override;

protected:
    std::string m_footer;
};