# Tema 14 ( Tema corespunzatoare din Tema1: 17).  grafuri orientate

Se dau urmatoarele clase:
- Matrice (int **a) – matrice de adiacenta
- Graf (int nr_noduri) – clasa abstracta
- Graf_complet (int nr_muchii) : Graf
- Graf_antisimetric( int nr_muchii) : Graf
- Graf_turneu: Graf_complet, Graf_antisimetric (eventual mostenire virtuala)
Clasa Graf trebuie sa aiba ca metode pur virtuale: parcurgerea in latime, in
adancime, conexitatea(care pentru grafuri orientate va fi implementata ca tare-
conexitate) si altele pe care le considerati utile.
Clasele derivate trebuie sa contina constructori parametrizati prin care sa se evidentieze
transmiterea parametrilor catre constructorul din clasa/clasele de baza, destructori si o
metoda virtuala care sa afiseze arcele unui Graf_antisiemtric, sau a unui Graf Turneu.
Obs: graf turneu – orientat complet si antisimetric. Un graf orientat se numeşte antisimetric dacă pentru
oricare două vârfuri din graf x şi y dacă există arcul (x,y), atunci nu există arcul (y,x). Un graf orientat sau
neorientat se numeşte complet dacă oricare două vârfuri din graf sunt adiacente.
