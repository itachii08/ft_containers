#include <memory>
#include <iostream>   // std::cout
#include <functional> // std::less
#include <algorithm>
#include <map>
#include "pair.hpp"
#include "vector.hpp"
#include "iterator_map.hpp"
#include "reverse_iterator.hpp"

namespace ft
{

    template <class T>
    class node
    {
    private:
        typedef T value_type;

    public:
        int height;
        value_type *data;
        node *left;
        node *right;
        node *parent;
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
        node(const value_type &val) // pair
        {
            left = NULL;
            right = NULL;
            parent = NULL;
            data = alloc.allocate(1);
            alloc.construct(data, val);
            height = 1;
        }
        node(const node &n)
        {
            left = n.left;
            right = n.right;
            parent = n.parent;
            data = alloc.allocate(1);
            alloc.construct(data, *n.data);
            height = n.height;
        }
        node &operator=(const node &n)
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
        class Compare // map::key_compare>
        >
    class avl
    {
    private:
        typedef ft::pair<const K, T> value_type;
        typedef K key_type;
        typedef node<value_type> node_type;
        typedef std::allocator<node_type> alloc;
        typedef std::allocator<value_type> alloc_pair;
        typedef Compare key_compare;
        typedef size_t size_type;

        alloc allocat;
        alloc_pair allocat_pair;
        key_compare comp;

    public:
        node_type *top;
        node_type *last;

    public:
        avl()
        {
            top = NULL;
            last = allocat.allocate(1);

            allocat = alloc();
            allocat_pair = alloc_pair();
        }
        avl(const avl & a)
        {
            top = NULL;
            last = allocat.allocate(1);

            tree_copy(a.top);

            allocat = alloc();
            allocat_pair = alloc_pair();
        }
        avl& operator=(const avl & a)
        {
            if (top)
            {
                allocat.destroy(top);
                allocat.deallocate(top, 1);
            }
            allocat.deallocate(last, 1);

            last = allocat.allocate(1);
            // allocat.construct(last, *a.last);

            tree_copy(a.top);

            allocat = a.allocat;
            allocat_pair = a.allocat_pair;
        }


        void tree_copy(node_type *n)
        {
            if (n != NULL)
            {
                insert(*n->data);
                tree_copy(n->left);
                tree_copy(n->right);
            }
        }

        int erase(const key_type &k)
        {
            return erase_recur(top, k);
        }

        int erase_recur(node_type *&c, const key_type &k)
        {
            int ret = 0;

            if (c)
            {
                if (comp(k, c->data->first)) // true
                {
                    ret = erase_recur(c->left, k);
                }

                else if (comp(c->data->first, k))
                {
                    ret = erase_recur(c->right, k);
                }

                else
                {

                    if (c->left == NULL && c->right == NULL)
                    {
                        allocat.destroy(c);
                        allocat.deallocate(c, 1);
                        c = NULL;

                        return 1;
                    }

                    else if (c->left == NULL)
                    {
                        node_type *tmp = c->right;
                        node_type *parent_tmp = c->parent;

                        allocat.destroy(c);
                        allocat.deallocate(c, 1);
                        c = NULL;

                        c = tmp;
                        tmp->parent = parent_tmp;
                        ret = 1;
                    }

                    else if (c->right == NULL)
                    {
                        node_type *tmp = c->left;
                        node_type *parent_tmp = c->parent;

                        allocat.destroy(c);
                        allocat.deallocate(c, 1);
                        c = NULL;

                        c = tmp;
                        tmp->parent = parent_tmp;
                        ret = 1;
                    }
                    else
                    {
                        node_type *tmp = min_left(c->right);

                        allocat_pair.destroy(c->data);
                        allocat_pair.deallocate(c->data, 1);

                        c->data = allocat_pair.allocate(1);
                        allocat_pair.construct(c->data, ft::make_pair(tmp->data->first, tmp->data->second));

                        ret = erase_recur(c->right, tmp->data->first);
                    }
                }

                c->height = 1 + std::max(nodeHeight(c->left), nodeHeight(c->right));
                int balance = nodeBalance(c);

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
            return ret;
        }

        node_type *min_left(node_type *t)
        {
            node_type *tmp = t;
            while (tmp && tmp->left)
            {
                tmp = tmp->left;
            }
            return tmp;
        }
        node_type *max_right(node_type *t)
        {
            node_type *tmp = t;
            while (tmp && tmp->right)
            {
                tmp = tmp->right;
            }
            return tmp;
        }

        bool insert(value_type newnode)
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

        bool insert_recur(node_type *&c, value_type newnode, node_type *par)
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
                if (comp(newnode.first, c->data->first)) // true
                {
                    retrn = insert_recur(c->left, newnode, c);
                }

                else if (comp(c->data->first, newnode.first))
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

        void iterateParent(node_type *&nod, node_type *par)
        {
            if (nod)
            {
                nod->parent = par;

                iterateParent(nod->right, nod);
                iterateParent(nod->left, nod);
            }
        }

        node_type *rotationLeft(node_type *y)
        {
            node_type *x = y->right;
            node_type *T2 = x->left;

            x->left = y;
            y->right = T2;

            y->height = std::max(nodeHeight(y->left),
                                 nodeHeight(y->right)) +
                        1;
            x->height = std::max(nodeHeight(x->left),
                                 nodeHeight(x->right)) +
                        1;

            iterateParent(x, y->parent);

            return x;
        }

        node_type *rotationRight(node_type *y)
        {
            node_type *x = y->left;
            node_type *T2 = x->right;

            x->right = y;
            y->left = T2;

            y->height = std::max(nodeHeight(y->left),
                                 nodeHeight(y->right)) +
                        1;
            x->height = std::max(nodeHeight(x->left),
                                 nodeHeight(x->right)) +
                        1;

            iterateParent(x, y->parent);

            return x;
        }

        int nodeBalance(node_type *nod)
        {
            if (nod)
            {
                // std::cout << node
                return nodeHeight(nod->left) - nodeHeight(nod->right);
            }
            else
                return 0;
        }

        int nodeHeight(node_type *nod)
        {
            if (nod)
            {
                return nod->height;
            }
            else
                return 0;
        }

        node_type *find(node_type *c, const key_type &k)
        {
            node_type *retrn = NULL;

            if (comp(k, c->data->first)) // true
            {
                retrn = find(c->left, k);
            }

            else if (comp(c->data->first, k))
            {
                retrn = find(c->right, k);
            }

            else
            {
                retrn = c;
            }

            return retrn;
        }

        void printBT(const std::string &prefix, const node_type *node, bool isRight)
        {
            if (node != NULL)
            {
                std::cout << prefix;

                std::cout << (isRight ? "├──" : "└──");

                // print the value of the node
                std::cout << node->data->first << std::endl;

                // enter the next tree level - left and right branch
                printBT(prefix + (isRight ? "│   " : "    "), node->right, true);
                printBT(prefix + (isRight ? "│   " : "    "), node->left, false);
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

            if (last)
            {
                allocat.deallocate(last, 1);
                last = NULL;
            }
        }
    };

    template <class Key,                                           // map::key_type
              class T,                                             // map::mapped_type
              class Compare = std::less<Key>,                      // map::key_compare
              class Alloc = std::allocator<ft::pair<const Key, T> > // map::allocator_type
              >
    class map
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const key_type, mapped_type> value_type;
        typedef const value_type const_value_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef	typename	Alloc::template rebind< avl<Key, T, Compare> >::other alloc_tree;
        typedef value_type &reference;
        typedef const value_type &const_reference;
        typedef node<value_type> node_type;
        typedef ft::map_iterator<value_type, node_type> iterator;
        typedef ft::map_iterator<const_value_type, node_type> const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef avl<Key, T, Compare> Avl;
        typedef size_t size_type;
        
        class value_compare
        { // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
            friend class map;

        protected:
            Compare comp;
            value_compare(Compare c) : comp(c) {} // constructed with map's comparison object
        public:
            typedef bool result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;
            bool operator()(const value_type &x, const value_type &y) const
            {
                return comp(x.first, y.first);
            }
        };

        Avl *avl_map;
        alloc_tree tree_alloc;
        allocator_type alloc;
        key_compare comp;
        size_type siz;

    public:
        //=====> Member functions <===========//
        explicit map(const key_compare &compe = key_compare(),
                     const allocator_type &allocc = allocator_type())
                     : tree_alloc(), alloc(allocc), comp(compe), siz(0)
        {
            avl_map = tree_alloc.allocate(1);
			tree_alloc.construct(avl_map, avl<Key, T, Compare>());
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &compe = key_compare(),
            const allocator_type &allocc = allocator_type())
            : tree_alloc(), alloc(allocc), comp(compe), siz(0)
        {
            avl_map = tree_alloc.allocate(1);
			tree_alloc.construct(avl_map, avl<Key, T, Compare>());
			while (first != last)
			{
				insert(*first);
				first++;
			}
        }

        map(const map &x) : tree_alloc(), alloc(x.alloc), comp(x.comp), siz(0)
        {
            avl_map = tree_alloc.allocate(1);
			tree_alloc.construct(avl_map, avl_map());
            comp = x.comp;
			alloc = x.alloc;
			comp = x.comp;
			for (const_iterator ite = x.begin(); ite != x.end(); ite++)
			{
				insert(*ite);
			}
        }

        map& operator= (const map& x)
		{
			clear();
			comp = x.comp;
			alloc = x.alloc;
			comp = x.comp;
			for (const_iterator ite = x.begin(); ite != x.end(); ite++)
				insert(*ite);
			return *this;
		}
      
        ~map()
        {
            clear();
			tree_alloc.destroy(avl_map);
			tree_alloc.deallocate(avl_map, 1);
        }
        //=====> Modifiers <===========//
        // INSERT
        pair<iterator, bool> insert(const value_type &val)
        {
            bool ret = avl_map->insert(val);
            if (ret)
                siz++;

            return ft::pair<iterator, bool>(iterator(avl_map->top, avl_map->find(avl_map->top, val.first), avl_map->last), ret);
            // return ft::make_pair( iterator(avl_map->find(avl_map->top, val.first), avl_map->last), ret ) ;
        }
        iterator insert(iterator position, const value_type &val)
        {
            (void)position;
            if (avl_map->insert(val))
                siz++;

            return iterator(avl_map->top, avl_map->find(avl_map->top, val.first), avl_map->last);
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                insert(*first);
                // avl_map->insert(*first);
                first++;
                siz++;
            }
        }

        // ERASE
        void erase(iterator position)
        {
            int a = avl_map->erase(position->first);
            if (a == 1)
                siz--;
        }
        size_type erase(const key_type &k)
        {
            int a = avl_map->erase(k);
            if (a == 1)
                siz--;
            return a;
        }
        void erase(iterator first, iterator last)
        {
            ft::vector<key_type> v;
            while (first != last)
            {
                v.push_back(first->first);
                first++;
            }
            typename ft::vector<key_type>::iterator ite = v.begin();
            while (ite != v.end())
            {
                erase(*ite);
                ite++;
            }
        }
        void swap(map &x) 
        {
            Avl *tmp = avl_map;
			size_type size_tmp = siz;
			avl_map = x.avl_map;
			siz  = x.siz;
			x.avl_map =  tmp;
			x.siz = size_tmp;    
        }
        void clear() 
        {
            erase(begin(), end());
        }

        //=====> Iterators: <===========//
        iterator begin()
        {
            return iterator(avl_map->top, avl_map->min_left(avl_map->top), avl_map->last);
        }

        const_iterator begin() const
        {
            return const_iterator(avl_map->top, avl_map->min_left(avl_map->top), avl_map->last);
        }

        iterator end()
        {
            return iterator(avl_map->top, avl_map->last, avl_map->last);
        }
        const_iterator end() const
        {
            return const_iterator(avl_map->top, avl_map->last, avl_map->last);
        }

        reverse_iterator rbegin()
        {
            return (reverse_iterator(end()));
        }
        const_reverse_iterator rbegin() const
        {
            return (const_reverse_iterator(end()));
        }
        reverse_iterator rend()
        {
            return (reverse_iterator(begin()));
        }
        const_reverse_iterator rend() const
        {
            return (const_reverse_iterator(begin()));
        }
        //============> Capacity: <======================//
        bool empty() const
        {
            return (siz == 0);
        }
        size_type size() const
        {
            return siz;
        }
        size_type max_size() const
        {
            return alloc.max_size(); 
        }
        //============> Element access:<======================//
        mapped_type &operator[](const key_type &k)
        {
            ft::pair<key_type, mapped_type> n = ft::make_pair(k, mapped_type());
            avl_map->insert(n);
            // std::cout << "first " << p.first << " second " << p.second << std::endl;
            node_type *node = avl_map->find(avl_map->top, n.first);
            return (node->data->second);
        }
        //============> Operations: <======================//
        iterator find(const key_type &k)
        {
            node_type *tmp = avl_map->find(avl_map->top, k);
            if (tmp == NULL)
            {
                return end();
            }
            else
            {
                return iterator(avl_map->top, tmp, avl_map->last);
            }
        }
        const_iterator find(const key_type &k) const
        {
            node_type *tmp = avl_map->find(avl_map->top, k);
            if (tmp == NULL)
            {
                return end();
            }

            else
            {
                return const_iterator(avl_map->top, tmp, avl_map->last);
            }
        }
        size_type count(const key_type &k) const 
        {
            node_type *tmp = avl_map->find(avl_map->top, k);
            if (!tmp)
                return (0);
            return (1);
        }
        iterator lower_bound(const key_type &k) 
        {
            iterator it = find(k);
				if (it != end())
					return (it);
				iterator tmp(avl_map->_top, avl_map->_last, avl_map->min_left(avl_map->top));
				while ( tmp != end() )
				{
					if (comp(k, (*tmp).first) &&
						comp(k, avl_map->max_right(avl_map->top)->data->first))
					{
						return (iterator(tmp));
					}
					tmp++;
				}
				return (end());
        }
        const_iterator lower_bound(const key_type &k) const 
        {
            const_iterator it = find(k);
				if (it != end())
					return (it);
				const_iterator tmp(avl_map->_top, avl_map->_last, avl_map->min_left(avl_map->top));
				while ( tmp != end() )
				{
					if (comp(k, (*tmp).first) &&
						comp(k, avl_map->max_right(avl_map->top)->data->first))
					{
						return (iterator(tmp));
					}
					tmp++;
				}
				return (end());
        }
        iterator upper_bound(const key_type &k) 
        {
            iterator it = find(k);
				if (it != end())
					return (++it);

				iterator tmp = begin();
				while ( tmp != end() )
				{
					if (comp(k, (*tmp).first) &&
						comp(k, avl_map->max_right(avl_map->top)->data->first))
						return (iterator(tmp));
					tmp++;
				}
				return (end());
        }
        const_iterator upper_bound(const key_type &k) const
        {
            const_iterator it = find(k);
				if (it != end())
					return (++it);

				const_iterator tmp = begin();
				while ( tmp != end() )
				{
					if (comp(k, (*tmp).first) &&
						comp(k, avl_map->max_right(avl_map->top)->data->first))
						return (iterator(tmp));
					tmp++;
				}
				return (end());
        }
        ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const 
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        ft::pair<iterator, iterator> equal_range(const key_type &k) 
        {
            return (ft::make_pair(lower_bound(k), upper_bound(k)));
        }
        //============> Observers: <======================//
        key_compare key_comp() const 
        {
            return this->comp;
        }
        value_compare value_comp() const 
        {
            return value_compare(comp);   
        }
        //============> Allocator: <======================//
        allocator_type get_allocator() const
        {
             return (this->alloc);
        }

        void print()
        {
            avl_map->print();
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

    // std::map<int, int>  ;
    // std::cout << m.end()->first << std::endl;
    // std::cout << mitb->first << std::endl;

    // while (mitb != mite)
    // {
    //     mite--;
    //     std::cout << mite->first << std::endl;
    // }

    std::cout << std::endl;
    a.erase(5);
    std::cout << std::endl;

    a.print();

    // mite = a.end();
    // while (mitb != mite)
    // {
    //     mite--;
    //     std::cout << mite->first << std::endl;
    // }

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