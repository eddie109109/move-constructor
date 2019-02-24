#include <iostream>
#include <vector>
using namespace std;


class Move {
private:
    int *data;
    
public:
    void set_data_value(int d) {
        *data = d;
    }
    int get_data_value() {
        return *data;
    }
    Move(int d);
    
    Move(const Move &source);
    Move(Move &&source) noexcept; // move constructor
    ~Move();
};

Move::Move(int d) {
    data = new int;
    *data = d;
    cout << "constructor for "<< d << endl;
}

Move::Move(const Move &source)
    :Move{*source.data}{
    cout << "copy constructor- deep copy for:" << *data << endl;
}

Move::Move(Move &&source) noexcept
    :data{source.data} { // we simply copy source.data to data, not doing a deep copy here
    source.data = nullptr;   // (steals the data and then) we null out the source pointer
    cout << "move constructor being called" << endl;    
}

Move::~Move() {
    if (data != nullptr) {
        cout << "Destructor freeing data for: " << *data << endl;
    } else {
        cout << "Destructor freeing data for nullptr" << endl;
    }
    delete data;
    
}


int main() {
    vector<Move> vec;
    vec.push_back(Move{10});

    return 0;
}

// the result:

// constructor called for 10
// move constructor being called
// destructor freeing data for nullptr
// destructor freeing data for 10 (unexpected result)
