#############################################################################
# DAVID VARGAS CARRILLO
# https://github.com/dvcarrillo
#
# Implementación de la clase Matriz2D
#
# Fichero: Matriz2D.cpp
#############################################################################

BIN = bin
SRC = src
OBJ = obj
LIB = lib
INCLUDE = include

#................................................
all:  preambulo \
	  mr.proper\
	  bibliotecas \
	  $(LIB)/libMatriz2D.a \
	  fin-bibliotecas \
	  ejecutables \
	  $(BIN)/DemoMatriz2D \
	  fin-ejecutables

#................................................
preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo DAVID VARGAS CARRILLO
	@echo https://github.com/dvcarrillo
	@echo
	@echo Compilando programa...
	@echo ------------------------------------------------------------
	@echo
	
	mkdir {bin,doc,lib,obj}
#................................................

ejecutables:
	@echo Creando ejecutables...

fin-ejecutables:
	@echo Creados
	@echo 	

bibliotecas:
	@echo Creando modulos objeto y bibliotecas...

fin-bibliotecas:
	@echo Creados
	@echo 

#................................................
# EJECUTABLES

$(BIN)/DemoMatriz2D : $(OBJ)/DemoMatriz2D.o $(LIB)/libMatriz2D.a
	g++ -o $(BIN)/DemoMatriz2D $(OBJ)/DemoMatriz2D.o -lMatriz2D -L$(LIB)

#................................................
# OBJETOS

 $(OBJ)/DemoMatriz2D.o : $(SRC)/DemoMatriz2D.cpp $(INCLUDE)/Matriz2D.h
	g++ -c -o $(OBJ)/DemoMatriz2D.o $(SRC)/DemoMatriz2D.cpp -I$(INCLUDE)

#................................................
# BIBLIOTECAS

$(LIB)/libMatriz2D.a : $(OBJ)/Matriz2D.o
	ar -rvs $(LIB)/libMatriz2D.a $(OBJ)/Matriz2D.o

$(OBJ)/Matriz2D.o : $(SRC)/Matriz2D.cpp $(INCLUDE)/Matriz2D.h
	g++ -c -o $(OBJ)/Matriz2D.o $(SRC)/Matriz2D.cpp -I$(INCLUDE)


#................................................
# LIMPEZA

clean: clean-objs clean-libs

clean-objs: 
	@echo Borrando objetos...

	-rm $(OBJ)/DemoMatriz2D.o 

	@echo ...Borrados
	@echo 

clean-libs: 
	@echo Borrando modulos objeto y bibliotecas...

	-rm $(OBJ)/Matriz2D.o
	-rm $(LIB)/libMatriz2D.a

	@echo ...Borrado
	@echo 

clean-bins: 
	@echo Borrando ejecutables...

	-rm $(BIN)/DemoMatriz2D 

	@echo ...Borrados
	@echo 

mr.proper:  clean clean-bins 

#................................................
