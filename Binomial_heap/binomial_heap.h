template <class Key>
struct binomial_node
{
    Key value;
    binomial_node<Key> *parent;
    binomial_node<Key> *child; // указатель на левого сына
    binomial_node<Key> *sibling; // указатель на правого брата
    binomial_node<Key> *adoptee; //указатель на левого брата
    int degree; // количество сыновей
    binomial_node<Key> *point;
    bool mark;
};

template <class Key>
class binomial_heap
{
public:
    bool is_empty();
    binomial_node<Key>* insert(Key key);
    Key get_min();
    Key extract_min();

    void erase(binomial_node<Key>* ptr);
    void change(binomial_node<Key>* ptr, Key new_value);
    binomial_heap();
    void merge(binomial_heap<Key>* otherHeap);
private:
    binomial_node<Key>* heap_merge(binomial_node<Key>* heap1, binomial_node<Key>* heap2);
    binomial_node<Key>* tree_merge(binomial_node<Key>* root1, binomial_node<Key>* root2);
    int heap_size;
    binomial_node<Key>* Heap;
    void siftUp(binomial_node<Key>* ptr);
    void siftDown(binomial_node<Key>* ptr);
    void _swap(binomial_node<Key>* ptr1, binomial_node<Key>* ptr2);
    binomial_node<Key>* tree_extract_min(binomial_node<Key>* min);

};