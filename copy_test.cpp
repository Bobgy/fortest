#include <iter/util/time_keeper.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>
using namespace std;

class A {
public:
    A(vector <int> a) {
        a_ = unique_ptr <vector <int>>(new vector <int> (std::move(a)));
    }
    void update(vector <int> a) {
        *a_ = std::move(a);
    }
    unique_ptr <vector <int>> a_;
};

class B {
public:
    B(vector <int> a) {
        a_ = unique_ptr <vector <int>>(new vector <int> (a));
    }
    void update(vector <int> a) {
        *a_ = a;
    }
    unique_ptr <vector <int>> a_;
};

class C {
public:
    C(const vector <int>& a) {
        a_ = unique_ptr <vector <int>>(new vector <int> (a));
    }
    void update(const vector <int>& a) {
        *a_ = a;
    }
    unique_ptr <vector <int>> a_;
};

vector <int> get() {
    vector <int> tmp;
    for (int i = 0; i < 2e4; i ++) tmp.push_back(i);
    return tmp;
}

vector <int> glob = get();

vector <int> get_tmp() {
    vector <int> tmp = glob;
    return tmp;
}

template <class T>
void test(int tot) {
    vector <int> v = glob;
    cout << "constructor \t: ";

    iter::TimeKeeper tk;
    for (int i = 0; i < tot; i ++) T t(v);
    cout << "lvalue = " << tk.GetElapsedTime() << "\t";
    tk.Reset();
    for (int i = 0; i < tot; i ++) T t(get_tmp());
    cout << "rvalue = " << tk.GetElapsedTime() << endl;

    T t(v);
    cout << "member \t\t: ";

    tk.Reset();
    for (int i = 0; i < tot; i ++) t.update(v);
    cout << "lvalue = " << tk.GetElapsedTime() << "\t";
    tk.Reset();
    for (int i = 0; i < tot; i ++) t.update(get_tmp());
    cout << "rvalue = " << tk.GetElapsedTime() << endl;
}

int main() {
    cout << "pass value with move" << endl;
    test <A> (1e5);
    cout << "pass value without move" << endl;
    test <B> (1e5);
    cout << "pass reference" << endl;
    test <C> (1e5);
    return 0;
}
/*
void test_constructor() {
    cout << "rvalue" << endl;

    iter::TimeKeeper tk;
    for (int i = 0; i < 1e5; i ++) A a(get_tmp());
    cout << "value " << tk.GetElapsedTime() << endl;

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) B b(get_tmp());
    cout << "ref " << tk.GetElapsedTime() << endl;

    cout << "lvalue" << endl;
    vector <int> v = get();

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) A a(v);
    cout << "value " << tk.GetElapsedTime() << endl;

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) B b(v);
    cout << "ref " << tk.GetElapsedTime() << endl;
}

void test_member() {
    cout << "rvalue" << endl;
    A a(glob);
    B b(glob);

    iter::TimeKeeper tk;
    for (int i = 0; i < 1e5; i ++) a.update(get_tmp());
    cout << "value " << tk.GetElapsedTime() << endl;

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) b.update(get_tmp());
    cout << "ref " << tk.GetElapsedTime() << endl;

    cout << "lvalue" << endl;
    vector <int> v = get();

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) a.update(v);
    cout << "value " << tk.GetElapsedTime() << endl;

    tk.Reset();
    for (int i = 0; i < 1e5; i ++) b.update(v);
    cout << "ref " << tk.GetElapsedTime() << endl;
}

int main() {
    cout << "test constructor" << endl;
    test_constructor();
    cout << endl;
    cout << "test member" << endl;
    test_member();
    return 0;
}
*/
