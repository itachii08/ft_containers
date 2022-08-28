#pragma once
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"
#include <iterator>

namespace ft
{
   template < class T, class Alloc = std::allocator<T> > 
   class vector;
}

template <class T, class Alloc>
class ft::vector
{
        //Member Types
        public:
            typedef T                                        value_type;
            typedef Alloc                                    allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef Vector_iterator<value_type>              iterator;
            typedef Vector_iterator<const value_type>        const_iterator;
            typedef ft::reverse_iterator<iterator>           reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

            private:
		         allocator_type _alloc;
		         size_type _size; 
		         size_type _capacity;
				 pointer _container;

            public:
		    	explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(0), _capacity(0)
		    	{
		    	}
               
            	explicit vector (size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _container(NULL), _size(n), _capacity(n)
		         {
		         	_container = _alloc.allocate(n);
		         	for (unsigned long i = 0; i < n; i++)
		         	{
		         		_container[i] = val;
		         	}
		         }

               template <class InputIterator> 
               vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
               typename enable_if<!is_integral<InputIterator>::value>::type* = NULL) : _alloc(alloc)
               {
                  	_size = last - first;
			    	_capacity = _size;
			    	_container = _alloc.allocate(_capacity);
			    	pointer ptr;
			    	ptr = _container;
			    	int i = 0;
			    	for (InputIterator it = first; it != last; it++)
			    	{
			    		_container[i++] = *it;
			    	}
               }

               vector (const vector& x)
               {
                 *this = x;
               }

               vector &operator=(const vector &x)
		         {
		         	_alloc = x._alloc;
		         	_size = x._size;
		         	_capacity = x._capacity;
		         	_container = _alloc.allocate(_capacity);
		         	for (size_t i = 0; i < _size; i++)
		         	{
		         		_container[i] = x._container[i];
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
               

				//iterators fonctions//

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

				//Capacity//

		    	size_type size() const
		    	{
		    		return (_size);
		    	}
		    	size_type max_size() const
		    	{
		    		return (_alloc.max_size());
		    	}

				void reserve( size_type n )
				{
					if (n < _capacity)
						return ;
					else if (n > max_size())
						throw std::length_error("error length");
					pointer t = _container;
					_container = _alloc.allocate(n);
					for (size_t i = 0; i < _size; ++i)
					{
						_alloc.construct(&_container[i], t[i]);
						_alloc.destroy(&t[i]);
					}
					_alloc.deallocate(t, _capacity);
					_capacity = n;
				}

					void resize( size_type n, value_type val = value_type() )
				{
					if (n == _size)
						return ;
					if (n < _size)
					{
						for (size_t i = n; i < _size; ++i)
							_alloc.destroy(&_container[i]);
						_size = n;
						return ;
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
           		    else
           		        return false;
           		}

				//Element access

				reference operator[] (size_type n)
				{
					return (_container[n]);
				}
				const_reference operator[] (size_type n) const
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

				//Modifiers
 
        		void swap(vector &x)
        		{
        		    pointer tmparr;
        		    size_type tmpcapacity;
        		    size_type tmpsize;

        		    tmparr = this->_container;
        		    tmpcapacity = this->_capacity;
        		    tmpsize = this->_size;

        		    this->_container = x._container;
        		    this->_capacity = x._capacity;
        		    this->_size = x._size;

        		    x._container = tmparr;
        		    x._capacity = tmpcapacity;
        		    x._size = tmpsize;
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
        		        _alloc.construct(&_container[i] , x);
        		    _size = n;
        		}

        		template <class InputIterator>
        		void assign(InputIterator first, InputIterator last,
        		            typename enable_if<!is_integral<InputIterator>::value>::type *f = NULL)
        		{
        		    (void)f;
        		    size_type n = std::distance(first, last);
        		    if (n > _capacity)
        		    {
        		        _alloc.deallocate(_container, _capacity);
        		        _container = _alloc.allocate(n);
        		        _capacity = n;
        		    }
        		    for (size_type i = 0; i < n; ++i)
        		        _alloc.construct(&_container[i] , *first++);
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
        		        _alloc.construct(&_container[i] , _container[i + n]);
        		    _size -= n;
        		    return first;
        		}

        		iterator insert(iterator position, const value_type &val)
        		{
        		    size_type i = 0;
        		    size_type o = position - this->begin();
        		    if (_size == 0)
        		        push_back(val);
        		    else
        		    {
        		        if (_size + 1 > _capacity)
        		            reserve(_capacity * 2);
        		        while (_size - i + 1 > 0)
        		        {
        		            if (_size - i == o)
        		            {
        		                _alloc.construct(&_container[_size - i] , val);
        		                break;
        		            }
        		            else
        		                _alloc.construct(&_container[_size - i] , _container[_size - i - 1]);
        		            i++;
        		        }
        		        _size++;
        		    }
        		    return (_container + o);
        		}

        		void insert(iterator position, size_type n, const value_type &val)
        		{
        		    size_type o = position - this->begin();
        		    size_type i = 0;
        		    size_type k = n;
        		    if (_size + n > _capacity)
        		    {
        		        if (_size + n < _size * 2)
        		            reserve(!(_size )? 1 : (_size * 2));
        		        else
        		            reserve(!(_size + n)? 1 : (_size + n ));

        		    }
        		    while (_size - i + n > 0)
        		    {
        		        if (_size - i == o)
        		        {
        		            while (k--)
        		                _alloc.construct(&_container[_size - i + k] , val);
        		            break;
        		        }
        		        else
        		            _alloc.construct(&_container[_size - i + n - 1] , _container[_size - i - 1]);
        		        i++;
        		    }
        		    _size += n;
        		}

        		template <class InputIterator>
    			void insert (iterator position, InputIterator first, InputIterator last)
        		{
        		    size_type n = std::distance(first, last);
        		    size_type i = 0;
        		    size_type pos = position - begin();
        		    if (_capacity < _size + n && n <= _size)
        		        reserve(_capacity * 2);
        		    else if (_size + n > _capacity)
        		        reserve(_capacity + n);
        		    while (_size + n - i > 0)
        		    {
        		        if (_size - i == pos)
        		        {
        		            pos = n;
        		            try
        		            {
        		                while (pos--)
        		                   _alloc.construct(&_container[_size - i + pos], *(--last));
        		            }
        		            catch (...)
        		            {
        		                for (size_type i = size(); i != 0; i--)
        		                {
								
        		                    std::cout << "i =  " << i << std::endl;
        		                    _alloc.destroy(&_container[i - 1]);
        		                }
        		                _capacity = 0;
        		                throw 3;
        		            }
        		            break;
        		        }
        		        else
        		            _alloc.construct(&_container[_size - i + n - 1] ,  _container[_size - i - 1]);
        		        i++;
        		    }
        		    _size += n;
        		}
}; 

