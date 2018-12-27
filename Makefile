PGJOBJS = Figure1.pgf Figure2.pgf Figure3.pgf
TBLOBJS = Table1.tbl
RUNOBJS = Problem.run

.PHONY: all
all: hardware.txt environment.yml report

Report.pdf: Report.tex Report.bbl $(PGFOBJS) $(TBLOBJS) | pnote.cls pdef.sty Report.aux
	lualatex Report.tex

Report.aux: Report.tex Report.bbl | pnote.cls pdef.sty
	lualatex Report.tex

Report.bbl: Report.tex | pnote.cls pdef.sty
	lualatex Report.tex
	biber Report

pnote.cls pdef.sty:
	ln -s ptmpls/pdef.sty .
	ln -s ptmpls/pnote.cls .

.SECONDEXPANSION:
$(PGFOBJS) $(TBLOBJS): $(wildcard $(RUNOBJS))
	touch $@

.PRECIOUS: %.py
%.py: %.ipynb
	jupyter nbconvert --to script $*

%.run: %.py samp.so
	python $<
	touch $@

setup.cfg:
	if [ -z "$$CONDA_PREFIX" ];\
	then\
		echo "Anaconda not found";\
		exit 1;\
	fi
	echo "[build_ext]" > setup.cfg
	echo "include_dirs=${CONDA_PREFIX}/include" >> setup.cfg
	echo "library_dirs=${CONDA_PREFIX}/lib" >> setup.cfg

samp.so: setup.py setup.cfg samp/samplers.c samp/utils.c samp/wrappers.c samp/samp.h
	python setup.py build_ext --inplace
	FILENAMES=`ls | grep 'samp.*\.so' | grep -v 'samp.so'`;\
	for FILE in $${FILENAMES};\
	do\
		mv $${FILE} samp.so;\
	done

Main: Main.c samp/samplers.c samp/utils.c samp/samp.h
	gcc Main.c samp/samplers.c samp/utils.c -o Main -O3 -fopenmp -lm

hardware.txt:
	echo 'lscpu:' > hardware.txt
	lscpu >> hardware.txt
	echo 'lsmem:' >> hardware.txt
	lsmem >> hardware.txt
	echo 'uname -a:' >> hardware.txt
	uname -a | awk '$$2="********"' >> hardware.txt

environment.yml:
	conda env export | grep -v prefix > environment.yml

.PHONY: template
template:
	$(MAKE) -C ptmpls

.PHONY: environment
environment: environment.yml
	conda env create -f environment.yml

.PHONY: report
report: Report.pdf

.PHONY: run
run: $(RUNOBJS)

.PHONY: bench
bench: Main run.slurm
	sbatch run.slurm
