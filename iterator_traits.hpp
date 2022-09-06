#pragma once
#include <iostream>
#include <cstddef>

namespace ft
{
    template <class Iterator>
    struct iterator_traits;
    template <class T>
    struct iterator_traits<T *>;
    template <class T>
    struct iterator_traits<const T *>;

}

// generic defenition
template <class Iterator>
struct ft::iterator_traits
{
    typedef typename Iterator::value_type value_type;               // the type of the element the iterator can point to.
    typedef typename Iterator::difference_type difference_type;     // type to express the result of subtracting one iterator from another.
    typedef typename Iterator::pointer pointer;                     // The type of a pointer to an element the iterator can point to.
    typedef typename Iterator::reference reference;                 // The type of a reference to an element the iterator can point to.
    typedef typename Iterator::iterator_category iterator_category; // Identifies the iterator concept modeled by the iterator.
};

// T* specialization
template <class T>
struct ft::iterator_traits<T *>
{
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T *pointer;
    typedef T &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

// const T* specialization
template <class T>
struct ft::iterator_traits<const T *>
{
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef const T *pointer;
    typedef const T &reference;
    typedef std::random_access_iterator_tag iterator_category;
};