#include <iostream>
#include <string>

using namespace std;

class dog{
    //不写关键字的时候，就是private属性的
public:
    string name;
    int age;
    void run(){
               cout << "都会" << endl;
             }
private:
    double weight;
};

int main()
{
    //从栈中实例化对象
    dog dog1;
    dog1.name="旺财";
    cout << dog1.name <<endl;
    dog1.run();
    //从堆中实例化对象,要使用delete删除
    dog *dog2 =new dog;
    dog2->age=3;
    cout << dog2->age << endl;
    delete dog2;
    return 0;
}
