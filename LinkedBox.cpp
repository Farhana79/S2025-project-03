#include <iostream>
#include "LinkedBox.hpp"

/**
     * @brief Default constructor
     * @post Sets head_ to nullptr.
     *       Initializes capacity_ to 64 and size_ to 0.
     */
template <typename T>
LinkedBox<T>::LinkedBox():head_{nullptr},capacity_{64}, size_{0} {}

/**
 * @brief Parameterized constructor
 * @param capacity A const reference to an integer to specify the capacity of the LinkedBox
 * @post Sets the head pointer to nullptr.
 *       Initializes capacity_ to the specified parameter and size_ to 0.
 * @note If the capacity is 0 or negative, 64 is used instead
 */
template<typename T>
LinkedBox<T>::LinkedBox(const int &capacity): capacity_{capacity},head_{nullptr}, size_{0} {}

/**
 * @brief Getter for the size_ member
 * @return The integer value stored within the size_ member variable
 */
template<typename T>
int LinkedBox<T>::size() const {
    return size_;
}

/**
 * @brief Getter for the capacity_ member
 * @return The integer value stored within the capacity_ member variable
 */
template<typename T>
int LinkedBox<T>::capacity() const {
    return capacity_;
}

/**
     * @brief Appends the target item to the chain such that
     *      1) The current size_ and target.getSize() is small enough
     *         that the item can be added without exceeding the LinkedBox capacity_
     *      2) A new Node whose value equals the target item is created
     *         and inserted at the head (ie. at the front of the chain)
     *
     * @param target A const reference to the item (of the templated type) to be added
     *
     * @return True if the add was successful. False otherwise.
     * @post Increment size_ (if the item was added) by the size of the added object.
     *
     * @example Given the following instructions, and a capacity 8 LinkedBox:
                addItem(Pawn)   // Pawn size = 1
                addItem(Rook)   // Rook size = 2
                addItem(Queen)  // Queen size = 3
                addItem(Pawn)   // Pawn size = 1
                addItem(Rook)   // Rook size = 2

                Our LinkedBox Chain will look like:
                "PAWN(head)->QUEEN->ROOK->PAWN" (size = 7) after all insertions.

                Notice, since Rook is of size 2, the add fails,
                as adding it would make our size exceed capacity 8.
    */
template<typename T>
bool LinkedBox<T>::addItem(const T &target) {
    // Limit capacity
    if (size_ + target.size() > capacity_) { return false; }

    // Create a new node with the target item
    Node<T> *node = new Node<T>(target);

    // Insert at the head of the chain
    node->setNext(head_);
    head_ = node;

    // Increment size_
    size_ += target.size();

    return true;
}

// Remove method
template <typename T>
bool LinkedBox<T>::remove(const std::string& type) {
    Node<T>* current = head_;
    Node<T>* previous = nullptr;

    while (current) {
        if (current->value().getType() == type) {
            if (previous) {
                previous->setNext(current->next());
            } else {
                head_ = current->next();
            }
            size_ -= current->value().size();
            delete current;
            return true;
        }
        previous = current;
        current = current->next();
    }
    return false;
}
/**
    * @brief Determines whether the LinkedBox contains an item of the specified type
    *
    * @param type A const reference to a string denoting
    *        the type of the item to search for
    *
    * @return True if items_ contains an object whose getType()
    *         equals the given parameter. False otherwise.
    */
template<typename T>
bool LinkedBox<T>::contains(const std::string &type) const {
    Node<T>* current = head_;

    while (current){
        if (current->value().getType() == type){
            return true;
        }
        current = current->next();
    }
    return false;
}
/**
     * @brief Counts the number of distinct intances of the given type stored within the chain
     *
     * @param type A const reference to a string denoting
     *        the type of the item to search for
     *
     * @return An integer representing the number of instances
     *        of objects whose type is equal to the parameter.
     */
template<typename T>
int LinkedBox<T>::count(const std::string &type) const {
    Node<T>* current = head_;
    int count = 0;
    while (current){
        if (current->value().getType() == type){
            count++;
        }
        current = current->next();
    }
    return count;
}
// display method
template <typename T>
void LinkedBox<T>::display() const {
    Node<T>* current = head_;
    while (current) {
        std::cout << current->value().getType() << " ";
        current = current->next();
    }
    std::cout << std::endl;
}