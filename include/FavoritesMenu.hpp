#pragma once

#include <tesla.hpp>
#include <list>

#include <FileSelectEntry.hpp>

class FavoritesMenu : public tsl::Gui {
public:
    FavoritesMenu();
    ~FavoritesMenu();

    tsl::elm::Element* createUI() override;

private:
    std::list<FileSelectEntry*> m_entries;
};
