# CXLibrary

Una libreria C++ progettata per lavorare con numeri complessi.

Attualmente la libreria è composta dalle seguenti classi:
- `cx`: rappresentazione di un numero complesso;
- `cx_vector`: rappresentazione di un vettore di numeri complessi;
- `cx_matrix`: rappresentazione di una matrice di numeri complessi;
- `cx_tensor` :  rappresentazione di un tensore di numeri complessi;

Le classi contengono funzionalità basilari per gestire le operazioni più comuni associate ai numeri complessi e a spazi vettoriali complessi.

È inoltre disponibile la namespace `cx_lib` dove sono definite alcune operazioni generiche (es. prodotto tra matrici o tra matrici e vettori complessi).

***

# Eseguire test

All'interno della cartella del progetto vi è un `Makefile` che permette di compilare ed eseguire i vari file di test situati nella cartella `tests`. I comandi da lanciare sono:
- `make` per compilare i file di test
- `make run-tests` per eseguire i test
- `make clean` per fare pulizia dei binari dei test

**NOTA**: è necessario avere a disposizione la libreria `catch2` per poter eseguire i test.
