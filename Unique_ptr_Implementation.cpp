#include<iostream>
using namespace std;

template<class T>
class Unique_ptr{
    private :
    T* m_ptr;

    public:
    Unique_ptr(): m_ptr(nullptr){} 
    Unique_ptr(T* ptr) : m_ptr(ptr){ }

    // unique pointer cannot be copied to another pointer , hence delete copy constructor and assigment operator
    Unique_ptr(const Unique_ptr<T>& other) = delete;
    Unique_ptr& operator=(const Unique_ptr<T>& other) = delete;

    Unique_ptr(Unique_ptr&& other) // move constructor
    {
        m_ptr=other.m_ptr;
        other.m_ptr=nullptr;
    }

    Unique_ptr& operator=(Unique_ptr<T>&& other){  //move assignment operator
        if(this!=&other){
            delete m_ptr;
            m_ptr=other.m_ptr;
            other.m_ptr=nullptr;
        }
        return *this;
    }

    T* get(){
        return m_ptr;
    }

    void reset(T* ptr = nullptr){
        delete m_ptr;
        m_ptr=ptr;
    }

    T& operator*()
    {
        return *m_ptr;
    }

    T* operator->(){
        return m_ptr;
    }

    ~Unique_ptr(){
            delete m_ptr;
            m_ptr=nullptr;
    }

};

int main(){
    Unique_ptr<int> p1(new int(10)); 
    cout << "First Unique ptr : " << (*p1) << endl;
    cout <<  "Address of my pointer : " << p1.get() << endl; 
    Unique_ptr<int> p2 = move(p1); 
    cout <<  "Address of my new pointer p2 : " << p2.get() << "and value is : " << (*p2) << endl; 
    cout <<  "Address of old pointer p1 : " << p2.get() << "and value is : " << (*p1) <<endl; 
}