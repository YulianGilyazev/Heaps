template <class Key>
class my_vector
{
public:
    void push_back(Key key);
    void pop_back();
    bool is_empty() const;
    void increase();
    void decrease();
    int size() const;
    Key& operator [](int i);
    const Key& operator [](int i) const;
    Key* operator &(int i);
    ~my_vector();
    my_vector();
private:
    Key* T = nullptr;
    int size_T;
    int size_vec;

};
template <class Key>
void my_vector<Key>::push_back(Key key)
{
    if (size_vec + 1 >= size_T)
    {
        increase();
    }
    T[size_vec] = key;
    size_vec++;
}

template<class Key>
void my_vector<Key>::pop_back()
{
    size_vec--;
    if (size_vec * 4 < size_T && size_vec > 20)
        decrease();
}
template <class Key>
int my_vector<Key>::size() const
{
    return size_vec;
}
template <class Key>
bool my_vector<Key>::is_empty() const
{
    return size == 0;
}

template <class Key>
void my_vector<Key>::increase()
{

    size_T = size_T * 2 + 1;
    Key* Q = new Key[size_T];
    for (int i = 0; i < size_vec; i++)
    {
        Q[i] = T[i];

    }
    T = Q;
}
template <class Key>
const Key& my_vector<Key>::operator [](int i) const
{
    return T[i];
}
template <class Key>
Key& my_vector<Key>::operator [](int i)
{
    return T[i];
}
template <class Key>
Key* my_vector<Key>::operator &(int i)
{
    return &T[i];
}

template <class Key>
my_vector<Key>::~my_vector()
{
    if (T != nullptr)
    {
        delete[] T;
    }
}

template<class Key>
my_vector<Key>::my_vector()
{
    size_T = 2;
    Key *Q = new Key[2];
    T = Q;
    size_vec = 0;
}

template<class Key>
void my_vector<Key>::decrease()
{
    size_T = size_T / 2;
    Key* Q = new Key[size_T];
    for (int i = 0; i < size_vec; i++)
    {
        Q[i] = T[i];
    }
    T = Q;
}
