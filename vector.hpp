#pragma once
#include <memory>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include <iterator>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector;
}

template <class T, class Alloc>
class ft::vector
{
	// Member Types
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::size_type size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer pointer;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef Vector_iterator<value_type> iterator;
	typedef Vector_iterator<const value_type> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

private:
	allocator_type _alloc;
	size_type _size;
	size_type _capacity;
	pointer _container;

public:
	explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _container(NULL)
	{
	}

	explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _container(NULL)
	{
		_container = _alloc.allocate(n);
		for (size_type i = 0; i < n; i++)
		{
			_alloc.construct(_container + i, val);
		}
	}

	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
		   const allocator_type &alloc = allocator_type(),
		   typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *f = NULL)
	{
		f = NULL;
		_alloc = alloc;
		size_type n = 0;
		size_type i = 0;
		InputIterator tmp(first);
		while (tmp != last)
		{
			tmp++;
			n++;
		}
		_size = n;
		_capacity = n;
		_container = _alloc.allocate(n);
		while (first != last)
		{
			_alloc.construct(_container + i, *(first));
			i++;
			first++;
		}
	}

	vector(const vector &x)
	{
		*this = x;
	}

	vector &operator=(const vector &x)
	{
		// if (_capacity)
		// {
		// 	clear();
		// 	_alloc.deallocate(_container, _capacity); // check
		// }
		_alloc = x._alloc;
		_size = x._size;
		_capacity = x._capacity;

		_container = _alloc.allocate(_capacity);

		for (size_t i = 0; i < _size; i++)
		{
			_alloc.construct(_container + i, x._container[i]);
		}
		return (*this);
	}

	void clear()
	{
		size_t i;
		i = 0;
		while (i < _size)
		{
			_alloc.destroy(&_container[i]);
			i++;
		}
		_size = 0;
	}

	~vector()
	{
		this->clear();
		_alloc.deallocate(_container, _capacity);
	};

	// iterators fonctions//

	iterator begin()
	{
		return iterator(_container);
	}

	const_iterator begin() const
	{
		return const_iterator(_container);
	}

	iterator end()
	{
		return (iterator(&_container[_size]));
	}
	const_iterator end() const
	{
		return (const_iterator(&_container[_size]));
	}
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}
	reverse_iterator rend()
	{
		return reverse_iterator(this->begin());
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(this->begin());
	}

	// Capacity//

	size_type size() const
	{
		return (_size);
	}
	size_type max_size() const
	{
		return (_alloc.max_size());
	}

	void reserve(size_type n)
	{
		if (n < _capacity)
			return;
		else if (n > max_size())
		{
			throw std::length_error("error length");
			return;
		}
		pointer ptr = _container;
		_container = _alloc.allocate(n);
		for (size_t i = 0; i < _size; ++i)
		{
			_alloc.construct(&_container[i], ptr[i]);
			_alloc.destroy(&ptr[i]);
		}
		_alloc.deallocate(ptr, _capacity);
		_capacity = n;
	}

	void resize(size_type n, value_type val = value_type())
	{
		if (n == _size)
			return;
		if (n < _size)
		{
			for (size_t i = n; i < _size; ++i)
				_alloc.destroy(&_container[i]);
			_size = n;
			return;
		}
		else if (n > _capacity || n > _size)
			reserve(n);
		for (size_t i = _size; i < n; ++i)
			_alloc.construct(&_container[i], val);
		_size = n;
	}

	size_type capacity() const
	{
		return _capacity;
	}

	bool empty() const
	{
		if (_size == 0)
			return true;
		return false;
	}

	// Element access

	reference operator[](size_type n)
	{
		return (_container[n]);
	}
	const_reference operator[](size_type n) const
	{
		return (_container[n]);
	}

	reference at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return (_container[n]);
	}

	const_reference at(size_type _n) const
	{
		if (_n >= _size)
			throw std::out_of_range("vector");
		return (_container[_n]);
	}

	reference front()
	{
		return (_container[0]);
	}
	const_reference front() const
	{
		return (_container[0]);
	}

	reference back()
	{
		return (_container[_size - 1]);
	}

	const_reference back() const
	{
		return (_container[_size - 1]);
	}

	// Modifiers

	void swap(vector &x)
	{
		pointer tmp;
		size_type tmpsiz;
		size_type tmpcap;

		tmp = this->_container;
		tmpsiz = this->_size;
		tmpcap = this->_capacity;

		this->_container = x._container;
		this->_size = x._size;
		this->_capacity = x._capacity;

		x._container = tmp;
		x._capacity = tmpcap;
		x._size = tmpsiz;
	}

	void push_back(const value_type &val)
	{
		if (_size == 0)
			reserve(1);
		else if (_size == _capacity)
			reserve(_capacity * 2);
		_alloc.construct(_container + _size, val);
		_size++;
	}

	void pop_back()
	{
		_alloc.destroy(&_container[_size]);
		_size--;
	}

	void assign(size_type n, const T &x)
	{
		if (n > _capacity)
		{
			_alloc.deallocate(_container, _capacity);
			_container = _alloc.allocate(n);
			_capacity = n;
		}
		for (size_type i = 0; i < n; ++i)
			_alloc.construct(&_container[i], x);
		_size = n;
	}

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last,
				typename enable_if<!is_integral<InputIterator>::value>::type *f = NULL)
	{
		f = NULL;
		size_type n = std::distance(first, last);
		if (n > _capacity)
		{
			_alloc.deallocate(_container, _capacity);
			_container = _alloc.allocate(n);
			_capacity = n;
		}
		for (size_type i = 0; i < n; ++i)
			_alloc.construct(&_container[i], *first++);
		_size = n;
	}

	iterator erase(iterator pos)
	{
		for (size_type i = pos - _container; i < _size - 1; ++i)
			_container[i] = _container[i + 1];
		_size--;
		return pos;
	}

	iterator erase(iterator first, iterator last)
	{
		size_type n = std::distance(first, last);
		for (size_type i = first - _container; i < _size - n; ++i)
			_alloc.construct(&_container[i], _container[i + n]);
		_size -= n;
		return first;
	}

	iterator insert(iterator position, const value_type &val)
	{
		size_type p;
		size_type len;

		p = std::distance(this->begin(), position);

		if (this->_size == this->_capacity)
		{
			if (this->_capacity == 0)
				len = 1;
			else
				len = this->_capacity * 2;
			this->reserve(len);
		}

		for (size_type i = (this->_size); i > p; i--)
		{
			this->_alloc.construct(this->_container + i, *(this->_container + i - 1));
		}

		this->_alloc.construct(this->_container + p, val);

		this->_size++;

		return (iterator(this->_container + p));
	}

	void insert(iterator position, size_type n, const value_type &val)
	{
		difference_type p = std::distance(this->begin(), position);
		size_type len;
		if (this->_size == this->_capacity)
		{
			if (this->_capacity == 0)
				len = n;
			else
				len = _capacity * 2;
			if (len < _size + n)
				len = _size + n;
			this->reserve(len);
		}
		for (difference_type i = _size - 1; i >= p; --i)
			this->_alloc.construct(_container + i + n, *(_container + i));
		for (size_t i = 0; i < n; i++)
			this->_alloc.construct(_container + p + i, val);
		_size += n;
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		size_type len;
		size_type dis;
		difference_type pos;

		pos = std::distance(begin(), position);
		dis = (std::distance(first, last));

		if (this->_size == _capacity)
		{
			if (this->_capacity == 0)
				len = dis;
			else
				len = this->_capacity * 2;
			if (len < (this->_size + dis))
				len = (this->_size + dis);
			this->reserve(len);
		}

		for (difference_type i = (this->_size - 1); i >= pos; --i)
		{
			this->_alloc.construct(this->_container + i + dis, *(this->_container + i));
		}
		for (size_t i = 0; i < dis; i++)
		{
			this->_alloc.construct(this->_container + pos + i, *(first + i));
		}

		this->_size += dis;
	}

	allocator_type get_allocator() const
	{
		return (_alloc);
	}
};

template <class Tp, class Alloc>
bool operator==(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Tp, class Alloc>
bool operator!=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return !(lhs == rhs);
}
template <class Tp, class Alloc>
bool operator<(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return ft::lexicographical_compare(lhs.begin(), lhs.end(),
									   rhs.begin(), rhs.end());
}

template <class Tp, class Alloc>
bool operator<=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return !(rhs < lhs);
}

template <class Tp, class Alloc>
bool operator>(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{
	return rhs < lhs;
}

template <class Tp, class Alloc>
bool operator>=(const ft::vector<Tp, Alloc> &lhs, const ft::vector<Tp, Alloc> &rhs)
{

	return !(lhs < rhs);
}

template <class Tp, class Alloc>
void swap(ft::vector<Tp, Alloc> &x, ft::vector<Tp, Alloc> &y)
{
	x.swap(y);
}