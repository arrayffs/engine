#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T>
class Singleton
{
public:
  Singleton(const Singleton&) = delete;
  Singleton& operator=(const Singleton&) = delete;

  static T* inst() {
    static T inst{ };
    return &inst;
  }

protected:
  Singleton() = default;
  ~Singleton() = default;
};

#endif // !_SINGLETON_H_