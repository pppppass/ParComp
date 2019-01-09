PGJOBJS = Figure1.pgf Figure2.pgf Figure3.pgf
TBLOBJS = Table1.tbl
RUNOBJS = Problem.run

.PHONY: all
all: template recursive

.PHONY: template
template:
	$(MAKE) -C ptmpls

.PHONY: recursive
recursive: template
	for DIR in $(DIRS);\
	do\
		$(MAKE) -C $${DIR};\
	done
