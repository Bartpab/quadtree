#include "Container.h"

template <typename T> Container<T>::Container(T value): m_value(value) {}
template <typename T> T Container<T>::operator() ()
{
    return this->m_value;
}
