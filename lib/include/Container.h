template <typename T> class Container
{
public:
  typedef Container<T>* ptr_t;
public:
    Container(T value);
    T operator() ();
private:
    T m_value;
};
