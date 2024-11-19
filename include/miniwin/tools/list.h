#pragma once
#include <vector>

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
	explicit List(size_type size) : vec_(size) { }
	List(std::initializer_list<T> args) : vec_(args) {}

	size_type size() const { return vec_.size(); }
	size_type capacity() const { return vec_.capacity(); }

	const T* data() const { return vec_.data(); }
	T* data() { return vec_.data(); }
	bool empty() const { return vec_.empty(); }

	void resize(size_type size) { vec_.resize(size); }

	iterator begin() { return { 0, this }; }
	const_iterator begin() const { return { 0, this }; }

	iterator end() { return { size(), this}; }
	const_iterator end() const { return { size(), this }; }

	void Clear() { vec_.clear(); }

	size_type Erase(const T& val);
	size_type EraseIf(auto&& func);
	iterator Erase(const_iterator where);
	iterator Erase(const_iterator where, size_type count);
	iterator Erase(const_iterator first, const_iterator last);
	iterator RemoveIf(auto&& func);

	size_type IndexOf(const T& t) const;
	const_iterator Find(const T& t) const;
	iterator Find(const T& t);

	const_iterator FindIf(auto&& func) const;
	iterator FindIf(auto&& func);

	void PushBack(const T& val);
	void PushBack(T&& val);
	T& EmplaceBack(auto&&... args);

	void SwapElem(size_type index, size_type index2);
	void SwapElem(iterator iter, iterator iter2);
	void Swap(List& other);

	iterator Insert(const_iterator where, const size_type count, const T& val);
	iterator Insert(const_iterator where, const T& val);

	iterator Insert(const_iterator where, const size_type count, T&& val);
	iterator Insert(const_iterator where, T&& val);

	const T& operator[](size_type off) const { return vec_[off]; }
	T& operator[](size_type off) { return vec_[off]; }

	List Filter(auto&& pr) const;
	template<class E>
	List<E> Transform(auto&& pr) const;

private:
	friend class ListConstIterator<T>;
	friend class ListIterator<T>;

	auto ToStdIter(const ListConstIterator<T>& iter) const;
	auto ToStdIter(const ListIterator<T>& iter);
	const_iterator FromStdIter(const typename std::vector<T>::const_iterator& iter) const;
	iterator FromStdIter(const typename std::vector<T>::iterator& iter);

	std::vector<T> vec_;
};

namespace internal {
void VerifyIndex(size_t index, size_t size);
void VerifyIndex(size_t index, intptr_t off, size_t size);
void VerifyDiff(intptr_t diff);
void VerifyAddIndex(size_t index, intptr_t off, size_t size);
void VerifySubIndex(size_t index, intptr_t off, size_t size);
}


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

	ListConstIterator() = default;
	ListConstIterator(size_type index, const List<T>* owner) : owner_(owner), index_(index) {}

	bool IsBegin() const { return index_ == 0; }
	bool IsEnd() const { return index_ == owner_->size(); }

	size_type index() const { return index_; }

	reference operator*() const { return StdIter().operator*(); }
	pointer operator->() const { return StdIter().operator->(); }

	//TODO 边界检查
	ListConstIterator& operator++();
	ListConstIterator operator++(int) { auto tmp = *this; ++*this; return tmp; }
	ListConstIterator& operator--();
	ListConstIterator operator--(int) { auto tmp = *this; --*this; return tmp; }

	ListConstIterator& operator+=(const difference_type off);
	ListConstIterator operator+(const difference_type off) const { auto tmp = *this; tmp += off; return tmp; }
	ListConstIterator& operator-=(const difference_type off);
	ListConstIterator operator-(const difference_type off) const { auto tmp = *this; tmp -= off; return tmp; }
	difference_type operator-(const ListConstIterator& right) const { return static_cast<difference_type>(index_) - right.index_; }

	reference operator[](const difference_type off) const;

	bool operator==(const ListConstIterator& right) const {
		return index_ == right.index_ && owner_ == right.owner_;
	}
	bool operator!=(const ListConstIterator& right) const {
		return !operator==(right);
	}

	std::strong_ordering operator<=>(const ListConstIterator& right) const { return index_ <=> right.index_; }

private:
	auto StdIter() const { return owner_->ToStdIter(*this); }

protected:
	const List<T>* owner_ = nullptr;
	size_type index_ = 0;
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

	ListIterator() = default;
	ListIterator(size_type index, List<T>* owner) : ListConstIterator<T>(index, owner) {}

	reference operator*() const { return const_cast<reference>(Base::operator*()); }
	pointer operator->() const { return const_cast<pointer>(Base::operator->()); }

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
typename List<T>::size_type List<T>::Erase(const T& val)
{
	return std::erase(vec_, val);
}

template <class T>
typename List<T>::size_type List<T>::EraseIf(auto&& func)
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

template <class T>
typename List<T>::iterator List<T>::RemoveIf(auto&& func)
{
	return FromStdIter(std::remove_if(vec_.begin(), vec_.end(), func));
}

template<class T>
typename List<T>::size_type List<T>::IndexOf(const T& t) const
{
	for (size_type i = 0; i < vec_.size(); i++)
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
typename List<T>::const_iterator List<T>::FindIf(auto&& func) const
{
	return FromStdIter(std::ranges::find_if(vec_, std::forward<decltype(func)>(func)));
}

template<class T>
typename List<T>::iterator List<T>::FindIf(auto&& func)
{
	return FromStdIter(std::ranges::find_if(vec_, std::forward<decltype(func)>(func)));
}

template <class T>
void List<T>::PushBack(const T& val) {
	vec_.push_back(val);
}

template <class T>
void List<T>::PushBack(T&& val)
{
	vec_.push_back(std::move(val));
}

template <class T>
T& List<T>::EmplaceBack(auto&&... args)
{
	return vec_.emplace_back(std::forward<decltype(args)>(args)...);
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
typename List<T>::iterator List<T>::Insert(const_iterator where, const size_type count, const T& val) {
	return FromStdIter(vec_.insert(ToStdIter(where), count, val));
}

template <class T>
typename List<T>::iterator List<T>::Insert(const_iterator where, const T& val)
{
	return Insert(where, 1, val);
}

template <class T>
typename List<T>::iterator List<T>::Insert(const_iterator where, const size_type count, T&& val)
{
	return FromStdIter(vec_.insert(ToStdIter(where), count, std::move(val)));
}

template <class T>
typename List<T>::iterator List<T>::Insert(const_iterator where, T&& val)
{
	return Insert(where, 1, std::move(val));
}

template <class T>
List<T> List<T>::Filter(auto&& pr) const {
	List ret;
	for (auto& x : *this) {
		if (pr(x)) {
			ret.PushBack(x);
		}
	}
	return ret;
}

template <class T>
template <class E>
List<E> List<T>::Transform(auto&& pr) const {
	List<E> ret;
	for (auto& x : *this) {
		ret.PushBack(pr(x));
	}
	return ret;
}

template <class T>
auto List<T>::ToStdIter(const ListConstIterator<T>& iter) const
{
	if (iter.IsEnd()) {
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
	internal::VerifyDiff(diff);
	return { static_cast<size_type>(diff), this };
}

template <class T>
typename List<T>::iterator List<T>::FromStdIter(const typename std::vector<T>::iterator& iter)
{
	auto diff = iter - vec_.begin();
	internal::VerifyDiff(diff);
	return { static_cast<size_type>(diff), this };
}

template <class T>
ListConstIterator<T>& ListConstIterator<T>::operator++() {
	internal::VerifyAddIndex(index_, 1, owner_->size());
	++index_;
	return *this;
}

template <class T>
ListConstIterator<T>& ListConstIterator<T>::operator--() {
	internal::VerifySubIndex(index_, 1, owner_->size());
	--index_;
	return *this;
}

template <class T>
ListConstIterator<T>& ListConstIterator<T>::operator+=(const difference_type off) {
	internal::VerifyAddIndex(index_, off, owner_->size());
	index_ += off;
	return *this;
}

template <class T>
ListConstIterator<T>& ListConstIterator<T>::operator-=(const difference_type off) {
	internal::VerifySubIndex(index_, off, owner_->size());
	index_ -= off;
	return *this;
}

template <class T>
typename ListConstIterator<T>::reference ListConstIterator<T>::operator[](const difference_type off) const {
	internal::VerifyIndex(index_, off, owner_->size());
	return *(*this + off);
}

template<class T>
void List<T>::SwapElem(size_type index, size_type index2)
{
	internal::VerifyIndex(index, size());
	internal::VerifyIndex(index2, size());
	SwapElem(begin() + index, begin() + index2);
}
}