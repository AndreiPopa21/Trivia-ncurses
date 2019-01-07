Numele aplicatiei: Trivia
Creator: Popa Stefan-Andrei 313CC

Aplicatia se deschid printr-un Splash Screen care prezinta titlul si autorul aplicatiei printr-o animatie.
Dupa ce se inchide Splash Screen-ul, aplicatia intra in meniul principal si de acolo, utilizatorul poate sa selecteze dintre 4 optiuni:
New Game, Resume Game, Quit, How To Play. Navigatia in aplicatie se face exclusiv din tastatura, prin taste specifice si prin sagetile
UP and DOWN.

La inceput cand se deschide pentru prima data meniul, inainte ca orice sesiune de joc sa fie
inceputa, optiunea Resume Game nu poate fi accesata, iar pe ecran apare un mesaj sugestiv care explica asta. In aplicatie, toate textele
sunt afisate in limba engleza. Apasand optiunea de New Game, se incepe o noua sesiune de joc cu 10 intrebari. Optiunea Quit iese din aplicatie,
iar optiunea How To Play deschide o fereastra in care sunt clarificate controalele.

Odata ce se incepe o noua sesiune de joc, se porneste de la intrebarea 1, iar initial, inainte de orice fel de actiune, optiunile de
50/50 si Skip sunt active. Daca sunt active, ele se pot vedea in fereastra jocului in stanga, respectiv dreapta ferestrei. Cand una este
folosita, inceteaza sa mai fie vizibila pe ecran si implicit utilizabila pentru restul sesiunii de joc. Jucatorul navigheaza cu sagetile
UP and DOWN printre raspunsuri, iar prin ENTER confirma alegerea. In stanga-sus, se poate vedea scorul curent, iar in dreapta-sus, ora si data
curenta locala. Apasand tasta R, se updateaza timpul afisat. Daca se apasa Q, se pauzeaza jocul curent si se revine in meniul principal.
Jucatorul poate reveni totusi in sesiunea curenta selectand Resume Game, optiune ce devine de data asta activa.

Dupa ce utilizatorul a raspuns la toate cele 10 intrebari, se afiseaza o fereastra cu scorul obtinut, numarul de intrebari gresite, precum si
numarul de intrebari corecte. Apasand orice tasta, se revine in meniul principal de unde poate fi inceputa o noua sesiune de joc.

Pe intreg parcursul jocului, jucatorul este insotit de mesaje sugestive, si in cazul executarii unor comenzi invalide, aplicatia incearca sa
ofere cat mai mult feedback cu putinta.

Dimensiunea ideala a terminalului pentru rularea aplicatiei este: 90 X 25, 100 X 30. In cazul unei dimensiuni prea mici, elementele vor arata haotic
pe ecran, iar in cazul unei dimensiuni prea mari, elementele vor fi prea indepartate. Pozitionarea elementelor grafice este in principal, relativa
fata de dimensiunile ecranului.

Intrebarile sunt descrise in fisierele date drept parametrii executabilului dupa urmatorul format:
<Intrebare>|<Majuscula corespunzatoare raspunsului corect>
A<raspunsul_a>|B<raspunsul_b>|C<raspunsul_c>|D<raspunsul_d>

Programul foloseste strtok cu delimitatorii "|" si "\n" pentru a-si extrage corect informatia din fisiere.
Intrebarile sunt despartite in fisier printr-un rand liber. (A se vedea formatul file1.txt, file2.txt)


Descrierea implementarii programului:
Crearea executabilului foloseste 
