#Makefile pour les courbes de Bézier
#R. RAFFIN, Dept Info, Arles

compilateur = g++
preproc_options = -c -Wall
link_options = -Wall
libs = -lGLEW -lGL -lGLU -lglut
main = TP4Bezier

all: $(main)
	@echo "\ncompilation terminee"

$(main): point3.o TP4Bezier.o
	@echo "--- compilation de $@ ..."
	$(compilateur) $(link_options) $^ $(libs) -o $@
	@echo "--- compilation de $@ terminée"

point3.o: point3.cpp point3.h
	$(compilateur) $(preproc_options) $<

TP4Bezier.o: TP4Bezier.cpp
	$(compilateur) $(preproc_options) $<

clean:
	rm -f *.o $(main) *~

archive:
	tar czvf $(main).tgz *.cpp *.h makefile
