#pragma once
#include <memory>
#include <vector>
#include<iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"

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
		         value_type *_container;
		         size_type _size; 
		         size_type _capacity;
				 pointer ptr;

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
					return (ptr[n]);
				}
				const_reference operator[] (size_type n) const
				{
					return (ptr[n]);
				}

				 reference at(size_type n)
       			{
       			    if (n >= _size)
       			        throw std::out_of_range("vector");
       			    return (ptr[n]);
       			}

       			const_reference at(size_type _n) const
       			{
       			    if (_n >= _size)
       			        throw std::out_of_range("vector");
       			    return (ptr[_n]);
       			}

				reference front()
      			{
      			    return (ptr[0]);
      			}
      			const_reference front() const
      			{
      			    return (ptr[0]);
      			}

      			reference back()
      			{
      			    return (ptr[_size - 1]);
      			}

      			const_reference back() const
      			{
      			    return (ptr[_size - 1]);
      			}
 


      
}; 

