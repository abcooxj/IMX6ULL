#include <iostream>

using namespace std;

//这个就是基类，也是父类
class animal
{
public:
    string name;
    int age;
    void run()
    {
        cout << "狗的年龄：" << age<<endl;
    }
private:
    double weight;
protected:
    string color;
};
//私有继承
class dog:public animal
{
public :
    void eat(){

        this->name="旺财";
        this->color="黑色";
    }
};

int main()
{
    dog dog1;
    dog1.age=5;
    dog1.run();
    return 0;
}
