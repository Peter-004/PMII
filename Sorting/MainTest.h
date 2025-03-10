//
// Created by opemi on 10/27/2024.
//

#ifndef MAINTEST_H
#define MAINTEST_H

#include <iostream>
#include <vector>
class MainTest {

};
class MyClass {
private:
    std::vector<int> data;
public:
    MyClass(const std::vector<int>& elements) : data(elements) {}
    MyClass operator+(const MyClass& other) const {
        int resultSize = std::max(data.size(), other.data.size());
        std::vector<int> result(resultSize, 0);
        for (int i = 0; i < data.size(); ++i) {
            result[i] += data[i];
        }
        for (int i = 0; i < other.data.size(); ++i) {
            result[i] += other.data[i];
        }
        return MyClass(result);
    }
    friend std::ostream& operator<< (std::ostream& out, const MyClass& obj) ;
};
std::ostream& operator<< (std::ostream& out, const MyClass& obj) {
    for (const auto& element : obj.data) {
        std::cout << element << ":";
    }
    return out;
}
int main() {
    MyClass obj_1({0});
    MyClass obj_2({1, 2});
    MyClass obj_3({2, 4, 6, 8});
    MyClass obj_4({3, 9, 6});
    std::cout << "Result_1: " << obj_1 + obj_2 << std::endl;
    std::cout << "Result_2: " << obj_2 + obj_3 << std::endl;
    std::cout << "Result_3: " << obj_2 + obj_3 + obj_4 << std::endl;
    return 0;
}





#endif //MAINTEST_H
