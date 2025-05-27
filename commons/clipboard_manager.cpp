#include "clipboard_manager.hpp"

ClipboardManager::~ClipboardManager() {
  stop();
}

std::string ClipboardManager::get_text() const {
  std::string str;
  if (clip::has(clip::text_format())) {
    clip::get_text(str);
  }
  return str;
}

void ClipboardManager::set_text(const std::string& str) {
  clip::set_text(str);
}

void ClipboardManager::poll(std::function<void(const std::string&)> cb) {
  std::thread([this, cb]() {
    while (running_) {
      std::string clipboard_content = get_text();

      if (clipboard_content != last_clipboard_content_) {
        std::cout << "Syncing..." << std::endl;
        last_clipboard_content_ = clipboard_content;
        cb(clipboard_content);
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }).detach();
}

void ClipboardManager::stop() {
  running_ = false;
}
