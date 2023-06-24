#include <iostream>
using namespace std;

int main()
{
    int a[5]{0,102,3,4,5};
    int (&b)[5] = a;

    int* c[5];
    c[0] = a;

    int (*d)[5] = &a;

    return 0;
}