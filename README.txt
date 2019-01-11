Numele aplicatiei: Trivia
Autor: Popa Stefan-Andrei 313CC
Timp de implementare: aproximativ 1-2 saptamani



Executia jocului:

Aplicatia se deschid printr-un Splash Screen care prezinta titlul si autorul aplicatiei 
printr-o animatie. Dupa ce se inchide Splash Screen-ul, aplicatia intra in meniul principal 
si de acolo, utilizatorul poate sa selecteze dintre 5 optiuni: New Game, Resume Game, Quit,
How To Play, Scoreboard. Navigatia in aplicatie se face exclusiv din tastatura, odata prin 
tastele obligatorii A, B, C, D in timpul jocului, cat si prin sagetile UP and DOWN, atat in 
meniul principal, cat si in meniul raspunsurilor.

New Game - incepe o sesiune de joc noua si eventual, o termina pe cea deja in desfasurare
Resume Game - daca nu este nicio sesiune de joc in desfasurare, aplicatia va printa pe 
              ecran un mesaj sugestiv, altfel va reveni la jocul curent
Quit - termina orice sesiune de joc si lanseaza procesul de inchidere a aplicatiei
How To Play (bonus) - deschide o fereastra unde sunt printate indicatiile de navigare prin joc
Scoreboard (bonus) - deschide o fereastra unde afiseaza din fisierul leaderboard.txt pe ecran
             numele jucatorilor, precum si scorurile acestora

Iesirea din cele doua ferestre mentionate se face apasand orice tasta.

Odata ce jucatorul a ales sa inceapa o noua sesiune de joc, se afiseaza pe ecran succesiv cele
10 intrebari la care trebuie sa raspunda. Jucatorul poate naviga atat cu sagetile UP si DOWN,
cat si cu tastele A, B, C, D prin raspunsuri. Apasand ENTER, jucatorul confirma alegerea,
scorul pe ecran se updateaza si o noua intrebare este afisata pe ecran. O data pe joc,
optiunile de 50/50 si Skip sunt disponibile pentru jucator. Mesajele pe ecran de tipul:
50/50 PRESS F, SKIP PRESS G, sunt vizibile atunci cand sunt disponibile, iar odata ce jucatorul
a ales cel putin una dintre ele, mesajele vor disparea, iar orice apasare succesiva a tastelor
F sau G nu va realiza nicio actiune.

Apasand Q, jucatorul are optiunea sa se intoarca in ecranul principal, de unde optiunea de Resume Game
este disponibila. Un mesaj sugestiv pe in partea de jos a meniului confirma acest lucru. Apasand Resume,
starea jocului e reconstruita fidel, iar utilizatorul poate sa isi continue aceeasi sesiune de joc.
Apasand New Game, sesiune curenta se termina si se reia o noua runda.

In timpul jocului, apasand R, jucatorul are optiunea de actualiza ora si data curenta.

Dupa ce s-a terminat jocul, utilizatorul parcurgand toate cele 10 intrebari, o ferestrea de scor se
afiseaza pe ecran. Scorul, numarul de intrebari corecte si gresite, cat si un emoticon sugestiv sunt
afisate pe ecran. Apasand orice tasta, se face tranzitia catre ecranul unde jucatorul are posibilitatea
sa isi tasteze numele pentru a fi salvat in Scoreboard. Netastarea niciunui caracter, urmat de apasarea
lui ENTER, face skip si nu salveaza numele in fisierul leaderboard.txt. Un mesaj sugestiv insoteste 
utilizatorul inclusiv la acest pas. 

Apasand ENTER, se termina practic sesiunea de joc, iar din meniul principal se pot relua pasii precedenti.




Intentiile dezvoltatorului:

Am dorit creearea unei aplicatii usor de folosit si care sa ofere pe langa facilitatile cerute, o experienta
de utilizator placuta. Am incercat sa imbogatesc ecranul cu animatii, decoratiuni, mesaje sugestive care sa 
insoteasca utilizatorul la fiecare pas si care sa il coordoneze prin aplicatie. Tranzitiile se fac fara 
intarzieri nedorite, navigatia nu e anevoioasa, iar informatiile despre starea jocului se pastreaza si se 
updateaza permanent intre stari. Majoritatea elementelor vizuale au fost desenate pe ecran relativ fata de 
dimensiunile terminalului, astfel ca elementele reusesc sa se scaleze si sa se adapteze intr-un mod cat 
mai placut vizual. Din punct de vedere personal, pentru ca elementele sa se poate tipari placut si fara prea 
multe spatii pe ecran, se recomanda jucarea la o rezolutie de la 90 X 25 pana la 120 X 35 (numar de coloane X 
numar de linii). Oricum, jocul se poate juca la aproape orice dimensiune. Ca nota tehnica pe care o voi
lamuri mai departe, am dorit sa implementez codul avand in minte urmatoarele principii: scalabilitatea
codului si facilitarea implementarii unor optiuni viitoarea, usurinta de citire si organizarea acestuia
pe 3 headere (utils.h, manager.h, structs.h) si 3 source-file-uri (trivia.c, manager.c, utils.)




Formatul intrebarilor:

Intrebarile sunt descrise in fisierele date drept parametrii executabilului dupa urmatorul format:

<Intrebare>|<Majuscula corespunzatoare raspunsului corect>
A<raspunsul_a>|B<raspunsul_b>|C<raspunsul_c>|D<raspunsul_d>

Programul foloseste strtok cu delimitatorii "|" si "\n" pentru a-si extrage corect informatia din fisiere.
Intrebarile sunt despartite in fisier printr-un rand liber. (A se vedea formatul file1.txt, file2.txt)



Partea tehnica:

Codul este organizat in mai multe fisiere pentru organizare:

trivia.c - sursa de tip main, care odata ce proceseaza intrebarile, lanseaza jocul in executie
utils.c - (header utils.h) contine definitiile functiilor care realizeaza diferite actiuni utilitare
          cum ar fi decorarea ecranului, stergerea unor elemente, procesarea unor informatii, eliberarea
          de memorie, etc. Functiile sunt comentate mai specific in utils.header
manager.c - (header manager.h) contine definitiile functiilor care se ocupa de organizarea si desfasurarea
            starilor jocului: meniul principal, sesiunea de joc, intrebarea, scoreboardul, etc. Practic,
            functiile din utils.h vin intr-ajutorarea acestor functii.

Arhitectura executiei functiilor este urmatoarea:

- se deschid fisierele si se proceseaza intrebarile()
- se deschide Splash Screenul si se inchide()
- se deschide meniul principal cu cele 5 optiuni()
        -> New Game -> functia de sesiune de joc()
                            -> Intrebarea 1
                            <-
                            -> Intrebarea 2
                            <-
                            ....
                            <- pauzarea jocului prin tasta Q
                   <- functia de sesiune de joc()
- meniul principal 
        -> Resume Game -> functia de sesiune de joc()
                             -> Intrebarea X
                             <-
                             ...
                             <- Intrebarea 10
                    - functia de sesiune de joc()
                             -> arata scorul()
                              <-
                    -functia de sesiune de joc()
                        -> salveaza numele in scoreboard
                        <-
                  <- functia de sesiune de joc()
- meniul principal 

Aceasta este in mare executia functiilor pe stiva si avantajul este ca stiva nu se umple de prea 
multe functii la un anumit moment dat. Informatia jocului dintre functii este prezervata prin intermediul
unei structuri de tip GameStat care este pasata ca argument si ca valoare de intoarce intre functii.
Astfel, odata ce s-a dat Q in timpul jocului si s-a revenit in aceasta prin Resume, programul poate
sa reconstruiasca cu fidelitate starea jocului de dinainte de pauzare.

Sistemul de navigatie in timpul jocului este implementat prin doua functii din utils.h:
navigate_answers_with_up_down_keys() si navigate_answers_with_a_b_c_d().

Amestecarea intrbarilor la inceperea unei sesiuni se face printr-o functie ce utilizeaza random:
shuffleQuestions().

