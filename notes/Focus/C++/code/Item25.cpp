namespace std {
    template<typename T>
    void swap (T& a, T& b) {
        T tmp(a);
        a = b;
        b = tmp;
    }
}

class WidgetImpl {
private:
    int a, b, c; 
    ... // a lot of data
}

class Widget {
public:
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs) {
        *pImpl = *(rhs.pImpl); // copy assignment: 把 WidgetImpl 的每一個內容都複製一份過來
    }

private:
    WidgetImpl* pImpl;
}
