#include <memory>
#include <iostream>     // std::cout
#include <functional>   // std::less
#include <algorithm>
#include <map>
#include "pair.hpp"
#include "iterator_map.hpp"

namespace ft {

template <class T>
class node
{
private:
    typedef T   value_type;

public:
    int         height;
    value_type *  data;
    node *      left;
    node *      right;
    node *      parent;
    typedef std::allocator<value_type> allocat;
    allocat alloc;

public:
    node()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = alloc.allocate(1);
        height = 1;
    }
    node(const value_type & val) // pair
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = alloc.allocate(1);
        alloc.construct(data, val);
        height = 1;
    }
    node(const node & n)
    {
        left = n.left;
        right = n.right;
        parent = n.parent;
        data = alloc.allocate(1);
        alloc.construct(data, *n.data);
        height = n.height;
    }
    node & operator=(const node & n)
    {
        left = n.left;
        right = n.right;
        parent = n.parent;
        if (data)
        {
            alloc.destroy(data);
            alloc.deallocate(data, 1);
        }
        data = alloc.allocate(1);
        alloc.construct(data, *n.data);
        height = n.height;
        return *this;
    }
    ~node()
    {
        if (data)
        {
            alloc.destroy(data);
            alloc.deallocate(data, 1);
            data = NULL;
        }
    }
};

template <
            class K,
            class T,
            class Compare                     // map::key_compare>
        >
class avl
{
private:
    typedef ft::pair<const K, T>      value_type;
    typedef K                   key_type;
    typedef node<value_type>    node_type;
    typedef std::allocator<node_type> alloc;
    typedef Compare             key_compare;
    typedef size_t              size_type;

    alloc               allocat;
    key_compare      comp;
public:
    node_type         * top;
    node_type         * last;

public:
    avl()
    {
        top = NULL;
        last = allocat.allocate(1);
    }

    node_type * min_left()
    {
        node_type * tmp = top;
        while (tmp && tmp->left)
        {
            tmp = tmp->left;
        }
        return tmp;
    }

    bool insert (value_type newnode)
    {
        bool ret = insert_recur(top, newnode, NULL);

        node_type *tmp = top;
        while (tmp && tmp->right)
        {
            tmp = tmp->right;
        }
        last->parent = tmp;

        return ret;
    }

    bool insert_recur (node_type *& c, value_type newnode, node_type * par)
    {
        bool retrn;

        if (!c)
        {
            c = allocat.allocate(1);
            allocat.construct(c, node_type(newnode));
            c->parent = par;
            return true;
        }
        else
        {
            if ( comp(newnode.first, c->data->first) ) // true
            {
                retrn = insert_recur(c->left, newnode, c);
            }

            else if ( comp(c->data->first, newnode.first) )
            {
                retrn = insert_recur(c->right, newnode, c);
            }

            else
            {
                retrn = false;
            }
        }

        if (retrn)
        {
            c->height = 1 + std::max(nodeHeight(c->left), nodeHeight(c->right));

            int balance = nodeBalance(c);

            // std::cout << "BALANCE " << balance << std::endl;

            if (balance > 1)
            {
                int leftBal = nodeBalance(c->left);
                if (leftBal > 0)
                {
                    c = rotationRight(c);
                }

                else if (leftBal < 0)
                {
                    c->left = rotationLeft(c->left);
                    c = rotationRight(c);
                }
            }

            else if (balance < -1)
            {
                int rightBal = nodeBalance(c->right);
                if (rightBal < 0)
                {
                    c = rotationLeft(c);
                }

                else if (rightBal > 0)
                {
                    c->right = rotationRight(c->right);
                    c = rotationLeft(c);
                }
            }
        }

        return retrn;
    }

    void iterateParent(node_type *& nod, node_type * par)
    {
        if (nod)
        {
            nod->parent = par;

            iterateParent(nod->right, nod);
            iterateParent(nod->left, nod);
        }
    }

    node_type * rotationLeft(node_type * y)
    {
        node_type * x = y->right;
        node_type * T2 = x->left;

        x->left = y;
        y->right = T2;

        y->height = std::max(nodeHeight(y->left),
                        nodeHeight(y->right)) + 1;
        x->height = std::max(nodeHeight(x->left),
                        nodeHeight(x->right)) + 1;

        iterateParent(x, y->parent);

        return x;
    }

    node_type * rotationRight(node_type * y)
    {
        node_type * x = y->left;
        node_type * T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(nodeHeight(y->left),
                        nodeHeight(y->right)) + 1;
        x->height = std::max(nodeHeight(x->left),
                        nodeHeight(x->right)) + 1;

        iterateParent(x, y->parent);

        return x;
    }

    int nodeBalance(node_type * nod)
    {
        if (nod)
        {
            // std::cout << node
            return nodeHeight(nod->left) - nodeHeight(nod->right);
        }
        else
            return 0;
    }

    int nodeHeight(node_type * nod)
    {
        if (nod)
        {
            return nod->height;
        }
        else
            return 0;
    }

    node_type* find (node_type * c, const key_type& k)
    {
        node_type * retrn = NULL;

        if ( comp(k, c->data->first) ) // true
        {
            retrn = find(c->left, k);
        }

        else if ( comp(c->data->first, k) )
        {
            retrn = find(c->right, k);
        }

        else
        {
            retrn = c;
        }

        return retrn;
    }

    void printBT(const std::string& prefix, const node_type* node, bool isRight)
    {
        if( node != NULL )
        {
            std::cout << prefix;

            std::cout << (isRight ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->data->first << std::endl;

            // enter the next tree level - left and right branch
            printBT( prefix + (isRight ? "│   " : "    "), node->right, true);
            printBT( prefix + (isRight ? "│   " : "    "), node->left, false);
        }
    }

    void print()
    {
        printBT("", top, false);
    }

    ~avl()
    {
        if (top)
        {
            allocat.destroy(top);
            allocat.deallocate(top, 1);
        }

        allocat.deallocate(last, 1);
    }
};



template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator<ft::pair<const Key,T> >    // map::allocator_type
           > class map
{
public:
    typedef Key                                     key_type;
    typedef T                                       mapped_type;
    typedef ft::pair<const key_type, mapped_type>   value_type;
    typedef const value_type                        const_value_type;
    typedef Compare                                 key_compare;
    typedef Alloc                                   allocator_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;
    typedef node<value_type>                        node_type;
    typedef ft::map_iterator<value_type, node_type> iterator;
    typedef ft::map_iterator<const_value_type, node_type> const_iterator;

    avl<Key, T, Compare> avl_map;
public:
    map()
    {
    }

    // single element (1)
    pair<iterator,bool> insert (const value_type& val)
    {
        bool ret = avl_map.insert(val);

        return ft::pair<iterator, bool> ( iterator(avl_map.top, avl_map.find(avl_map.top, val.first), avl_map.last), ret );
        // return ft::make_pair( iterator(avl_map.find(avl_map.top, val.first), avl_map.last), ret ) ;
    }
    // with hint (2)
    iterator insert (iterator position, const value_type& val)
    {
        avl_map.insert(val);
        return iterator (avl_map.top, avl_map.find(avl_map.top, val.first), avl_map.last) ;
    }
    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            insert(*first);
            // avl_map.insert(*first);
            first++;
        }
    }

          iterator begin()
          {
            return iterator(avl_map.top, avl_map.min_left(), avl_map.last);
          }
    const_iterator begin() const
          {
            return const_iterator(avl_map.top, avl_map.min_left(), avl_map.last);
          }

          iterator end()
          {
            return iterator(avl_map.top, avl_map.last, avl_map.last);
          }
    const_iterator end() const
          {
            return const_iterator(avl_map.top, avl_map.last, avl_map.last);
          }

    ~map()
    {
    }

    iterator find (const key_type& k)
    {
        node_type * tmp = avl_map.find(avl_map.top, k);
        if (tmp == NULL)
        {
            return end();
        }

        else
        {
            return iterator(avl_map.top, tmp, avl_map.last);
        }
    }

    const_iterator find (const key_type& k) const
    {
        node_type * tmp = avl_map.find(avl_map.top, k);
        if (tmp == NULL)
        {
            return end();
        }

        else
        {
            return const_iterator(avl_map.top, tmp, avl_map.last);
        }
    }

    void print()
    {
        avl_map.print();
    }
};

};

int main()
{
    // avl< ft::pair<int, int>, std::less<int> > a;

    ft::map<int, int> a;

    a.insert(ft::pair<int, int>(7, 7));
    a.insert(ft::pair<int, int>(2, 2));
    a.insert(ft::pair<int, int>(0, 0));
    a.insert(ft::pair<int, int>(-1, -1));
    a.insert(ft::pair<int, int>(1, 1));
    a.insert(ft::pair<int, int>(6, 6));
    a.insert(ft::pair<int, int>(8, 8));
    a.insert(ft::pair<int, int>(10, 10));
    a.insert(ft::pair<int, int>(4, 4));
    a.insert(ft::pair<int, int>(5, 5));
    a.insert(ft::pair<int, int>(3, 3));
    a.insert(ft::pair<int, int>(9, 9));
    ft::pair<ft::map<int, int>::iterator, bool> pr = a.insert(ft::pair<int, int>(9, 9));
    a.print();

    ft::map<int, int>::const_iterator mitb = a.begin();
    ft::map<int, int>::const_iterator mite = a.end();

    // std::map<int, int> m;
    // std::cout << m.end()->first << std::endl;
        std::cout << mitb->first << std::endl;

    while (mitb != mite)
    {
        mite--;
        std::cout << mite->first << std::endl;
    }

    // while (mitb != mite)
    // {
        
    //     std::cout << mitb->first << std::endl;
    //     mitb++;
    // }
    // std::cout << mitb->first << std::endl;

    // std::cout << pr.second << std::endl;
    // std::cout << mit->first << std::endl;

    // std::cout<< a.top->left->left->left->parent->parent->parent->data->first << std::endl;
    // std::cout << a.top->left->left->parent->parent->data->first << std::endl;

    return 0;
}