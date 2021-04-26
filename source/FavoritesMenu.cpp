#include <FavoritesMenu.hpp>

#include <StandardOverlayFrame.hpp>
#include <FileSelectEntry.hpp>
#include <Config.hpp>
#include <Utils.hpp>

FavoritesMenu::FavoritesMenu() {
    auto favorites = Config::read()["favorites"];
    if (!favorites.is_array()) {
        favorites = {};
    }

    for (auto &val : favorites) {
        std::string path = val;
        if (utils::endsWith(path, "/"))
            m_entries.push_back(new FileSelectDirEntry(path, true));
        else
            m_entries.push_back(new FileSelectFileEntry(path, true));
    }

    m_entries.sort([](FileSelectEntry *a, FileSelectEntry *b) { return *a < *b; });
}

FavoritesMenu::~FavoritesMenu() {
    for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
        delete *it;
    }
}

tsl::elm::Element* FavoritesMenu::createUI() {
    auto frame = new StandardOverlayFrame("Favorites", " ", "\uE0E3  Favorite");

    if (m_entries.empty()) {
        frame->setContent(new tsl::elm::CustomDrawer([this](tsl::gfx::Renderer *renderer, u16 x, u16 y, u16 w, u16 h) {
            renderer->drawString("No favorites added yet", false, 20, 100, 16, a(0xFFFF));
        }));
        return frame;
    }

    auto list = new tsl::elm::List();

    for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
        auto item = new tsl::elm::ListItem((*it)->label());
        item->setClickListener([it, item](s64 keys) {
            if (keys & KEY_A) {
                (*it)->select();
                return true;
            }
            if (keys & KEY_Y) {
                (*it)->toggleFavorite();
                item->setText((*it)->label());
                return true;
            }
            return false;
        });
        list->addItem(item);
    }

    frame->setContent(list);

    return frame;
}
