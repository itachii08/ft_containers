#include <memory>
#include <iostream>   // std::cout
#include <functional> // std::less
#include <algorithm>
#include <map>
#include "pair.hpp"
#include "vector.hpp"
#include "iterator_map.hpp"
#include "reverse_iterator.hpp"
#include "Avl.hpp"

namespace ft
{

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
			tree_alloc.construct(avl_map, avl<Key, T, Compare>());
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
                // siz++;
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
            if (empty())
                return end();
            return iterator(avl_map->top, avl_map->min_left(avl_map->top), avl_map->last);
        }

        const_iterator begin() const
        {
            if (empty())
                return end();
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
            if (avl_map->insert(n) == true)
                siz++;
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
        iterator lower_bound (const key_type& k)
        {
             iterator it = begin();

            while  (it != end())
            {
                if (comp(it->first, k) == false)
                    break;
                it++;
            }
            return it;  
        }
        const_iterator lower_bound(const key_type &k) const 
        {
             const_iterator it = begin();

            while  (it != end())
            {
                if (comp(it->first, k) == false)
                    break;
                it++;
            }
            return it;  
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

    template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator == (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator != (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator > (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator < (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator >= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
			return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool	operator <= (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (!(lhs > rhs));
	}

};