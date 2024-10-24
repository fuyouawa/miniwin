#pragma once
#include <vector>
#include <optional>
#include <cassert>

namespace miniwin {
template<class T>
class ListConstIterator;
template<class T>
class ListIterator;

// 线性数组的数据结构
// 虽然在c++标准库中list是链表, 但是由于考虑到可能会和向量的Vector命名混淆, 所以这里叫做List
// 而且大多数情况下线性数组(vector)确实够用了, 链表只有开销更大, Qt6中也是将QList也等同于QVector
template<class T>
class List
{
public:
	using iterator = ListIterator<T>;
	using const_iterator = ListConstIterator<T>;
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using difference_type = intptr_t;
	using size_type = size_t;

	List() = default;
	explicit List(size_t size) : vec_(size) { }
	List(std::initializer_list<T> args) : vec_(args) {}

	size_t size() const { return vec_.size(); }
	size_t capacity() const { return vec_.capacity(); }

	auto data() const { return vec_.data(); }
	auto data() { return vec_.data(); }
	bool empty() const { return vec_.empty(); }

	void resize(size_t size) { vec_.resize(size); }

	iterator begin() { return { 0, this }; }
	const_iterator begin() const { return { 0, this }; }

	iterator end() { return { size(), this}; }
	const_iterator end() const { return { size(), this }; }

	void Clear() { vec_.clear(); }

	size_t Erase(const T& val);
	size_t EraseIf(std::invocable<const T&> auto&& func);
	iterator Erase(const_iterator where);
	iterator Erase(const_iterator where, size_type count);
	iterator Erase(const_iterator first, const_iterator last);

	size_t IndexOf(const T& t) const;
	const_iterator Find(const T& t) const;
	iterator Find(const T& t);

	const_iterator FindIf(std::invocable<const T&> auto&& func) const;
	iterator FindIf(std::invocable<const T&> auto&& func);

	void PushBack(std::convertible_to<T> auto&& val);
	void EmplaceBack(auto&&... args);

	void SwapElem(size_t index, size_t index2);
	void SwapElem(iterator iter, iterator iter2);
	void Swap(List& other);

	iterator Insert(const_iterator where, const size_type count, const T& val);
	iterator Insert(const_iterator where, const T& val);

	const T& operator[](size_type off) const { return vec_[off]; }
	T& operator[](size_type off) { return vec_[off]; }

private:
	friend class ListConstIterator<T>;
	friend class ListIterator<T>;

	auto ToStdIter(const ListConstIterator<T>& iter) const;
	auto ToStdIter(const ListIterator<T>& iter);
	const_iterator FromStdIter(const typename std::vector<T>::const_iterator& iter) const;
	iterator FromStdIter(const typename std::vector<T>::iterator& iter);

	std::vector<T> vec_;
};


template<class T>
class ListConstIterator
{
public:
	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = typename List<T>::value_type;
	using size_type = typename List<T>::size_type;
	using difference_type = typename List<T>::difference_type;
	using pointer = typename List<T>::const_pointer;
	using reference = const value_type&;

	ListConstIterator(size_type index, const List<T>* owner) : index_(index), owner_(owner) {}

	bool IsBegin() const { return index_ == 0; }
	bool IsEnd() const { return index_ == owner_->size(); }
	bool IsValid() const { return index_ < owner_->size(); }

	size_type index() const { return index_; }

	reference operator*() const { return StdIter().operator*(); }
	pointer operator->() const { return StdIter().operator->(); }

	//TODO 边界检查
	ListConstIterator& operator++() { ++index_; return *this; }
	ListConstIterator operator++(int) { auto tmp = *this; ++*this; return tmp; }
	ListConstIterator& operator--() { --index_; return *this; }
	ListConstIterator operator--(int) { auto tmp = *this; --*this; return tmp; }

	ListConstIterator& operator+=(const difference_type off) { index_ += off; return *this; }
	ListConstIterator& operator+(const difference_type off) const { auto tmp = *this; tmp += off; return tmp; }
	ListConstIterator& operator-=(const difference_type off) { index_ -= off; return *this; }
	ListConstIterator& operator-(const difference_type off) const { auto tmp = *this; tmp -= off; return tmp; }
	difference_type operator-(const ListConstIterator& right) const { return static_cast<difference_type>(index_ - right.index_); }

	reference operator[](const difference_type off) const { return *(*this + off); }
	bool operator==(const ListConstIterator& right) const
	{
		return index_ == right.index_ && owner_ == right.owner_;
	}

	std::strong_ordering operator<=>(const ListConstIterator& right) const { return index_ <=> right.index_; }

private:
	auto StdIter() const { return owner_->ToStdIter(*this); }

protected:
	const List<T>* owner_;
	size_t index_;
};

template<class T>
class ListIterator : public ListConstIterator<T>
{
public:
	using Base = ListConstIterator<T>;

	using iterator_concept = std::contiguous_iterator_tag;
	using iterator_category = std::random_access_iterator_tag;
	using value_type = typename List<T>::value_type;
	using size_type = typename List<T>::size_type;
	using difference_type = typename List<T>::difference_type;
	using pointer = typename List<T>::pointer;
	using reference = value_type&;

	ListIterator(size_type index, List<T>* owner) : ListConstIterator<T>(index, owner) {}

	reference operator*() const { return const_cast<reference>(Base::operator*()); }
	pointer operator->() const { return const_cast<reference>(Base::operator->()); }

	ListIterator& operator++() { Base::operator++(); return *this; }
	ListIterator operator++(int) { auto tmp = *this; Base::operator++(); return tmp; }
	ListIterator& operator--() { Base::operator--(); return *this; }
	ListIterator operator--(int) { auto tmp = *this; Base::operator--(); return tmp; }

	ListIterator& operator+=(const difference_type off) { Base::operator+=(off); return *this; }
	ListIterator operator+(const difference_type off) { auto tmp = *this; tmp += off; return tmp; }
	ListIterator& operator-=(const difference_type off) { Base::operator-=(off); return *this; }
	ListIterator operator-(const difference_type off) { auto tmp = *this; tmp -= off; return tmp; }
	using Base::operator--;

	reference operator[](const difference_type off) const { return const_cast<reference>(Base::operator[](off)); }

private:
	auto StdIter() { return const_cast<List<T>*>(this->owner_)->ToStdIter(*this); }
};

template <class T>
size_t List<T>::Erase(const T& val)
{
	return std::erase(vec_, val);
}

template <class T>
size_t List<T>::EraseIf(std::invocable<const T&> auto&& func)
{
	return std::erase_if(vec_, std::forward<decltype(func)>(func));
}

template <class T>
typename List<T>::iterator List<T>::Erase(const_iterator where)
{
	return FromStdIter(vec_.erase(ToStdIter(where)));
}

template <class T>
typename List<T>::iterator List<T>::Erase(const_iterator where, size_type count)
{
	return Erase(where, where + count);
}

template <class T>
typename List<T>::iterator List<T>::Erase(const_iterator first, const_iterator last)
{
	return FromStdIter(vec_.erase(ToStdIter(first), ToStdIter(last)));
}

template<class T>
size_t List<T>::IndexOf(const T& t) const
{
	for (size_t i = 0; i < vec_.size(); i++)
	{
		if (vec_[i] == t)
			return i;
	}
	return static_cast<size_type>(-1);
}

template<class T>
typename List<T>::const_iterator List<T>::Find(const T& t) const
{
	return FromStdIter(std::ranges::find(vec_, t));
}

template<class T>
typename List<T>::iterator List<T>::Find(const T& t)
{
	return FromStdIter(std::ranges::find(vec_, t));
}

template<class T>
typename List<T>::const_iterator List<T>::FindIf(std::invocable<const T&> auto&& func) const
{
	return FromStdIter(std::ranges::find_if(vec_, std::forward<decltype(func)>(func)));
}

template<class T>
typename List<T>::iterator List<T>::FindIf(std::invocable<const T&> auto&& func)
{
	return FromStdIter(std::ranges::find_if(vec_, std::forward<decltype(func)>(func)));
}

template <class T>
void List<T>::PushBack(std::convertible_to<T> auto&& val)
{
	vec_.push_back(std::forward<decltype(val)>(val));
}

template <class T>
void List<T>::EmplaceBack(auto&&... args)
{
	vec_.emplace_back(std::forward<decltype(args)>(args)...);
}

template<class T>
void List<T>::SwapElem(iterator iter, iterator iter2)
{
	std::swap(*iter, *iter2);
}

template <class T>
void List<T>::Swap(List& other)
{
	vec_.swap(other.vec_);
}

template <class T>
typename List<T>::iterator List<T>::Insert(const_iterator where, const size_type count, const T& val)
{
	return FromStdIter(vec_.insert(ToStdIter(where), count, val));
}

template <class T>
typename List<T>::iterator List<T>::Insert(const_iterator where, const T& val)
{
	return Insert(where, 1, val);
}

template <class T>
auto List<T>::ToStdIter(const ListConstIterator<T>& iter) const
{
	if (!iter.IsValid()) {
		return vec_.end();
	}
	return vec_.begin() + iter.index();
}

template <class T>
auto List<T>::ToStdIter(const ListIterator<T>& iter)
{
	if (!iter.IsValid()) {
		return vec_.end();
	}
	return vec_.begin() + iter.index();
}

template <class T>
typename List<T>::const_iterator List<T>::FromStdIter(const typename std::vector<T>::const_iterator& iter) const
{
	auto diff = iter - vec_.begin();
	assert(diff >= 0);
	return { static_cast<size_type>(diff), this };
}

template <class T>
typename List<T>::iterator List<T>::FromStdIter(const typename std::vector<T>::iterator& iter)
{
	auto diff = iter - vec_.begin();
	assert(diff >= 0);
	return { static_cast<size_type>(diff), this };
}

template<class T>
void List<T>::SwapElem(size_t index, size_t index2)
{
	assert(index < size() && index2 < size());
	SwapElem(begin() + index, begin() + index2);
}
}