#pragma once
#include<iostream>
#include "iterator_traits.hpp"

namespace ft
{
    template <class Iterator> class reverse_iterator;
}

template <class Iterator>
class ft::reverse_iterator
{

public:
    typedef Iterator iterator_type;
    typedef typename ft::iterator_traits<Iterator>::difference_type   difference_type;
    typedef typename ft::iterator_traits<Iterator>::value_type        value_type;
    typedef typename ft::iterator_traits<Iterator>::pointer           pointer;
    typedef typename ft::iterator_traits<Iterator>::reference         reference;
    typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;
private:
	iterator_type ptr;

public:

    reverse_iterator() : ptr() //default	
	{

	}

    explicit reverse_iterator (iterator_type it) :ptr(it) //initialization
    {

    }

    template <class Iter>
    reverse_iterator (const reverse_iterator<Iter>& rev_it) //copy
    {
       this->ptr = rev_it.base();
    }


    iterator_type base() const
	{
	    return (ptr);
	}

    reference operator*() const
    {
        iterator_type tmp = ptr;
        return (*(--tmp));   
    }

    reverse_iterator operator+ (const difference_type n) const
    {
        return reverse_iterator(ptr - n);
    }

    reverse_iterator operator++(int) 
    {
      reverse_iterator temp = *this;
      ++(*this);
      return temp;
    }

    reverse_iterator& operator++()
	{
		ptr--;
        return (*this);
	}

    reverse_iterator& operator+= (difference_type n)
    {
        ptr -= n;
		return (*this);
    }

    reverse_iterator operator- (difference_type n) const
    {
        return reverse_iterator(ptr + n);
    }

    reverse_iterator operator--(int) 
    {
        reverse_iterator temp = *this;
        --(*this);
        return temp;
    }

    reverse_iterator& operator--()
	{
		ptr++;
        return (*this);
	}

    reverse_iterator& operator-= (difference_type n)
    {
        ptr += n;
	    return (*this);   
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    reference operator[] (difference_type n) const
    {
        return (base()[-n-1]);
    }

    bool operator== (reverse_iterator const & lhs) const
   {
       return (this->ptr != lhs.ptr);
   }
     bool operator > (reverse_iterator const & lhs) 
   {
       return (this->ptr < lhs.ptr);
   }
     bool operator < (reverse_iterator const & lhs) 
   {
       return (this->ptr > lhs.ptr);
   }
     bool operator >= (reverse_iterator const & lhs) 
   {
       return (this->ptr <= lhs.ptr);
   }
    bool operator <= (reverse_iterator const & lhs) 
   {
       return (this->ptr >= lhs.ptr);
   }


   bool operator!= (reverse_iterator const & lhs) 
   {
       return (this->ptr == lhs.ptr);
   }

};

template <class Iterator>
bool operator== (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
   return (lhs.base() == rhs.base()); 
}

template <class Iterator>
bool operator< (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return lhs.base() > rhs.base();
}

template <class Iterator>
bool operator<= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return lhs.base() >= rhs.base();
}

template <class Iterator>
bool operator> (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return lhs.base() < rhs.base();
}

template <class Iterator>
bool operator>= (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return lhs.base() <= rhs.base();
}

template <class Iterator>
ft::reverse_iterator<Iterator> operator+ (typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it)
{
    return ( rev_it - n);
}

template <class Iterator>
typename ft::reverse_iterator<Iterator>::difference_type operator- (const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
{
    return ( lhs - rhs );
}