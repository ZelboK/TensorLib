//
// Created by Danial javady on 2023-03-10.
//

#ifndef TENSORLIB_TENSOR_H
#define TENSORLIB_TENSOR_H

#include <random>
#include "DefaultTypes.h"
#include <functional>
#include <memory>

template<int rank, Number T, bool isConst> requires (rank > 0)
class TensorIterator;

template<int rank, Number T> requires (rank > 0)
class Tensor {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = value_type *;
    using iterator = TensorIterator<rank, T, false>;
    using const_iterator = TensorIterator<rank, T, true>;
    using const_pointer = value_type const *;

    explicit Tensor(size_type size) {
        data_ =  std::shared_ptr<T[]>(new T[size], std::default_delete<T[]>());
        size_ = size;
    }

	// TODO Does this need changing because Tensor now uses a shared_ptr?
    explicit Tensor(T* data, int size) {
		data_ = std::shared_ptr<T[]>(data, std::default_delete<T[]>());
		size_ = size;
    }

    Tensor(const Tensor& other) {
        size_ = other.size_;
		data_ = std::shared_ptr<T[]>(new T[size_], std::default_delete<T[]>());
        std::copy(other.begin(), other.end(), data_.get());
    }
//	Tensor(const Tensor& other) : size_(other.size_), data_(std::make_shared<T[]>(other.size_)) {
//		std::copy(other.begin(), other.end(), data_.get());
//	}
    Tensor &operator=(const Tensor &other) {
        if (this == &other) {
            return *this;
        }
        size_ = other.size_;
        std::copy(other.data_, ot  her.data_ + size_, std::back_inserter(data_));
        return *this;
    }

    Tensor() = default;


    iterator begin() {
        return iterator(0, *this);
    }

    iterator end() {
        return iterator(size_, *this);
    }

    const_iterator begin() const {
        return const_iterator(0, *this);
    }

    const_iterator end() const {
        return const_iterator(size_, *this);
    }

    reference operator[](size_type const pos) {
        return data_[pos];
    }

    const_reference operator[](size_type const pos) const {
        return data_[pos];
    }

    size_type size() const {
        return this->size_;
    }

    bool empty() const noexcept { return size_ == 0; }

    size_type capacity() const noexcept { return size_; }

private:
    std::shared_ptr<T[]> data_;
    size_type size_ = 0;
 //   int columns; // found out at runtime
 //   int rows;

    friend TensorIterator<rank, T, true>;
	friend TensorIterator<rank, T, false>;

};

// TODO THINK ABOUT WHAT SHOULD BE PRIVATE AND PUBLIC!
template<int rank, Number T, bool isConst> requires (rank > 0)
class TensorIterator {
public:
    using value_type = T;
    using self_type = TensorIterator<rank, T, isConst>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = value_type *;
    using iterator_category = std::random_access_iterator_tag;
    using const_pointer = value_type const *;

    explicit TensorIterator(
            size_type const index,
            Tensor<rank, T> &buffer) :
            buffer_(buffer), index_(index) {}

	explicit TensorIterator(
		size_type const index,
		const Tensor<rank, T> &buffer) :
		buffer_(buffer), index_(index) {}

    self_type &operator++() {
        if (index_ >= buffer_.get().size())
            throw std::out_of_range("Iterator cannot be"
                                    " incremented past the end of the range");
        index_++;
        return *this;
    }

    self_type operator++(int) {
        self_type temp = *this;
        ++*this;
        return temp;
    }

    bool operator==(self_type const &other) const {
        return compatible(other) && index_ == other.index_;
    }

    bool operator!=(self_type const &other) const {
        return *this != other;
    }

	friend std::ostream& operator<<(std::ostream&os, TensorIterator<rank, T, isConst>& iter) {
		return os << iter.buffer_.get()[iter.index_] << " found" << std::endl;
	}

    reference operator*() {
        if (buffer_.get().empty() || !in_bounds()) {
            throw std::logic_error("Cannot dereference the iterator");
        }
        return buffer_.get().data_[index_];
    }

    const_reference operator*() const {
        if (buffer_.get().empty() || !in_bounds())
            throw std::logic_error("Cannot dereference the iterator");
        return buffer_.get().data_[index_];
    }

    const_reference operator->() const {
        if (buffer_.get().empty() || !in_bounds())
            throw std::logic_error("Cannot dereference the iterator");
        return buffer_.get().data_[index_];
    }

    self_type &operator--() {
        if (index_ <= 0)
            throw std::out_of_range("Iterator cannot be decremented before the beginning of the range");
        index_--;
        return *this;
    }

    self_type operator--(int) {
        self_type temp = *this;
        --*this;
        return temp;
    }

    self_type operator+(difference_type offset) const {
        self_type temp = *this;
        return temp += offset;
    }

    self_type operator-(difference_type offset) const {
        self_type temp = *this;
        return temp -= offset;
    }

    difference_type operator-(self_type const &other) const {
        return index_ - other.index_;
    }

    self_type &operator+=(difference_type const offset) {
        difference_type next =
                (index_ + next) % buffer_.get().capacity();
        if (next >= buffer_.get().size())
            throw std::out_of_range("Iterator cannot be incremented past the bounds of the range");
        index_ = next;
        return *this;
    }


    self_type &operator-=(difference_type const offset) {
        return *this += -offset;
    }

    bool operator<(self_type const &other) const {
        return index_ < other.index_;
    }

    bool operator<=(self_type const &other) const {
        return !(other < *this);
    }

    bool operator>=(self_type const &other) const {
        return !(*this < other);
    }

    value_type &operator[](difference_type const offset) {
        return *((*this + offset));
    }

    value_type const &operator[](difference_type const offset)
    const {
        return *((*this + offset));
    }


private:
	std::reference_wrapper<std::conditional_t<isConst, const Tensor<rank, T>, Tensor<rank, T>>
			> buffer_;


	size_type index_ = 0;

    bool compatible(self_type const &other) const {
        return buffer_.get().data_ ==
               other.buffer_.get().data_;
    }

    bool in_bounds() const {
        return
                !buffer_.get().empty() &&
                index_ <= buffer_.get().capacity();
    }

};



#endif //TENSORLIB_TENSOR_H


/*
 * i need to be able to organize my data in such a way that i can map tensors   `
 * in their abstract form to their implemented form
 * So this naturally draws the question of how do I define the boundaries
 * Of these tensors exactly? At what point(since it's represented as a 1D array)
 * Do i say hey: You are now belonging to row and col: N.
 * Should i simply return a formula for computing this? it's a simple operation
 * But one that would need to be done... repeatedly? No, it can be cached.
 *
 */