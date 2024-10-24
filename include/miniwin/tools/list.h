#pragma once
#include <vector>

namespace miniwin {
template<class T>
class List;

template<class T>
class ListConstIterator : public std::vector<T>::const_iterator
{
public:
	using Inherit = std::vector<T>::const_iterator;

	ListConstIterator(const Inherit& iter, const List<T>* owner) : Inherit(iter), owner_(owner) {}

private:
	const List<T>* owner_;
};

template<class T>
class ListIterator : public std::vector<T>::iterator
{
public:
	using Inherit = std::vector<T>::iterator;

	ListIterator(const Inherit& iter, const List<T>* owner) : Inherit(iter), owner_(owner) {}

private:
	const List<T>* owner_;
};

// ������������ݽṹ
// ��Ȼ��c++��׼����list������, �������ڿ��ǵ����ܻ��������Vector��������, �����������List
// ���Ҵ�����������������(vector)ȷʵ������, ����ֻ�п�������, Qt6��Ҳ�ǽ�QListҲ��ͬ��QVector
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

	void resize(size_t size) { vec_.resize(size); }
	bool IsEmpty() const { return vec_.empty(); }

	iterator begin() { return { vec_.begin(), this }; }
	const_iterator begin() const { return { vec_.begin(), this }; }

	iterator end() { return { vec_.end(), this }; }
	const_iterator end() const { return { vec_.end(), this }; }

private:
	std::vector<T> vec_;
};
}