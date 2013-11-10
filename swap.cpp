/*
 * swap two bytes without temporary memory swap(byte a, byte b):
 * ALG: a^=b; b^=a; a^=b;
 */

// binary integers like 0b000100 is a gcc extension
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::ostream;

template <class Integral>
void swap(Integral& a, Integral& b) {
    a^=b;
    b^=a;
    a^=b;
}

/*
 * using the swap function to swap buffer (raw memory)
 */
void swapBuffer(char* buf1, char* buf2, size_t sz) {
    size_t l = sizeof(long long); // assert that sizeof(char)=1
    while(sz>=l) {
        swap(*reinterpret_cast<long long*>(buf1),*reinterpret_cast<long long*>(buf2));
        buf1+=l;
        buf2+=l;
        sz-=l;
    }

    while(sz>0){
        swap(*buf1++, *buf2++);
        --sz;
    }
}


struct TestClass {
    int _len;
    string _name;

    TestClass(const string& name) : _name(name), _len(name.size()) {
    }
};


ostream& operator<< (ostream& os, const TestClass& obj) {
    os << obj._name;
    return os;
}

int main(){
    unsigned char uChar1=10, uChar2=20;
    cout << int(uChar1) << " : " << int(uChar2) << endl;
    swap(uChar1, uChar2);
    cout << int(uChar1) << " : " << int(uChar2) << endl;

    int i1=-2, i2=2;
    cout << i1 << " : " << i2 << endl;
    swap(i1, i2);
    cout << i1 << " : " << i2 << endl;

    char str1[] = {'H', 'e', 'l', 'l', 'o', 0};
    char str2[] = {'W', 'o', 'r', 'l', 'd', 0};

    cout << str1 << " : " << str2 << endl;
    swapBuffer(str1, str2, 5);
    cout << str1 << " : " << str2 << endl;

    TestClass t1("Rong"), t2("Xiao");

    cout << t1 << " : " << t2 << endl;
    swapBuffer(reinterpret_cast<char*>(&t1), reinterpret_cast<char*>(&t2), sizeof(TestClass)); // swap two objects as raw buffer
    cout << t1 << " : " << t2 << endl;
    return 0;
}
