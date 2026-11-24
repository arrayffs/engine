#pragma once

#include <typeindex>

namespace singleton_detail
{
  void* get_or_create(std::type_index type, void* (*create)(), void (*destroy)(void*));
}

template <class T>
class Singleton
{
public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static T* inst()
  {
    static T* instance = static_cast<T*>(singleton_detail::get_or_create(
      typeid(T),
      []() -> void* { return new T(); },
      [](void* p) { delete static_cast<T*>(p); }
    ));
    return instance;
  }

protected:
  Singleton() = default;
  ~Singleton() = default;
};