#include<iostream>
using namespace std;

template<class T>
class Shared_ptr{
    private :
    T* m_ptr;
    int* m_count;
    void release(){
        if(m_count){
            (*m_count)--;
            if((*m_count)==0){
                delete m_ptr;
                delete m_count;
                m_ptr=nullptr;
                m_count=nullptr;
            }
        }
    }

    public:
    Shared_ptr(): m_ptr(nullptr),m_count(nullptr){} 
    Shared_ptr(T* ptr) : m_ptr(ptr), m_count(new int(1)) {

    } 
    Shared_ptr(const Shared_ptr<T>& other)
    {
        m_ptr=other.m_ptr;
        m_count= other.m_count;
        (*m_count)++;
    }

    Shared_ptr(Shared_ptr&& other) // move constructor
    {
        m_ptr=other.m_ptr;
        m_count=other.m_count;
        other.m_ptr=nullptr;
        other.m_count=nullptr;
    }

    Shared_ptr& operator=(const Shared_ptr<T>& other){ //copy assignment operator
        if(this!=&other){
            release();
            m_ptr=other.m_ptr;
            m_count=other.m_count;
            (*m_count)++;
        }
        return *this;
    }

    Shared_ptr& operator=(Shared_ptr<T>&& other){  //move assignment operator
        if(this!=&other){
            release();
            m_ptr=other.m_ptr;
            m_count=other.m_count;
            other.m_ptr=nullptr;
            other.m_count=nullptr;
        }
        return *this;
    }

    T* get(){
        return m_ptr;
    }

    void reset(T* ptr = nullptr){
        release();
        m_ptr=ptr;
        if(ptr){
        m_count= new int(1);
        }
    }

    T& operator*()
    {
        return *m_ptr;
    }

    T* operator->(){
        return m_ptr;
    }

    ~Shared_ptr(){
        release();
    }
};

int main()
{
    Shared_ptr<int> ptr1(new int(10));
    cout << "First Pointer : " << (*ptr1);
    Shared_ptr<int> ptr2;
    Shared_ptr<int> ptr3(ptr1);
    Shared_ptr<int> ptr4=std::move(ptr1);
    ptr3=ptr1; //copy assignment operator
    ptr3 = std::move(ptr2);
    cout<< (*ptr3);
   // ptr3->func();
    //ptr3.get_count();
    ptr3.get();
    ptr3.reset(new int(6));
    //Destructor
}