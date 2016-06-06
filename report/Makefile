all: $(patsubst %.tex,%.pdf,$(wildcard *.tex))

.PRECIOUS: %.pdf

% : report.pdf
	@echo -n ""

%.dvi: report.tex
	latex $<
	latex $<

%.ps: report.dvi
	dvips -t letter -Ppdf -G0 $< -o $@

%.pdf: report.ps
	ps2pdf $<

clean:
	rm -rf *.bbl *.blg *.aux *.log *~ *.bak *.ps *.dvi *.log *.out *.tmp 

cleanall:
	rm -rf *.bbl *.blg *.aux *.log *~ *.bak *.ps *.dvi *.log report.pdf svnver.tex *.out *.tmp 

spell:
	ispell -f ispell.words -t *.tex
