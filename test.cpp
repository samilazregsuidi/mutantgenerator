#include <iostream>

class Elem;
class A;
class B;
class C;

class Visitor {
public:
	void visit(Elem* e) {
		std::cout<<"visitElem(Elem*)\n";
	}
	void visit(A* e) {
		std::cout<<"visitElem(A*)\n";
	}
	void visit(B* e) {
		std::cout<<"visitElem(B*)\n";
	}
	void visit(C* e) {
		std::cout<<"visitElem(C*)\n";
	}
	
};

class Elem {
public:
	virtual void accept(Visitor* v) {
		std::cout<<"Elem::acceptVisitor(...)\n";
		v->visit(this);
	}
};

class A : public Elem {
public:
	void accept(Visitor* v) override {
		std::cout<<"A::acceptVisitor(...)\n";
		v->visit(this);
	}
};

class B : public A {
public:
	void accept(Visitor* v) override {
		std::cout<<"B::acceptVisitor(...)\n";
		v->visit(this);
	}
};

class C : public Elem {
public:
	void accept(Visitor* v) override {
		std::cout<<"C::acceptVisitor(...)\n";
		v->visit(this);
	}
};

#include <list>

int main() {
	
	Visitor* v = new Visitor();
	std::list<Elem*> elems = { new Elem(), new A(), new B(), new C()};
	for(auto e: elems)
		e->accept(v);
	return 0;
}

