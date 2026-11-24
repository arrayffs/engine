#pragma once

#include <filesystem>
#include <chrono>
#include <format>
#include <fstream>
#include <print>
#include <string>
#include <string_view>

class Logger
{
protected:
  inline static std::ofstream _log_file;

public:
  template <typename... Args>
  static void message(std::string_view mod, std::format_string<Args...> fmt, Args&&... args)
  {
    write('+', mod, std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void warn(std::string_view mod, std::format_string<Args...> fmt, Args&&... args)
  {
    write('?', mod, std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void error(std::string_view mod, std::format_string<Args...> fmt, Args&&... args)
  {
    write('!', mod, std::format(fmt, std::forward<Args>(args)...));
  }

private:
  static void create()
  {
    auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    auto local = std::chrono::zoned_time{ std::chrono::current_zone(), now };
    std::filesystem::create_directory("./logs");
    _log_file.open(std::format("./logs/log-{:%d-%m-%Y %H-%M-%S}.txt", local));

    message("Logger", "Initialized");
  }

  static void write(char level, std::string_view mod, const std::string& text)
  {
    auto line = std::format("[{}] {}: {}", level, mod, text);
    
    if (!_log_file.is_open())
      create();
    else if (_log_file.is_open())
      _log_file << line << std::endl;

    std::println("{}", line);
  }

};