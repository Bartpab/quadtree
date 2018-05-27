#ifndef __TD__
#define __TD__
#include <cstdint>

using ptr_typeid_t = void(*)();
using typeid_t = uintptr_t;

template <typename T>
typeid_t type_id() noexcept
{
  return (typeid_t)ptr_typeid_t(type_id<T>);
}

#endif
