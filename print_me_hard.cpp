#include <iostream>
using namespace std;

int main()
{
    int a, b = 0;

    cin >> a >> b;

    int equ_is_1 = a * a;
    int equ_is_neg_1 = (2 * a) + 1;

    int is_1 = (1 + b) / 2;
    int is_neg_1 = 1 - is_1;

    cout << (is_1 * equ_is_1) + (is_neg_1 * equ_is_neg_1);

    return 0;
}