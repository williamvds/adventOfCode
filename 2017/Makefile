KEEP = $(wildcard *.cpp) Makefile
CLEAN = $(filter-out ${KEEP}, $(wildcard *))
clean:
	for FILE in ${CLEAN}; do rm $$FILE; done
