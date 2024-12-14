#include <iostream>
#include "class-integer.hpp"
#include "class-matrix.hpp"
#include "class-bint.hpp"
#include <vector>
#include <deque>
#include "deck.hpp"
bool need_to_check_throw = 1;
bool good_complexity = 1;//if the complexity is N^2, change to 0
int N = good_complexity ? 50000 : 1000;
static const int N_SPEED = 21000;
class T{
private:
    int x;
public:
    T(int x):x(x){}
    int num()const {return x;}
    void change(int y){
        x = y;
    }
};
bool operator == (const T &a, const T &b){
    return a.num() == b.num();
}
bool operator != (const T &a, const T &b){
    return a.num() != b.num();
}
sjtu::deque<T> q;
std::deque<T> stl;
sjtu::deque<T>::iterator it_q;
std::deque<T>::iterator it_stl;
sjtu::deque<T>::const_iterator _it_q;
std::deque<T>::const_iterator _it_stl;
bool equal(){
    if(q.size() != stl.size()) return 0;
    if(q.empty() != stl.empty()) return 0;
    int cnt = 0;
    for(it_q = q.begin(), it_stl = stl.begin(); it_q != q.end() || it_stl != stl.end(); it_q++, it_stl++){
        if(*it_q != *it_stl) {
            printf("cnt = %d\n",cnt);
            return 0;
        }
        cnt++;
    }
    return 1;
}
class Int{
private:
    int data;

public:
    Int() = default;
    Int(const int &data) : data(data) {}
    Int & operator =(const Int &rhs) = default;
    bool operator <(const Int &rhs) = delete;
    bool operator >(const Int &rhs) = delete;
    bool operator <=(const Int &rhs) = delete;
    bool operator >=(const Int &rhs) = delete;
    bool operator ==(const Int &rhs)const {
        return data == rhs.data;
    }
    bool operator !=(const Int &rhs)const {
        return data != rhs.data;
    }
    
};

class Timer{
private:
    long dfnStart, dfnEnd;

public:
    void init() {
        dfnEnd = dfnStart = clock();
    }
    void stop() {
        dfnEnd = clock();
    }
    double getTime() {
        return 1.0 * (dfnEnd - dfnStart) / CLOCKS_PER_SEC;
    }

};

Timer timer;


bool isEqual(std::deque<Int> &a, sjtu::deque<Int> &b) {
    static std::vector<Int> resultA, resultB;
    resultA.clear();
    resultB.clear();
    for (auto x : a) resultA.push_back(x);
    for (auto x : b) resultB.push_back(x);
    if (resultA.size() != resultB.size()) return false;
    for (int i = 0; i < (int)resultA.size(); i++) {
        if (resultA[i] != resultB[i]) return false;
    }
    return true;
}
std::pair<bool, double> atChecker() {
    std::deque<Int> a;
    sjtu::deque<Int> b;
    for (int i = 0; i < N; i++) {
        int pos = rand() % (a.size() + 1);
        int tmp = rand();
        a.push_back(tmp);
        b.push_back(tmp);
    }
    timer.init();
    for (int i = 0; i < N; i++) {
        if (a.at(i) != b.at(i)) {
            return std::make_pair(false, 0);
        }
    }
    timer.stop();
    return std::make_pair(true, timer.getTime());
}
void test1(){
    printf("test1: push & pop                    ");
    for(int i=1;i<=N;i++){
        if(i % 10 <= 3) q.push_back(T(i)), stl.push_back(T(i));else
        if(i % 10 <= 7) q.push_front(T(i)), stl.push_front(T(i));else
        if(i % 10 <= 8) q.pop_back(), stl.pop_back();else
        if(i % 10 <= 9) q.pop_front(), stl.pop_front();
    }
    if(!equal()){puts("Wrong Answer");return;}
    while (!q.empty()){
        q.pop_back();
        stl.pop_back();
    }
    puts("Accept");
}
void test2(){
    printf("test2: at & [] & front & back        ");
    int flag = 0;
    try{
        int t = q.front().num();
    }catch(...){flag ++;}

    try{
        int t = q.back().num();
    }catch(...){flag ++;}
    if(flag != 2 && need_to_check_throw){puts("Wrong Answer");return;}
    for(int i=1;i<=N;i++){
        if(i % 10 <= 3) q.push_back(T(i)), stl.push_back(T(i));else
        if(i % 10 <= 7) q.push_front(T(i)), stl.push_front(T(i));else
        if(i % 10 <= 8) q.pop_back(), stl.pop_back();else
        if(i % 10 <= 9) q.pop_front(), stl.pop_front();
    }
    flag = 0;
    try{
        int t = (q.at(q.size() + 100)).num();
    }catch(...){flag = 1;}
    if(flag != 1 && need_to_check_throw){puts("Wrong Answer");return;}
    int num = q.size();
    for(int i=0;i<100;i++)
    {
        int t = rand() % num;
        if(q[t] != stl[t] || q.at(t) != stl.at(t)){puts("Wrong Answer");return;}
    }
    if(q.front() != stl.front() || q.back() != stl.back()){puts("Wrong Answer");return;}
    puts("Accept");
}
void test3(){
    printf("test3: itetator operation            ");
    int num = q.size();
    for(int i =1 ; i <= 1000; i++)
    {
        int t1 = rand() % num;
        int t2 = rand() % num;
        if(*(q.begin() + t1) != *(stl.begin() + t1)){puts("Wrong Answer");return;}
        if(t2 && *(q.end() - t2) != *(stl.end() - t2)){puts("Wrong Answer");return;}
        if((q.begin() + t1) - (q.begin() + t2) != (t1 - t2)){puts("Wrong Answer");return;}
    }
    if((q.begin() + num) != q.end()) {puts("Wrong Answer");return;}
    if((q.end() - num) != q.begin()) {puts("Wrong Answer");return;}
    bool flag=0;
    sjtu::deque<T> other;
    try{
        int t = q.begin() - other.begin();
    }catch(...){
        flag=1;
    }
    if(!flag && need_to_check_throw) {puts("Wrong Answer");return;}
    it_q = q.begin();
    it_stl = stl.begin();
    for(int i=1;i<=10;i++){
        int t = rand() % (num / 10);
        it_q += t;
        it_stl += t;
        if(*it_q != *it_stl) {puts("Wrong Answer");return;}
        if(it_q -> num() != it_stl -> num()) {puts("Wrong Answer");return;}
    }
    it_q = --q.end();
    it_stl = --stl.end();
    if(*it_q != *it_stl) {puts("Wrong Answer");return;}
    for(int i=1;i<10;i++){
        int t = rand() % (num / 10);
        it_q -= t;
        it_stl -= t;
        if(*it_q != *it_stl) {puts("Wrong Answer");return;}
        it_q -> change(t);;
        it_stl -> change(t);
        if(*it_q != *it_stl) {puts("Wrong Answer");return;}
    }
    if(!equal()) {puts("Wrong Answer");return;}
    if (!(q.begin() + 10 == q.begin() +5 + 6 - 1)) {puts("Wrong Answer");return;}
    sjtu::deque<T> pp;
    if(q.end() == pp.end()){puts("Wrong Answer");return;}

    int t = rand() % (q.size() - 1);
    it_q = q.begin() + t;
    it_stl = stl.begin() + t;
    const sjtu::deque<T>::iterator it_q_const(++it_q);
    const std::deque<T>::iterator it_stl_const(++it_stl);
    if(*it_q_const != *it_stl_const){puts("Wrong Answer");return;}
    if(it_q_const -> num() != it_stl_const -> num()){puts("Wrong Answer");return;}
    it_q_const -> change(t);
    it_stl_const -> change(t);
    if(!equal()){puts("Wrong Answer");return;}
    puts("Accept");
}


int main(){
    test1();
    test2();
    test3();
    return 0;
}