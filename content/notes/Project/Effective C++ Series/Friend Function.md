
> 提供私用成員給某些外部函式來存取，這個有權調用某類別私有成員的函式就稱為 Friend Function 

Friend Function 實質上定義在外面，但是在 Class 內部需要用 keyword `friend` 再提及一次該 function。因此，Friend Function 是 Non-member function !

```cpp
class Ball;

int compare(Ball &b1, Ball &b2) {
    // 可直接存取私用成員
    if(b1._radius == b2._radius)
        return 0;
    else if(b1._radius > b2._radius)
        return 1;
    else
        return -1;
}

class Ball { 
public: 
    Ball(double, char*); 
    void radius(double radius) {
        _radius = radius;
    } 
    // 宣告朋友函式 
    friend int compare(Ball&, Ball&);
 
private:
    double _radius; // 半徑
};
```







## Resource

[friend 函式、friend 類別](https://openhome.cc/Gossip/CppGossip/friendFunctionClass.html)
