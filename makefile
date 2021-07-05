LEX_FILE=lex.l
BISON_FILE=parse.y


LEX_OUTPUT= lex.yy.cpp
BISON_OUTPUT=$(patsubst %.y,%.cpp,$(BISON_FILE))
GENERATOR_OUTPUT= generator.cpp
OUTPUT=pythoncc

all:	$(OUTPUT)

$(LEX_OUTPUT):	$(LEX_FILE)
	flex  -o $(LEX_OUTPUT) $(LEX_FILE)

$(BISON_OUTPUT):	$(BISON_FILE)
	bison -d -o $(BISON_OUTPUT) $(BISON_FILE)	


$(OUTPUT):	$(LEX_OUTPUT) $(BISON_OUTPUT) $(GENERATOR_OUTPUT)
	g++ -g $(CFLAGS) -o $(OUTPUT) parse.cpp lex.yy.cpp generator.cpp `llvm-config --cppflags --ldflags --libs core jit native all` -lfl 
