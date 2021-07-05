#include "generator.hpp"
#include "parse.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Constants.h>
#include <llvm/GlobalVariable.h>
#include <llvm/Function.h>
#include <llvm/CallingConv.h>
#include <llvm/BasicBlock.h>
#include <llvm/Instructions.h>
#include <llvm/InlineAsm.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>
#include <llvm/Pass.h>
#include <llvm/PassManager.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <algorithm>
#include <fstream>
#include <llvm/Bitcode/ReaderWriter.h>
#include<cstdlib>
using namespace llvm;
Function* func_printf ;
Function* func_main ;
Function* func_putchar ;

CallInst* int32_9;
Constant* const_ptr_7;
std::vector<Value*> int32_55_params;
FunctionType* FuncTy_4;
BasicBlock* label_entry;
extern void input(char *);
extern void close();
extern int yyparse();
int flag=0;
extern Node* root;


//Constructors
Node :: Node() 
{
		leftchild=NULL;
		rightchild=NULL;
}

Nprint :: Nprint(): Node()
{
	
}

Nstring :: Nstring(std::string* val):Node()
{			

	value=*val;
	if(value.at(0) == '\"')
	{
		value.erase(0,1);
		value.erase(value.end()-1);
	}
}

Nnumber :: Nnumber(std::string* val):Node()
{
	value=*val;
	if(value.at(0) == '\"')
	{
		value.erase(0,1);
		value.erase(value.end()-1);
	}
}

Nassign:: Nassign():Node()
{
}

Noperator:: Noperator():Node()
{
}

Nidentifier:: Nidentifier(std::string* val):Node()
{
	id=*val;
}
//Child functions

void Node :: add_rightchild(Node* child) 
{
	rightchild = child;
}	

void Node :: add_leftchild(Node* child) 
{
	leftchild = child;
}

//Type functions

std::string Nstring:: type()
{
	return("string");
}

std::string Nprint:: type()
{
}

std::string Nnumber:: type()
{
	return("number");
}

std::string Nassign:: type()
{
}

std::string Noperator:: type()
{
}

std::string Nidentifier:: type()
{
}


//Get_value functions

std::string Nstring:: get_value()
{
	return(this->value);
}

std::string Nprint:: get_value()
{
}

std::string Nnumber:: get_value()
{
	return(this->value);
}

std::string Noperator:: get_value()
{
}

std::string Nassign:: get_value()
{
}

std::string Nidentifier:: get_value()
{
}


//Put_value functions

void Nstring:: put_value(std::string str)
{
	this->value=str;
}

void Nnumber:: put_value(std::string str)
{
	this->value=str;
}

void Nprint:: put_value(std::string str)
{
}

void Nassign:: put_value(std::string str)
{
}

void Noperator:: put_value(std::string str)
{
}

void Nidentifier:: put_value(std::string str)
{
}

//Generator functions
void Node :: generator(Module *Mod)
{
	if(this->leftchild != NULL)
		this->leftchild->generator(Mod);
	if(this->rightchild != NULL)
		this->rightchild->generator(Mod);
}

void Nstring::generator(Module *Mod)
{
	std::string str1=this->value;
	int size= str1.length()+1;
	//this->value;
	if (flag!=0)
	{
 		ConstantInt* const_int32_3 = ConstantInt::get(getGlobalContext(), APInt(32,  StringRef("10"), 10));
		CallInst::Create(func_putchar, const_int32_3, "", label_entry);

	}

	ArrayType* ArrayTy_0 = ArrayType::get(IntegerType::get(getGlobalContext(), 8), size);
	PointerType* PointerTy_1 = PointerType::get(ArrayTy_0, 0);
	GlobalVariable* gvar_array__str = new GlobalVariable(/*Module=*/*Mod, 
	/*Type=*/ArrayTy_0,
	/*isConstant=*/true,
	/*Linkage=*/GlobalValue::PrivateLinkage,
	/*Initializer=*/0, // has initializer, specified below
	/*Name=*/".str");
	gvar_array__str->setAlignment(1);
  
	 // Constant Definitions
  	Constant* const_array_6 = ConstantArray::get(getGlobalContext(), str1, true);
 	std::vector<Constant*> const_ptr_7_indices;
  	ConstantInt* const_int64_8 = ConstantInt::get(getGlobalContext(), APInt(64,  StringRef("0"), 10));
  	const_ptr_7_indices.push_back(const_int64_8);
  	const_ptr_7_indices.push_back(const_int64_8);
  	const_ptr_7 = ConstantExpr::getGetElementPtr(gvar_array__str, &const_ptr_7_indices[0], const_ptr_7_indices.size() );
	gvar_array__str->setInitializer(const_array_6);
    	int32_55_params.push_back(const_ptr_7);
	CallInst::Create(func_printf, int32_55_params.begin(),int32_55_params.end(),"", label_entry);
	int32_55_params.pop_back();
	flag=1;
	
}

void Nnumber :: generator(Module *Mod)
{
	std::string str1=this->value;	
	int size= str1.length()+1;
	//this->value;
	if (flag!=0)
	{
 		ConstantInt* const_int32_3 = ConstantInt::get(getGlobalContext(), APInt(32,  StringRef("10"), 10));
		CallInst::Create(func_putchar, const_int32_3, "", label_entry);
	}
	ArrayType* ArrayTy_0 = ArrayType::get(IntegerType::get(getGlobalContext(), 8), size);
	PointerType* PointerTy_1 = PointerType::get(ArrayTy_0, 0);
	GlobalVariable* gvar_array__str = new GlobalVariable(/*Module=*/*Mod, 
	/*Type=*/ArrayTy_0,
	/*isConstant=*/true,
	/*Linkage=*/GlobalValue::PrivateLinkage,
	/*Initializer=*/0, // has initializer, specified below
	/*Name=*/".str");
	gvar_array__str->setAlignment(1);
  
	 // Constant Definitions
  	Constant* const_array_6 = ConstantArray::get(getGlobalContext(), str1, true);
 	std::vector<Constant*> const_ptr_7_indices;
  	ConstantInt* const_int64_8 = ConstantInt::get(getGlobalContext(), APInt(64,  StringRef("0"), 10));
  	const_ptr_7_indices.push_back(const_int64_8);
  	const_ptr_7_indices.push_back(const_int64_8);
  	const_ptr_7 = ConstantExpr::getGetElementPtr(gvar_array__str, &const_ptr_7_indices[0], const_ptr_7_indices.size() );
gvar_array__str->setInitializer(const_array_6);
    	int32_55_params.push_back(const_ptr_7);
CallInst::Create(func_printf, int32_55_params.begin(),int32_55_params.end(),"", label_entry);
	int32_55_params.pop_back();
  	flag=1;
}
void Nprint :: generator(Module *Mod)
{
	char* str;
	if(this->leftchild != NULL)
		this->leftchild->generator(Mod);
}

void Nassign :: generator(Module *Mod)
{

}

void Nidentifier :: generator(Module *Mod)
{
}

void Noperator :: generator(Module *Mod)
{
		if(this->leftchild->type().compare(this->rightchild->type()) ==0)
		{
			std::string str = this->leftchild->type();
			if(str.compare("string")==0 && this->value == "+")
			{
				this->leftchild->put_value(this->leftchild->get_value().append(this->rightchild->get_value()));
				this->rightchild=NULL;
			}
			else if(str.compare("number")==0)
			{
				int num1,num2;
				std::istringstream stoi1(this->leftchild->get_value());
				stoi1>>num1;
				std::istringstream stoi2(this->rightchild->get_value());
				stoi2>>num2;
				std::ostringstream itos;
				if(this->value == "+") itos<< num1+num2;
				else if(this->value == "-") itos<< num1-num2;
				else if(this->value == "*") itos<< num1*num2;
				else if(this->value == "/") itos<< num1/num2;
				this->leftchild->put_value(itos.str());
				this->rightchild=NULL;
			}
			this->leftchild->generator(Mod);
		}
		else
		{
			std::cout<<"Syntax error. Invalid operation";
			exit(0);
		}
}

//main function
main(int argc, char** argv)
{	
	//Creating module for llvm
	Module* Mod = new Module("new", getGlobalContext());
	//verifyModule(*Mod, PrintMessageAction);

	//Streaming from an input python file
	--argc;	++argv;
	if(argc > 0)
	{
		input(argv[0]);
	}
	yyparse();
	close();

	//Adding main function to llvm module

	std::vector<const Type*>FuncTy_2_args;	
	FunctionType* FuncTy_2 = FunctionType::get(
	/*Result=*/Type::getVoidTy(getGlobalContext()),
    	/*Params=*/FuncTy_2_args,
    	/*isVarArg=*/true);
	Function* func_main = Function::Create(
   	/*Type=*/FuncTy_2,
	/*Linkage=*/GlobalValue::ExternalLinkage,
	/*Name=*/"main", Mod); 
  	func_main->setCallingConv(CallingConv::C);
	AttrListPtr func_main_PAL;
 	{
		SmallVector<AttributeWithIndex, 4> Attrs;
		AttributeWithIndex PAWI;
		PAWI.Index = 4294967295U; PAWI.Attrs = 0  | Attribute::NoUnwind;
		Attrs.push_back(PAWI);
		func_main_PAL = AttrListPtr::get(Attrs.begin(), Attrs.end());
    
  	}
  	func_main->setAttributes(func_main_PAL);
	label_entry = BasicBlock::Create(getGlobalContext(), "entry",func_main,0);
std::vector<const Type*>FuncTy_4_args;
  	PointerType* PointerTy_5 = PointerType::get(IntegerType::get(getGlobalContext(), 8), 0);
  
  	FuncTy_4_args.push_back(PointerTy_5);
  	FunctionType* FuncTy_4 = FunctionType::get(
   	/*Result=*/IntegerType::get(getGlobalContext(), 32),
    	/*Params=*/FuncTy_4_args,
    	/*isVarArg=*/true);
 func_printf = Function::Create(
    /*Type=*/FuncTy_4,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"printf", Mod); // (external, no body)
  func_printf->setCallingConv(CallingConv::C);
  AttrListPtr func_printf_PAL;
  {
    SmallVector<AttributeWithIndex, 4> Attrs;
    AttributeWithIndex PAWI;
    
    PAWI.Index = 4294967295U; PAWI.Attrs = 0  | Attribute::NoUnwind;
    Attrs.push_back(PAWI);
    func_printf_PAL = AttrListPtr::get(Attrs.begin(), Attrs.end());
    
  }
  func_printf->setAttributes(func_printf_PAL);
std::vector<const Type*>FuncTy_6_args;
  FuncTy_2_args.push_back(IntegerType::get(getGlobalContext(), 32));
  FunctionType* FuncTy_6 = FunctionType::get(
    /*Result=*/IntegerType::get(getGlobalContext(), 32),
    /*Params=*/FuncTy_6_args,
    /*isVarArg=*/true);


func_putchar = Function::Create(
    /*Type=*/FuncTy_6,
    /*Linkage=*/GlobalValue::ExternalLinkage,
    /*Name=*/"putchar", Mod); // (external, no body)
  func_putchar->setCallingConv(CallingConv::C);
  AttrListPtr func_putchar_PAL;
  {
    SmallVector<AttributeWithIndex, 4> Attrs;
    AttributeWithIndex PAWI;
    PAWI.Index = 4294967295U; PAWI.Attrs = 0  | Attribute::NoUnwind;
    Attrs.push_back(PAWI);
    func_putchar_PAL = AttrListPtr::get(Attrs.begin(), Attrs.end());
    
  }
  func_putchar->setAttributes(func_putchar_PAL);
/*int32_9->setCallingConv(CallingConv::C);
	int32_9->setTailCall(true);AttrListPtr int32_9_PAL;

	SmallVector<AttributeWithIndex, 4> Attrs;
	AttributeWithIndex PAWI;
	PAWI.Index = 4294967295U; PAWI.Attrs = 0  | Attribute::NoUnwind;
	Attrs.push_back(PAWI);
	int32_9_PAL = AttrListPtr::get(Attrs.begin(), Attrs.end());
      
    	int32_9->setAttributes(int32_9_PAL);*/
	root->generator(Mod);

	
    	BasicBlock* label_return = BasicBlock::Create(getGlobalContext(), "return",func_main,0);
    
	// Block entry (label_entry)
	
//int32_55_params.erase();
    ConstantInt* const_int32_3 = ConstantInt::get(getGlobalContext(), APInt(32,  StringRef("10"), 10));
CallInst::Create(func_putchar, const_int32_3, "", label_entry);

    	BranchInst::Create(label_return, label_entry);
    
    	// Block return (label_return)
    	ReturnInst::Create(getGlobalContext(), label_return);
    
  	verifyModule(*Mod, PrintMessageAction);
  	std::ofstream obj;
  	obj.open("main.o");
   
   	WriteBitcodeToFile(Mod,obj);
   	obj.close();
   	system("llc main.o -f");
   	system("g++ main.o.s");
}
