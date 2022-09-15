#pragma once
#include "iterator_traits.hpp"

namespace ft {

template <typename T, typename N>
class map_iterator
{
public:
    typedef T iterator_type;
    typedef typename ft::iterator_traits<T *>::difference_type difference_type;
    typedef typename ft::iterator_traits<T *>::value_type value_type;
    typedef typename ft::iterator_traits<T *>::pointer pointer;
    typedef typename ft::iterator_traits<T *>::reference reference;
    typedef typename std::bidirectional_iterator_tag iterator_category;
    // typedef map_iterator<const T> const_iterator;
    typedef N                                       node_type;

private:
public:
    node_type * top;
    node_type * p;
    node_type * last;

    map_iterator() : p(NULL)
    {
    }

    map_iterator(node_type * t, node_type * ptr, node_type * l) : top(t), p(ptr), last(l)
    {
    }

    template <class Type, class Node>
    map_iterator(const map_iterator<Type, Node> &src) // copy
    {
        this->p = src.p;
        this->top = src.top;
        this->last = src.last;
    }

    map_iterator &operator=(map_iterator const &src)
    {
        this->p = src.p;
        this->top = src.top;
        this->last = src.last;
        return (*this);
    }

    ~map_iterator()
    {
    }
    bool operator==(map_iterator const &lhs) const
    {
        return (this->p == lhs.p);
    }

    bool operator!=(map_iterator const &lhs) const
    {
        return (this->p != lhs.p);
    }

    reference operator*()
    {
        return *(this->p->data);
    }

    pointer operator->()
    {
        return &(operator*());
    }

    map_iterator operator++()
    {
        if ( p && p->right )
        {
            p = p->right;

            while ( p->left )
            {
                p = p->left;
            }
        }

        else if ( p )
        {
            node_type * tmp = p->parent;
            while ( tmp && tmp->left != p )
            {
                p = p->parent;
                tmp = tmp->parent;
            }

            p = tmp;
        }

        if (p == NULL)
        {
            // last
            p = last;
        }

        return *this;
    }

    map_iterator operator++(int)
    {
        map_iterator tmp(*this);
        ++(*this);
        return tmp;
    }
    

    map_iterator operator--()
    {
        if (p == last)
        {
            // last
            p = last->parent;
        }

        else if ( p && p->left )
        {
            p = p->left;

            while ( p->right )
            {
                p = p->right;
            }
        }

        else if ( p )
        {
            node_type * tmp = p->parent;
            while ( tmp && tmp->right != p )
            {
                p = p->parent;
                tmp = tmp->parent;
            }

            p = tmp;
        }

        return *this;
    }

    map_iterator operator--(int)
    {
        map_iterator tmp(*this);
        --(*this);
        return tmp;
    }
};

};