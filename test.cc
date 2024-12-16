#include <iostream>

namespace sex {
	int a = 6;
}

class C {
public:
	int a = 5;
	void func() {
		std::cout << sex::a;
	}
};

int main() {
	C c;
	c.func();
}
