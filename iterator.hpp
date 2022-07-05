#pragma once
#include "iterator_traits.hpp"
#include <type_traits>

template <typename T>
class Vector_iterator
{
    public:
    typedef typename ft::iterator_traits<T*>::difference_type   difference_type;
    typedef typename ft::iterator_traits<T*>::value_type        value_type;
    typedef typename ft::iterator_traits<T*>::pointer           pointer;
    typedef typename ft::iterator_traits<T*>::reference         reference;
    typedef typename ft::iterator_traits<T*>::iterator_category iterator_category;
    
    private:
        pointer p;
    public:
        Vector_iterator() : p(NULL)
        {

        }

        Vector_iterator(pointer ptr) : p(ptr)
        {

        }

        Vector_iterator(Vector_iterator const & src)
        {
            *this = src;
        }

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

        template <class _Iter1>
        friend bool operator!=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator>(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) ;
        template <class _Iter1>
        friend bool operator>=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator<=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator<(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator==(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y);
        template <class _Iter>
        friend typename Vector_iterator<T>::difference_type operator- (const Vector_iterator<_Iter>& lhs, const Vector_iterator<_Iter>& rhs);
        template <class _Iter>
        friend Vector_iterator <T> operator+ (typename Vector_iterator<_Iter>::difference_type n, const Vector_iterator<_Iter>& it);
        

};

template <class _Iter1>
bool operator!=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return !(__x.p == __y.p);
}

template <class _Iter1>
bool operator>(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return __y.p > __x.p;
}

template <class _Iter1>
bool operator<(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return __y.p < __x.p;
}

template <class _Iter1>
bool operator>=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y)
{
    return !(__x.p < __y.p);
}

template <class _Iter1>
bool operator<=(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y) 
{
    return !(__y.p < __x.p);
}

template <class _Iter1>
bool operator==(const Vector_iterator<_Iter1>& __x, const Vector_iterator<_Iter1>& __y)
{
    return __x.p == __y.p;
}

template <class _Iter>
Vector_iterator <_Iter> operator+ (typename Vector_iterator<_Iter>::difference_type n, const Vector_iterator<_Iter>& it)
{
    return (n + it);   
}

template <class _Iter>
typename Vector_iterator<_Iter>::difference_type operator- (const Vector_iterator<_Iter>& lhs, const Vector_iterator<_Iter>& rhs)
 {
    return (rhs - lhs);
 }