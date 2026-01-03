#include <iostream>

using namespace std;

class dog
{
public:
   //dog(int weight){
   //    cout << "int狗的体重"<<weight<<endl;
   //
   //};
   //dog(double weight){
   //    cout <<"double狗的体重"<<weight<<endl;
   //};
    void getweight(string color,int weight){
        cout << "int类型狗的体重"<<weight<<color<<endl;
    }
    void getweight(double weight){
        cout << "double类型狗的体重"<<weight<<endl;
    }
};

int main()
{
    dog dog1;
    dog1. getweight(50.2);
    dog1. getweight("黑色",50);
    return 0;
}
