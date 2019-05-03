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

