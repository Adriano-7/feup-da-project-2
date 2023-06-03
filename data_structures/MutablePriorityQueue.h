#include <vector>

/**
 * @class MutablePriorityQueue
 * @brief Represents a mutable priority queue data structure.
 * @tparam T The type of elements in the priority queue.
 */
template <class T>
class MutablePriorityQueue {
    std::vector<T *> H;

    /**
     * @brief Restores the heap property by moving an element up in the heap.
     * @param i The index of the element to be moved up.
     */
    void heapifyUp(unsigned i);

    /**
     * @brief Restores the heap property by moving an element down in the heap.
     * @param i The index of the element to be moved down.
     */
    void heapifyDown(unsigned i);

    /**
     * @brief Sets the element at the specified index in the heap.
     * @param i The index of the element to be set.
     * @param x A pointer to the element.
     */
    inline void set(unsigned i, T *x);

public:
    /**
     * @brief Constructs an empty mutable priority queue.
     */
    MutablePriorityQueue();

    /**
     * @brief Checks if the priority queue is empty.
     * @return True if the priority queue is empty, false otherwise.
     */
    bool empty();

    /**
     * @brief Inserts an element into the priority queue.
     * @param x A pointer to the element to be inserted.
     */
    void insert(T *x);

    /**
     * @brief Extracts the minimum element from the priority queue.
     * @return A pointer to the minimum element.
     */
    T *extractMin();

    /**
     * @brief Decreases the key of an element in the priority queue.
     * @param x A pointer to the element whose key needs to be decreased.
     */
    void decreaseKey(T *x);
};

/**
 * @brief Calculates the index of the parent of a node in the heap.
 * @param i The index of the node.
 * @return The index of the parent.
 */
#define parent(i) ((i) / 2)

/**
 * @brief Calculates the index of the left child of a node in the heap.
 * @param i The index of the node.
 * @return The index of the left child.
 */
#define leftChild(i) ((i) * 2)

/**
 * @brief Constructs a new MutablePriorityQueue object.
 *
 * This constructor initializes a new instance of the MutablePriorityQueue class.
 * It adds a nullptr to the vector H to maintain the heap property.
 *
 * @tparam T The type of elements stored in the priority queue.
 */
template <class T>
MutablePriorityQueue<T>::MutablePriorityQueue() {
    H.push_back(nullptr);
}

/**
 * @brief Checks whether the priority queue is empty.
 *
 * This function checks whether the priority queue is empty by comparing the size of the vector H
 * with 1. If the size is 1, it means that the queue only contains the nullptr element and is empty.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @return true if the priority queue is empty, false otherwise.
 */
template <class T>
bool MutablePriorityQueue<T>::empty() {
    return H.size() == 1;
}

/**
 * @brief Extracts the minimum element from the priority queue.
 *
 * This function extracts the minimum element from the priority queue and adjusts the heap
 * to maintain the heap property. The extracted element is removed from the priority queue.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @return The minimum element.
 */
template <class T>
T *MutablePriorityQueue<T>::extractMin() {
    auto x = H[1];
    H[1] = H.back();
    H.pop_back();
    if (H.size() > 1)
        heapifyDown(1);
    x->queueIndex = 0;
    return x;
}

/**
 * @brief Inserts an element into the priority queue.
 *
 * This function inserts an element into the priority queue and adjusts the heap to maintain
 * the heap property.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @param x The element to insert.
 */
template <class T>
void MutablePriorityQueue<T>::insert(T *x) {
    H.push_back(x);
    heapifyUp(H.size() - 1);
}

/**
 * @brief Decreases the key of the specified element in the priority queue.
 *
 * This function decreases the key of the specified element in the priority queue and adjusts
 * the heap to maintain the heap property.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @param x The element whose key needs to be decreased.
 */
template <class T>
void MutablePriorityQueue<T>::decreaseKey(T *x) {
    heapifyUp(x->queueIndex);
}

/**
 * @brief Performs the heapify-up operation to maintain the heap property after an element is inserted.
 *
 * This function performs the heapify-up operation to maintain the heap property after an element
 * is inserted into the priority queue. It compares the element at index i with its parent, and if
 * the parent is larger, it swaps them and continues the process until the element is in the correct
 * position or reaches the root of the heap.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @param i The index of the element to heapify-up.
 */
template <class T>
void MutablePriorityQueue<T>::heapifyUp(unsigned i) {
    auto x = H[i];
    while (i > 1 && *x < *H[parent(i)]) {
        set(i, H[parent(i)]);
        i = parent(i);
    }
    set(i, x);
}

/**
 * @brief Performs the heapify-down operation to maintain the heap property after an element is extracted.
 *
 * This function performs the heapify-down operation to maintain the heap property after an element
 * is extracted from the priority queue. It compares the element at index i with its children, and if
 * any child is smaller, it swaps them and continues the process until the element is in the correct
 * position or reaches the leaf level of the heap.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @param i The index of the element to heapify-down.
 */
template <class T>
void MutablePriorityQueue<T>::heapifyDown(unsigned i) {
    auto x = H[i];
    while (true) {
        unsigned k = leftChild(i);
        if (k >= H.size())
            break;
        if (k + 1 < H.size() && *H[k + 1] < *H[k])
            ++k;
        if (!(*H[k] < *x))
            break;
        set(i, H[k]);
        i = k;
    }
    set(i, x);
}

/**
 * @brief Sets the element at the given index in the priority queue.
 *
 * This function sets the element at the given index in the priority queue. It updates the vector H
 * and also updates the queueIndex of the element to reflect its new position in the priority queue.
 *
 * @tparam T The type of elements stored in the priority queue.
 * @param i The index of the element to set.
 * @param x The element to set.
 */
template <class T>
void MutablePriorityQueue<T>::set(unsigned i, T *x) {
    H[i] = x;
    x->queueIndex = i;
}
