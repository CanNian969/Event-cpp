#include "Event.h"
//示例代码信号与槽
//槽函数参数必须和信号参数对等 类型数量都一样

class Button
{
private:
	int data = 0;
public:
	void setData(int num) { data = num; }
	void printData() { std::cout << "类内函数,参数是" << data << std::endl; };
	Event<int> clicked;
};

void print(int num)
{
	std::cout << "普通函数" << " 参数是：" << num << std::endl;
}


int main()
{
	Button* button = new Button();
	button->clicked.connect(&print);
	button->clicked.connect(button,&Button::setData);
	button->printData();
	int lambdaSn = button->clicked.connect([=](int data)
		{
			std::cout << "我是lambda,参数是：" << data << '\n';
			std::cout << "我还能改外部变量的值\n";
			button->setData(1000);
			button->printData();
		});
	button->clicked.emit(100);
	std::cout << "\n\n\n\n";
	button->clicked.disconncet(lambdaSn);
	button->clicked.emit(11111);
}