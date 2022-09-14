#include <memory>
#include <iostream>     // std::cout
#include <functional>   // std::less
#include <algorithm>
#include <map>
#include "pair.hpp"

template <class T>
class node
{
private:
    typedef T   value_type;

public:
    int         height;
    value_type  data;
    node *      left;
    node *      right;
    node *      parent;

public:
    node()
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = value_type();
        height = 1;
    }
    node(const value_type & val) // pair
    {
        left = NULL;
        right = NULL;
        parent = NULL;
        data = val;
        height = 1;
    }
    node(const node & n)
    {
        left = n.left;
        right = n.right;
        parent = n.parent;
        data = n.data;
        height = n.height;
    }
    node & operator=(const node & n)
    {
        left = n.left;
        right = n.right;
        parent = n.parent;
        data = n.data;
        height = n.height;
        return *this;
    }
    ~node()
    {}
};

template <
            class T,
            class Compare                     // map::key_compare>
        >
class avl
{
private:
    typedef T                   value_type;
    typedef node<value_type>    node_type;
    typedef std::allocator<node_type> alloc;
    typedef Compare             key_compare;
    typedef size_t              size_type;

    alloc               allocat;
    key_compare      comp;
public:
    node_type         * top;

public:
    avl()
    {
        top = NULL;
    }

    bool insert (value_type newnode)
    {
        return insert_recur(top, newnode, NULL);
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
            if ( comp(newnode.first, c->data.first) ) // true
            {
                retrn = insert_recur(c->left, newnode, c);
            }

            else if ( comp(c->data.first, newnode.first) )
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

    void printBT(const std::string& prefix, const node_type* node, bool isRight)
    {
        if( node != NULL )
        {
            std::cout << prefix;

            std::cout << (isRight ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->data.first << std::endl;

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
        allocat.destroy(top);
        allocat.deallocate(top, 1);
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
    typedef Compare                                 key_compare;
    typedef Alloc                                   allocator_type;
    typedef value_type&                             reference;
    typedef const value_type&                       const_reference;

    avl<value_type, key_compare> avl_map;
public:
    map()
    {
    }
    ~map()
    {
    }
};


int main()
{
    avl< ft::pair<int, int>, std::less<int> > a;

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
    a.print();

    std::cout << a.top->left->left->left->parent->parent->parent->parent->data.first << std::endl;
    // std::cout << a.top->left->left->parent->parent->data.first << std::endl;

    return 0;
}