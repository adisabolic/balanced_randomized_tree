#ifndef RANDOMIZIRANOS_STABLO_H
#define RANDOMIZIRANOS_STABLO_H

#include <random>
using namespace std;

class Stablo{

public:
    struct Cvor{
        Cvor *lijevoDijete, *desnoDijete, *roditelj;
        double element, prioritet;
        Cvor(double v, double p, Cvor *rod = nullptr, Cvor *ld = nullptr, Cvor *dd = nullptr):element(v),prioritet(p),roditelj(rod),lijevoDijete(ld),desnoDijete(dd){}
    };
private:

    //----------------------- ATRIBUTI ---------------------------------------------------
    Cvor *korijen;

    //----------------------- GLAVNE FUNKCIJE ---------------------------------------------------
    Cvor* Umetni(double,double);
    void desnaRotacija(Cvor*);
    void lijevaRotacija(Cvor*);

    //----------------------- POMOCNE FUNKCIJE ---------------------------------------------------
    Cvor* Najmanji(Cvor* p){if(p->lijevoDijete == nullptr) return p; return Najmanji(p->lijevoDijete);}
    Cvor* Najveci(Cvor* p){if(p->desnoDijete == nullptr) return p; return Najmanji(p->desnoDijete);}
    void Ispisi(Cvor*);
    int Visina(Cvor*);
    int Nivo(Cvor*);
    void Unisti(Cvor*);

public:
    //----------------------- KONSTRUKTORI ---------------------------------------------------
    Stablo() {korijen = nullptr;}
    Stablo(double element) {korijen = new Cvor(element,(double) rand() / RAND_MAX);}
    Stablo(Cvor* p){ korijen = p ; if(korijen != nullptr) korijen->roditelj = nullptr;}
    //Stablo(const Stablo&);
    //~Stablo() {Destroy(korijen);}

    //----------------------- GLAVNE FUNKCIJE ---------------------------------------------------
    Cvor* Nadji(double);
    Cvor* Umetni(double element){return Stablo::Umetni(element, (double) rand() / RAND_MAX);}
    void Izbrisi(double);
    pair<Stablo,Stablo> Razdvoji(double);
    friend Stablo Spoji(Stablo&,Stablo&);
    friend Stablo Unija(Stablo&,Stablo&);

    //----------------------- POMOCNE FUNKCIJE ---------------------------------------------------
    Cvor* Najmanji(){return Najmanji(korijen);}
    Cvor* Najveci(){return Najveci(korijen);}
    void Ispisi(){Ispisi(korijen);}
    int Visina(){return Visina(korijen);}
    void Unisti(){Unisti(korijen);}
    void Iscrtaj();

};



#endif // RANDOMIZIRANOS_STABLO_H
