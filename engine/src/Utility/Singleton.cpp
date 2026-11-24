#include <Utility/Singleton.h>

#include <mutex>
#include <vector>

namespace
{
  struct Entry
  {
    std::type_index type;
    void* instance;
    void (*destroy)(void*);
  };

  struct Registry
  {
    std::recursive_mutex mutex;
    std::vector<Entry> entries;

    ~Registry()
    {
      for (auto it = entries.rbegin(); it != entries.rend(); ++it)
        it->destroy(it->instance);
    }
  };
}

void* singleton_detail::get_or_create(std::type_index type, void* (*create)(), void (*destroy)(void*))
{
  static Registry registry;
  std::lock_guard lock(registry.mutex);

  for (auto& entry : registry.entries)
    if (entry.type == type)
      return entry.instance;

  void* instance = create();
  registry.entries.push_back({ type, instance, destroy });
  return instance;
}