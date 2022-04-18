#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> vec = {1, 2, 3, 4};
    vector<int>::iterator it1 = vec.begin();
    cout << *(it1+2) << endl;
} 