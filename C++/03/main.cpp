#include <iostream>

using namespace std;

class dog{
public:
    dog(){
        cout << "构造函数" <<endl;
    }
    ~dog();

};
dog::~dog()
{
    cout << "析构函数被执行啦" << endl;
}

int main()
{
    //dog dog1;//两个函数都能被执行
    dog *dog2 =new dog;//当没有使用delete函数时，只有构造函数被执行啦，因为堆中实例化需要使用delete删除
    delete dog2;
    return 0;
}
