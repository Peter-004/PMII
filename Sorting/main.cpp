#include <iostream>
#include <vector>

void insSort(std::vector<int>& arr) {
    for(int i = 1;i<arr.size();i++) {
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>key) {
            std::swap(arr[j],arr[j+1]);
            j--;
        }
    }
}

int partition(std::vector<int>& arr, int p, int r) {
    int x = arr[r]; // the pivot
    int i = p-1;  // highest index into the low side
    for(int j = p;j <= r-1;j++) { // process each element other than the pivot
        if(arr[j] <= x) { // does this element belong on the low side?
            i++; // index of a new slot in the low side
            std::swap(arr[i],arr[j]); // put this element there
        }
    }
    std::swap(arr[i+1],arr[r]); // pivot goes just to the right of the low side
    return i+1; // new index of the pivot
}
void countSort(std::vector<int>& arr, int n, int k) {
    std::vector<int> b = {arr.begin(), arr.begin() + n };
    std::vector<int> c = {arr.begin(), arr.begin() + k };

    for(int i = 0;i<k;i++) {
        c[i] = 0;
    }

    for(int j = 0;j<n;j++) {
        int x = c[arr[j]-1];
        c[arr[j]-1]= x + 1;
    }

    for(int i = 1;i<k;i++) {
        c[i] = c[i] + c[i-1];
    }
    for(int j = n-1;j>=0;j--) {
        b[c[arr[j]-1]-1] = arr[j];
        c[arr[j]-1] = c[arr[j]-1]-1;
    }
    arr = c;
}

void quickSort(std::vector<int>& arr, int p, int r) {
    if(p<r) {
        // Partition the subarray around the pivot, which ends up in A[q].
        int q = partition(arr,p,r);
        quickSort(arr, p, q-1);//recursively sort low side
        quickSort(arr,q+1,r); //recursively sort high side
    }
}
template <typename S>
std::ostream& operator<<(std::ostream& os, const std::vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}
int  main()
{
    std::vector<int> arr1 = {52,63,68,23,96,46,11,78,59};
    std::vector<int> arr3 = {28,53,57,34,38,65,92,81,77};
    std::vector<int> arr4 = {4,15,21,25,21,3,1,99};
    std::vector<int> arr5 = {25,75,35,60,15,9,13,2,45};
    std::vector<int> arr6 = {5,55,14,16,12,10,1,0};
    std::vector<int> arr7 = {12,15,20,75,67,49,46,54,51};
    int y = partition(arr1 ,0,8);
    std::cout << y << " arr1 "<<arr1<< std::endl;
    int a = partition(arr3 ,0,4);
    std::cout << a << " arr3 "<<arr3<< std::endl;
    int b = partition(arr4 ,2,7);
    std::cout << b << " arr4 "<<arr4<< std::endl;
    int c = partition(arr5 ,0,8);
    std::cout << c << " arr5 "<<arr5<< std::endl;
    int d = partition(arr6 ,0,7);
    std::cout << d << " arr6 "  <<arr6<< std::endl;
    int e = partition(arr7 ,3,8);
    std::cout << e << " arr7 "  <<arr7<< std::endl;
    std::vector<int> arr2 = {12, 15, 20, 75, 67, 49, 46, 54, 51};
    int x = partition(arr2,3,8);
    std::vector<int> arr = {3, 2, 5, 4, 1, 6, 2, 1, 1, 2, 5, 3};
    countSort(arr,12,6);
    std::cout << x <<arr2<< std::endl;
    std::cout <<arr3<< std::endl;
    return 0;
}
