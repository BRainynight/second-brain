#include <string>
#include <iostream>
// g++ -o main Item3.cpp
class TextBlock
{
public:
    TextBlock(std::string text):m_text(text) { }

	// operator[] for const objects
	// const char& operator[](std::size_t position) const
	// { 
    //     std::cout<<"call const func ";
    //     return m_text[position]; 
    // }
	
	// operator[] for non-const objects
	char& operator[](std::size_t position) 
	{ 
        std::cout<<"call non-const func ";
        return m_text[position]; 
    }

private:
	std::string m_text;
};

int main() {
    TextBlock t1 = TextBlock("AAAA");
    // auto t2 = const t1;
    const TextBlock t2 = TextBlock("BBB");
    std::cout<<t1[0] << std::endl; 
    std::cout<<t2[0] <<std::endl;
}