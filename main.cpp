#include "vector.hpp"

#include "iterator.hpp"


int main()
{   
    int a[5] = {5, 4, 6, 7, 8};
    int b[5];

    int *p = NULL; 
    p = new int;
    p[0] = 456;
    p[1] = 77;
    p[2] = 747;

    

    iterator<int> v(a);
    iterator<int> q(a);

    if (v == q)
        std::cout << "mtsawyin\n";
    else
        std::cout << "mamtsawyin\n";

   
      int k = 5;

    v++;
    std::cout << *v << "\n";
    ++v;
    std::cout << *v << "\n";


    k++;
    std::cout << k << "\n";
    ++k;
    std::cout << k << "\n";



}