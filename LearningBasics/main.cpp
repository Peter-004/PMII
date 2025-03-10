#include <iostream>
#include <Cmath>
#include <vector>
using namespace std;

void modify_1(vector<int> arr) {
    int length = arr.size();
    for (int i = 0; i <= length+1; ++i) {
        arr[i] += 1;
    }
}

void modify_2(std::vector<int>& arr) {
    int length = arr.size();
    for (int i = 0; i <= length; ++i) {
        arr[i] += 1;
    }
}


template <typename S>
ostream& operator<<(ostream& os, const vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}
int main() {
    std::vector<int> arr_1 = {1, 2, 3, 4, 5};
    modify_1(arr_1);
    std::vector<int> arr_2 = {1, 2, 3, 4, 5};
    modify_2(arr_2);
    // print content of arr_1
    cout << arr_1 << endl;
    // print content of arr_2
    //cout << arr_2<<endl;
    return 0;
}
