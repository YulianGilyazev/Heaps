template <class Key>
struct node
{
    Key value;
    node<Key> *parent;
    node<Key> *child; // указатель на левого сына
    node<Key> *sibling; // указатель на правого брата
    node<Key> *adoptee; //указатель на левого брата
    int degree; // количество сыновей
    node<Key> *point;
    bool mark;
};

template <class Key>
class binomial_heap
{
public:
    bool is_empty();
    node<Key>* insert(Key key);
    Key get_min();
    Key extract_min();

    void erase(node<Key>* ptr);
    void change(node<Key>* ptr, Key new_value);
    binomial_heap();
    void merge(binomial_heap<Key>* otherHeap);
private:
    node<Key>* heap_merge(node<Key>* heap1, node<Key>* heap2);
    node<Key>* tree_merge(node<Key>* root1, node<Key>* root2);
    int heap_size;
    node<Key>* Heap;
    void siftUp(node<Key>* ptr);
    void siftDown(node<Key>* ptr);
    void _swap(node<Key>* ptr1, node<Key>* ptr2);
    node<Key>* tree_extract_min(node<Key>* min);

};