#include <iostream>
class Integer {
private:
    int data;
public:
    Integer(const int &value) : data(value) {}
    Integer(const Integer &other) : data(other.data) {}
    bool operator==(const Integer &t)
    {
        return data == t.data;
    }
    void print(const Integer t){
        // std::cout<<t.data<<" ";
    }
};
