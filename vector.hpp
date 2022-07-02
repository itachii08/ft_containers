#include <memory>
#include <vector>
#include "iterator.hpp"
namespace ft
{
   template < class T, class Alloc = std::allocator<T> > 
   class vector
   {
        //Member Types
        public:
            typedef T                                        value_type;
            typedef Alloc                                    allocator_type;
            typedef typename allocator_type::reference       reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef iterator<value_type>                     iterator;
           // typedef iterator<const value_type>               const_iterator;
            typedef typename allocator_type::size_type       size_type;
            typedef typename allocator_type::difference_type difference_type;
            typedef typename allocator_type::pointer         pointer;
            typedef typename allocator_type::const_pointer   const_pointer;
            typedef std::reverse_iterator<iterator>           reverse_iterator;
           // typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;
        
        public:
            
   }; 
}
