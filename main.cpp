#include "Event.h"
//ʾ�������ź����
//�ۺ�������������źŲ����Ե� ����������һ��

class Button
{
private:
	int data = 0;
public:
	void setData(int num) { data = num; }
	void printData() { std::cout << "���ں���,������" << data << std::endl; };
	Event<int> clicked;
};

void print(int num)
{
	std::cout << "��ͨ����" << " �����ǣ�" << num << std::endl;
}


int main()
{
	Button* button = new Button();
	button->clicked.connect(&print);
	button->clicked.connect(button,&Button::setData);
	button->printData();
	int lambdaSn = button->clicked.connect([=](int data)
		{
			std::cout << "����lambda,�����ǣ�" << data << '\n';
			std::cout << "�һ��ܸ��ⲿ������ֵ\n";
			button->setData(1000);
			button->printData();
		});
	button->clicked.emit(100);
	std::cout << "\n\n\n\n";
	button->clicked.disconncet(lambdaSn);
	button->clicked.emit(11111);
}