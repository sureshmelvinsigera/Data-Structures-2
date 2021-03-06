#include "LinkedStack.hpp"

template <class StackType>
LinkedStack<StackType>::LinkedStack(): top_(nullptr), size_(0) {}

template <class StackType>
LinkedStack<StackType>::LinkedStack(const LinkedStack<StackType>& aStack) {
  Node<StackType>* original_chain_ptr = aStack.top_;
  if (original_chain_ptr == nullptr) {
    top_ = nullptr; // Original stack is empty.
    size_ = 0;
  } else {
    size_ = aStack.size_;
    // Copy first node.
    top_ = new Node<StackType>();
    top_->SetData(original_chain_ptr->GetData());
    // Point to first node in new chain.
    Node<StackType>* new_chain_ptr = top_;
    // Advance original chain pointer.
    original_chain_ptr = original_chain_ptr->GetNext();
    // Copy remaining nodes.
    while (original_chain_ptr != nullptr) {
      // Get next item from original chain.
      StackType next = original_chain_ptr->GetData();
      // Create a new node containing the next item.
      Node<StackType>* new_node_ptr = new Node<StackType>(next);
      // Link new node to end of new chain.
      new_chain_ptr->SetNext(new_node_ptr);
      // Advance pointer to new last node.
      new_chain_ptr = new_chain_ptr->GetNext();
      // Advance original chain pointer.
      original_chain_ptr = original_chain_ptr->GetNext();
    }
    new_chain_ptr->SetNext(nullptr);
  }
}

template <class StackType>
LinkedStack<StackType>::~LinkedStack() {
  while (!IsEmpty())
    Pop();
}

template <class StackType>
bool LinkedStack<StackType>::Push(const StackType& entry) throw(MemoryAllocationExcept){
  Node<StackType>* new_node_ptr = new Node<StackType>(entry, top_);
// Node<StackType>* new_node_ptr = nullptr;
// ^uncomment to test MemoryAllocationExcept
  if (new_node_ptr == nullptr) {
    throw MemoryAllocationExcept();
    return false;
  }
  top_ = new_node_ptr;
  size_++;
  new_node_ptr = nullptr;
  return true;
}

template <class StackType>
bool LinkedStack<StackType>::Pop() {
  bool result = false;
  if (!IsEmpty()) {
    // Stack is not empty; delete top_
    Node<StackType>* node_to_delete = top_;
    top_ = top_->GetNext();
    // Return deleted node to memory
    node_to_delete->SetNext(nullptr);
    delete node_to_delete;
    node_to_delete = nullptr;

    size_--;

    result = true;
  }
  return result;
}

template <class StackType>
StackType LinkedStack<StackType>::Peek() const throw(PrecondViolatedExcept) {
  if (IsEmpty())
    throw PrecondViolatedExcept("Peek() called with empty stack");
  else
    return top_->GetData();
}


template <class StackType>
bool LinkedStack<StackType>::IsEmpty() const {
  return top_ == nullptr && size_ == 0;;
}

template <class StackType>
int LinkedStack<StackType>::GetSize() const {
  return size_;
}
