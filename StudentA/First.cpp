#include <iostream>

int main() {
    throw "some exception";
    std::cout << "some text"<< std::endl;
}
