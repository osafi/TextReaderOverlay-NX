#include <FileSelect.hpp>

#include <filesystem>

#include <StandardOverlayFrame.hpp>
#include <FileSelectEntry.hpp>
#include <Config.hpp>
#include <Utils.hpp>

namespace fs = std::filesystem;

FileSelect::FileSelect(std::string const &path)
    : m_path(path),
      m_failed(false)
{
    auto favorites = Config::read()["favorites"];
    if (!favorites.is_array()) {
        favorites = {};
    }
    auto isFavorite = [favorites](std::string const &path) {
        auto found = std::find(favorites.begin(), favorites.end(), path);
        return found != favorites.end();
    };

    for (auto &entry : fs::directory_iterator(path)) {
        std::string absolutePath = entry.path();
        if (entry.is_directory()) {
            absolutePath.append("/");
            m_entries.push_back(new FileSelectDirEntry(absolutePath, isFavorite(absolutePath)));
        }
        else if (entry.is_regular_file()) {
            if (utils::toLowerCase(entry.path().extension()) == ".txt")
                m_entries.push_back(new FileSelectFileEntry(absolutePath, isFavorite(absolutePath)));
        }
    }

    std::sort(
        m_entries.begin(), m_entries.end(),
        [](FileSelectEntry *a, FileSelectEntry *b) { return *a < *b; });
}

FileSelect::~FileSelect() {
    for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
        delete *it;
    }
}

tsl::elm::Element* FileSelect::createUI() {
    auto frame = new StandardOverlayFrame("Select File...", m_path, "\uE0E3  Favorite");

    auto list = new tsl::elm::List();

    for (auto it = m_entries.begin(); it != m_entries.end(); ++it) {
        auto item = new tsl::elm::ListItem((*it)->label());
        item->setClickListener([it, item](u64 keys) {
            if (keys & KEY_A) {
                (*it)->select();
                return true;
            }
            else if (keys & KEY_Y) {
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
