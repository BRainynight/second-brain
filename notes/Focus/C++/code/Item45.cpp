// g++ -o main .\Item45.cpp
#include <iostream>
class Top { 
    public:
        Top(int id):m_id(id) {};
        Top():m_id(-1) {};
        int m_id;
        virtual void print() const {
            std::cout<<"Top "<< m_id <<std::endl;
        }

};

class Middle: public Top { 
    public:
        virtual void print() const override {
            std::cout<<"Middle"<<std::endl;
        }    
};

class Bottom: public Middle { 
    public:
        virtual void print() const override  {
            std::cout<<"Bottom"<<std::endl;
        }    
};

template<typename T>
class SmartPtr {
public:
    explicit SmartPtr(T *realPtr) { heldPtr = realPtr; }
    T* get() const { return heldPtr; }
    void print() { heldPtr->print(); }
private:
    T *heldPtr;
};

template<>
class SmartPtr<Top> {
public:
    explicit SmartPtr(Top *realPtr) { heldPtr = realPtr; }
    Top* get() const { return heldPtr; }

	SmartPtr(const SmartPtr<Middle>& other) { heldPtr = other.get(); }
	SmartPtr(const SmartPtr<Bottom>& other) { heldPtr = other.get(); }
    void print() { heldPtr->print(); }
private:
    Top *heldPtr;
};


int main() {
    SmartPtr<Top> pt0 = SmartPtr<Top>(new Top);
    SmartPtr<Top> pt1 = SmartPtr<Middle>(new Middle);
    SmartPtr<Top> pt2 = SmartPtr<Bottom>(new Bottom);
    // SmartPtr<const Top> pct2 = pt1; 

    pt0.print();
    pt1.print();
    pt2.print();



    // Top *pt1 = new Middle; // convert Middle* ⇒ Top*
    // Top *pt2 = new Bottom; // convert Bottom* ⇒ Top*
    // const Top *pct2 = pt2; // convert Top* ⇒ const Top*
    // const Top *pct1 = pt1;

    // pt1->print();
    // pt2->print();
    // pct2->print();
    // pct1->print();
    
}