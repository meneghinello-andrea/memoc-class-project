::Clean all the working directory
del *.aux
del *.glg
del *.glo
del *.gls
del *.ist
del *.lof
del *.log
del *.lot
del *.out
del *.toc
del *.pdf
cd Frontespiece
del *.aux
del *.log
del *.pdf
del *-frn.tex
cd ..

::Run the document compilation
cd Frontespiece
pdflatex Frontespiece.tex
pdflatex Frontespiece-frn.tex
pdflatex Frontespiece.tex
cd ..
pdflatex Master.tex
makeglossaries Master
pdflatex Master.tex
pdflatex Master.tex