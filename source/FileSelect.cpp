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
    for (auto & m_entry : m_entries) {
        delete m_entry;
    }
}

tsl::elm::Element* FileSelect::createUI() {
    auto frame = new StandardOverlayFrame("Select File...", m_path, "\uE0E3  Favorite");

    auto list = new tsl::elm::List();

    for (auto & m_entry : m_entries) {
        auto item = new tsl::elm::ListItem(m_entry->label());
        item->setClickListener([&m_entry, item](u64 keys) {
            if (keys & HidNpadButton_A) {
                m_entry->select();
                return true;
            }
            else if (keys & HidNpadButton_Y) {
                m_entry->toggleFavorite();
                item->setText(m_entry->label());
                return true;
            }
            return false;
        });
        list->addItem(item);
    }

    frame->setContent(list);

    return frame;
}
