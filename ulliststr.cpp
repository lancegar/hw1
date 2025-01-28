#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// MY CODE  

void ULListStr::push_back(const std::string& val) {
    if(tail_ == NULL || tail_->last == ARRSIZE) {
        Item* new_item = new Item();
        if(tail_ != NULL) {
            tail_->next = new_item;
            new_item->prev = tail_;
        }

        else {
            head_ = new_item;
        }
        tail_ = new_item;
    }

    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
}

void ULListStr::pop_back() {
    if(empty()) {
        throw std::underflow_error("Empty list");
    }

    tail_->last--;
    size_--;

    if(tail_->first == tail_->last) {
        Item* temp = tail_;
        tail_ = tail_->prev;

        if(tail_ != NULL) {
            tail_->next = NULL;
        }

        else {
            head_ = NULL;
        }

        delete temp;
    }
}

void ULListStr::push_front(const std::string& val) {
    if(head_ == NULL || head_->first == 0) {
        Item* new_item = new Item();
        new_item->first = ARRSIZE;
        new_item->last = ARRSIZE;

        if(head_ != NULL) {
            head_->prev = new_item;
            new_item->next = head_;
        }

        else {
            tail_ = new_item;
        }

        head_ = new_item;
    }

    head_->first--;
    head_->val[head_->first] = val;
    size_++;
}

void ULListStr::pop_front() {
    if(empty()) {
        throw std::underflow_error("Empty list");
    }

    head_->first++;
    size_--;

    if(head_->first == head_->last) {
        Item* temp = head_;
        head_ = head_->next;

        if(head_ != NULL) {
            head_->prev = NULL;
        }

        else {
            tail_ = NULL;
        }

        delete temp;
    }
}

std::string const & ULListStr::back() const {
    if(empty()) {
        throw std::underflow_error("Empty list");
    }

    return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const {
    if(empty()) {
        throw std::underflow_error("Empty list");
    }

    return head_->val[head_->first];
}
// MY CODE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

std::string* ULListStr::getValAtLoc(size_t loc) const {
    if(loc >= size_) {
        return NULL;
    }

    Item* curr = head_;

    while(curr != NULL) {
        size_t num_elements = curr->last - curr->first;

        if(loc < num_elements) {
            return &curr->val[curr->first + loc];
        }

        loc -= num_elements;
        curr = curr->next;
    }

    return NULL;
}