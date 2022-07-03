#pragma once
#include "iterator_traits.hpp"

template< class T >
class iterator
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
        iterator() : p(NULL)
        {

        }

        iterator(pointer ptr) : p(ptr)
        {

        }

        iterator(iterator const & src)
        {
            *this = src;
        }

        iterator &operator=(iterator const & src)
        {
            this->p = src.p;
            return (*this);
        }

        ~iterator() 
        {

        }

        pointer base() const
        {
            return p;
        }

        bool operator== (iterator const & lhs) const
        {
            return (this->p == lhs.p);
        }

        bool operator!= (iterator const & lhs) const
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

        iterator &operator++()
        {
            p++;
            return *this;
        }

        iterator operator++(int)
        {
            iterator tmp(*this);
            ++p;
            return tmp;
        }

        iterator operator--(int)
        {
            iterator tmp(*this);
            --p;
            return tmp;
        }

         iterator &operator--()
        {
            --p;
            return *this;
        }

        iterator operator+(const difference_type & other) const 
	    {
	    	return iterator(p + other);
	    }

        iterator operator-(const difference_type & other) const 
	    {
	    	return iterator(p - other);
	    }

        difference_type operator-(const iterator & other) const 
	    {
	    	return (p - other.p);
	    }

        bool operator<(const iterator & other) const
	    {
	    	return (p < other.p);
	    }
	    bool operator>(const iterator & other) const
	    {
	    	return (p > other.p);
	    }
	    bool operator<=(const iterator & other) const
	    {
	    	return (p <= other.p);
	    }
	    bool operator>=(const iterator & other) const
	    {
	    	return (p >= other.p);
	    }

        iterator &operator+=(difference_type n)
        {
            p += n;
		    return (*this);
        }

        iterator &operator-=(difference_type n)
        {
            p -= n;
		    return (*this);  
        }

        reference operator[](const difference_type & n)
        {
		    return (p[n]);
	    }

        template <class _Iter1>
        friend bool operator!=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator>(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y) ;
        template <class _Iter1>
        friend bool operator>=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator<=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator<(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y);
        template <class _Iter1>
        friend bool operator==(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y);
        template <class _Iter>
        friend typename iterator<T>::difference_type operator- (const iterator<_Iter>& lhs, const iterator<_Iter>& rhs);
        template <class _Iter>
        friend iterator <T> operator+ (typename iterator<_Iter>::difference_type n, const iterator<_Iter>& it);
        

};

template <class _Iter1>
bool operator!=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y) 
{
    return !(__x.p == __y.p);
}

template <class _Iter1>
bool operator>(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y) 
{
    return __y.p > __x.p;
}

template <class _Iter1>
bool operator<(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y) 
{
    return __y.p < __x.p;
}

template <class _Iter1>
bool operator>=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y)
{
    return !(__x.p < __y.p);
}

template <class _Iter1>
bool operator<=(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y) 
{
    return !(__y.p < __x.p);
}

template <class _Iter1>
bool operator==(const iterator<_Iter1>& __x, const iterator<_Iter1>& __y)
{
    return __x.p == __y.p;
}

template <class _Iter>
iterator <_Iter> operator+ (typename iterator<_Iter>::difference_type n, const iterator<_Iter>& it)
{
    return (n + it);   
}

template <class _Iter>
typename iterator<_Iter>::difference_type operator- (const iterator<_Iter>& lhs, const iterator<_Iter>& rhs)
 {
    return (rhs - lhs);
 }