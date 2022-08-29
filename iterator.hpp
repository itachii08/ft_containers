#pragma once
#include "iterator_traits.hpp"
#include "vector.hpp"
#include <type_traits>
#include <vector>

template <typename T>
class Vector_iterator
{
    public:
        typedef T iterator_type;
        typedef typename ft::iterator_traits<T*>::difference_type   difference_type;
        typedef typename ft::iterator_traits<T*>::value_type        value_type;
        typedef typename ft::iterator_traits<T*>::pointer           pointer;
        typedef typename ft::iterator_traits<T*>::reference         reference;
        typedef typename ft::iterator_traits<T*>::iterator_category iterator_category;
        typedef Vector_iterator<const T>						const_iterator;	

    private:
        pointer p;
    public:
        Vector_iterator() : p(NULL)
        {

        }

        Vector_iterator(pointer ptr) : p(ptr)
        {

        }

        pointer base()
        {
            return (p);
        }

        template <class Iter>
        Vector_iterator (const Vector_iterator<Iter>& rev_it) //copy
        {
           this->p = rev_it.base();
        }

        // Vector_iterator(Vector_iterator const & src)
        // {
        //     *this = src;
        // }

        Vector_iterator &operator=(Vector_iterator const & src)
        {
            this->p = src.p;
            return (*this);
        }

        ~Vector_iterator() 
        {

        }

        pointer base() const
        {
            return p;
        }

        operator const_iterator() 
        {
            return (const_iterator(p));
        }
        bool operator== (Vector_iterator const & lhs) const
        {
            return (this->p == lhs.p);
        }

        bool operator!= (Vector_iterator const & lhs) const
        {
            return (this->p != lhs.p);
        }

        reference operator* ()
        {
            return (*this->p);
        }

        pointer operator-> ()
        {
            return (this->p);
        }

       reference operator=(reference src)
        {
            *this->p = src;
            return (*this);
        }

        Vector_iterator &operator++()
        {
            p++;
            return *this;
        }

        Vector_iterator operator++(int)
        {
            Vector_iterator tmp(*this);
            ++p;
            return tmp;
        }

        Vector_iterator operator--(int)
        {
            Vector_iterator tmp(*this);
            --p;
            return tmp;
        }

         Vector_iterator &operator--()
        {
            --p;
            return *this;
        }

        Vector_iterator operator+(const difference_type & other) const 
	    {
	    	return Vector_iterator(p + other);
	    }

        Vector_iterator operator-(const difference_type & other) const 
	    {
	    	return Vector_iterator(p - other);
	    }

        difference_type operator-(const Vector_iterator & other) const 
	    {
	    	return (p - other.p);
	    }

        bool operator<(const Vector_iterator & other) const
	    {
	    	return (p < other.p);
	    }
	    bool operator>(const Vector_iterator & other) const
	    {
	    	return (p > other.p);
	    }
	    bool operator<=(const Vector_iterator & other) const
	    {
	    	return (p <= other.p);
	    }
	    bool operator>=(const Vector_iterator & other) const
	    {
	    	return (p >= other.p);
	    }

        Vector_iterator &operator+=(difference_type n)
        {
            p += n;
		    return (*this);
        }

        Vector_iterator &operator-=(difference_type n)
        {
            p -= n;
		    return (*this);  
        }

        reference operator[](const difference_type & n)
        {
		    return (p[n]);
	    }

};

template <class _Iter1>
bool operator!=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return !(__x.base() == __y.base());
}

template <class _Iter1>
bool operator>(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return __y.base() > __x.base();
}

template <class _Iter1>
bool operator<(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return __y.base() < __x.base();
}

template <class _Iter1>
bool operator>=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y)
{
    return !(__x.base() < __y.base());
}

template <class _Iter1>
bool operator<=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return !(__y.base() < __x.base());
}

template <class _Iter1>
bool operator==(const Vector_iterator<_Iter1>& x, const Vector_iterator<_Iter1>& y)
{
    return (x.base() == y.base());
}

template <class _Iter>
Vector_iterator <_Iter> operator+(const typename Vector_iterator<_Iter>::difference_type n, const Vector_iterator<_Iter>& it)
{
    return (n + it);   
}

template <class _Iter>
typename Vector_iterator<_Iter>::difference_type operator-(const Vector_iterator<_Iter>& lhs, const Vector_iterator<_Iter>& rhs)
 {
    return (rhs - lhs);
 }