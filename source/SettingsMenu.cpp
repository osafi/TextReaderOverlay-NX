#include <SettingsMenu.hpp>

#include <StandardOverlayFrame.hpp>
#include <Config.hpp>
#include <Utils.hpp>

SettingsMenu::SettingsMenu(): m_chunkSize(150) {
    auto j = Config::read();
    auto chunkSize = j["settings"].find("chunkSize");
    if (chunkSize != j["settings"].end()) {
        m_chunkSize = *chunkSize;
    }
}

SettingsMenu::~SettingsMenu() {
    Config::update([this](json &j) {
        j["settings"]["chunkSize"] = m_chunkSize;
    });
}

tsl::elm::Element *SettingsMenu::createUI() {
    auto frame = new StandardOverlayFrame("Settings");

    auto list = new tsl::elm::List();

    list->addItem(new tsl::elm::CategoryHeader("Chunk Size"));
    auto *chunkSizeTrackBar = new tsl::elm::NamedStepTrackBar("c", {"50", "100", "150", "200", "250"});
    chunkSizeTrackBar->setProgress((m_chunkSize / 50) - 1);
    chunkSizeTrackBar->setValueChangedListener([this](u32 value){
        m_chunkSize = 50 * (value + 1);
    });
    list->addItem(chunkSizeTrackBar);

    frame->setContent(list);
    return frame;
}
