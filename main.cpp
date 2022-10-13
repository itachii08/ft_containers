#include "vector.hpp"
#include "iterator.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "iterator_map.hpp"
#include "stack.hpp"

int main_map()
{
  std::cout << "********************* MAP ********************\n";
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
    std::cout << "********************* VECTOR ********************\n";
    return 0;
}
int main_swap()
{
  ft::vector<int> v1;

  for (int i = 1; i < 6; i++)
    v1.push_back(i);

  ft::vector<int> v2;

  for (int i = 6; i < 10; i++)
    v2.push_back(i);

  ft::vector<int>::iterator it = v1.begin();

  std::cout << "it before swap => " << *it << std::endl;

  v1.swap(v2);
  it = v1.begin();
  std::cout << "it after swap => " << *it << std::endl;
  return 0;
}

int main1 ()
{
  
  std::cout << "\n=========constructing vectors===================\n";
    // constructors used in the same order as described above:
    ft::vector<int> first;                                // empty vector of ints
    ft::vector<int> second (4,100);                       // four ints with value 100
    ft::vector<int> third (second.begin(),second.end());  // iterating through second
    ft::vector<int> fourth (third);                       // a copy of third   
    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );    
    std::cout << "The contents of fifth are:";
    for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
      std::cout << ' ' << *it;
    std::cout << "\n===========vector assignment==============\n";
  
    return 0;
}

int main2 ()
{
  std::vector<int> foo (3,0);
  std::vector<int> bar (5,0);

  bar = foo;
  foo = std::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  std::cout << "\n===============vector::begin/end=======================\n";
  return 0;
}

int main3 ()
{
  ft::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "\n===============vector::rbegin/rend=======================\n";
  return 0;
}

int main4()
{
  ft::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  ft::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  std::cout << "\n===============vector::size=======================\n";

  return 0;
}

int main5()
{
  ft::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.end(), myints.begin() + 10, myints.begin() + 100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';
  std::cout << "\n===============comparing size, capacity and max_size=======================\n";
  return 0;
}

int main6()
{
  ft::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";
  std::cout << "\n===============resizing vector=======================\n";
  return 0;
}

int main7 ()
{
  ft::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (unsigned long i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  std::cout << "\n===============vector emty=======================\n";

  return 0;
}

int main8 ()
{
  ft::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';
  std::cout << "\n=============== vector::reserve=======================\n";

  return 0;
}

int main9 ()
{
  std::vector<int>::size_type sz;

  std::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  std::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) 
    {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  std::cout << "\n=============== vector::operator[]=======================\n";
  return 0;
}

int main10 ()
{
  ft::vector<int> myvector (10);   // 10 zero-initialized elements

  ft::vector<int>::size_type sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
    std::cout << '\n';
    std::cout << "\n===============vector::at=======================\n";
  return 0;
}

int main11 ()
{
  ft::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';
  std::cout << "\n===============vector::front=======================\n";

  return 0;
}

int main12 ()
{
  ft::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';
  std::cout << "\n===============vector::back=======================\n";

  return 0;
}

int main13 ()
{
  ft::vector<int> myvector;

  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  return 0;
}

int main_stack1 ()
{
  std::cout << "===========> Constract============== \n";
  ft::vector<int> mydeque (3,100);          // deque with 3 elements
  ft::vector<int> myvector (2,200);        // vector with 2 elements

  ft::stack<int> first;                    // empty stack
  ft::stack<int> second (mydeque);         // stack initialized to copy of deque

  ft::stack<int,ft::vector<int> > third;  // empty stack using vector
  ft::stack<int,ft::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  return 0;
}

int main_stack2 ()
{
  std::cout << "===========> emty and top pop ================== \n";
  ft::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

  return 0;
}



int main()
{
  main_swap();
  main_map();
  main1();
  main2();
  main3();
  main4();
  main5();
  main6();
  main7();
  main8();
  main9();
  main10();
  main11();
  main12();
  main13();
  main_stack1();
  main_stack2();

  
 
  //system("leaks a.out");
  return 0;
}