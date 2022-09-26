#pragma once
   
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
          if (c)
          {
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
          }
              return retrn;
      }   
      void     printBT(const std::string &prefix, const node_type *node, bool isRight)
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
};