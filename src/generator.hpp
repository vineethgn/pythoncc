#include <string>
#include <llvm/Module.h>
using namespace llvm;
class Node {
public:
	Node* leftchild;
	Node* rightchild;

	void add_rightchild(Node *);
	void add_leftchild(Node *);
	
	virtual void generator(Module *);	
	virtual std::string type(){}
	
	virtual std::string get_value(){}
	virtual void put_value(std::string){}
	
	Node();
};


class Nprint: public Node {
public:
	
	Nprint();	

	void generator(Module *);
	std::string type();
	
	std::string get_value();
	void put_value(std::string);
	
};
	
class Nstring: public Node {
public:
	std::string value;
	
	Nstring(std::string*);
	
	void generator(Module *);
	std::string type();
	std::string get_value();
	void put_value(std::string);

};

class Nnumber: public Node {
public:
	std::string value;
	Nnumber(std::string*);
	
	void generator(Module *);
	std::string type();
	
	std::string get_value();
	void put_value(std::string);
};

class Nassign: public Node {
public:
	Nassign();
	void generator(Module *);
	std::string type();
	
	std::string get_value();
	void put_value(std::string);
};

class Noperator: public Node {
public:
	std::string value;
	Noperator();
	void generator(Module *);
	void add();
	std::string type();
	
	std::string get_value();
	void put_value(std::string);
};

class Nidentifier: public Node {
public:
	std::string id;
	Nidentifier(std::string *);
	std::string* add(std::string*);
	void generator(Module *);
	std::string type();
	
	std::string get_value();
	void put_value(std::string);
};
	
	
