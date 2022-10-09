#pragma once

#include <tesla.hpp>
#include <list>

class SettingsMenu : public tsl::Gui {
public:
    SettingsMenu();
    ~SettingsMenu();

    tsl::elm::Element* createUI() override;

private:
    u8 m_chunkSize;
};
