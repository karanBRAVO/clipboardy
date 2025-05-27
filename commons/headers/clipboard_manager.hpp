#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <thread>

#include "clip.h"

class ClipboardManager {
  std::string last_clipboard_content_;
  std::atomic<bool> running_{true};

 public:
  ClipboardManager() = default;
  ~ClipboardManager();

  std::string get_text() const;
  void set_text(const std::string& str);
  void poll(std::function<void(const std::string&)> cb);
  void stop();
};
