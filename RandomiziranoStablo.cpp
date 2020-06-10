#ifndef RANDOMIZIRANOS_STABLO_CPP
#define RANDOMIZIRANOS_STABLO_CPP

#include <iostream>
#include "RandomiziranoStablo.h"
#include <random>
#include <queue>
#include <iomanip>
using namespace std;

//--------------- KONSTRUKTOR KOPIJE (DA BI RADILO SVE AKO IMAM I DESTRUKTOR) ---------------
// Stablo::Stablo(const Stablo &s){
//        korijen = new Cvor(s.korijen->element, s.korijen->prioritet);
//        stack<Cvor*> Stek;
//        Stablo::Cvor *Tekuci = s.korijen;
//        while(1) {
//            while(Tekuci) {
//                Stek.push(Tekuci);
//                Tekuci = Tekuci->lijevoDijete;
//            }
//            if(Stek.empty()) break;
//            Tekuci = Stek.top();
//            Stek.pop();
//            Umetni(Tekuci->element,Tekuci->prioritet);
//            Tekuci = Tekuci->desnoDijete;
//
//        }
//}

//----------------------- GLAVNE FUNKCIJE ---------------------------------------------------

Stablo::Cvor* Stablo::Nadji(double element){
    Stablo::Stablo::Cvor *trenutni = korijen;
    while(trenutni != nullptr){
        if(element == trenutni->element)
            return trenutni;
        else if(element > trenutni->element)
            trenutni = trenutni->desnoDijete;
        else trenutni = trenutni->lijevoDijete;
    }
    return nullptr;
}

void Stablo::desnaRotacija(Stablo::Cvor *p){
    p->roditelj->lijevoDijete = p->desnoDijete;
    p->desnoDijete = p->roditelj;
    p->roditelj = p->desnoDijete->roditelj;
    if(p->roditelj != nullptr){
        if(p->roditelj->element > p->element)
            p->roditelj->lijevoDijete = p;
        else
            p->roditelj->desnoDijete = p;
    }
    p->desnoDijete->roditelj = p;
    if(p->desnoDijete->lijevoDijete != nullptr)
        p->desnoDijete->lijevoDijete->roditelj = p->desnoDijete;
    if(p->roditelj == nullptr)
        korijen = p;
}

void Stablo::lijevaRotacija(Stablo::Cvor *p){
    p->roditelj->desnoDijete = p->lijevoDijete;
    p->lijevoDijete = p->roditelj;
    p->roditelj = p->lijevoDijete->roditelj;
    if(p->roditelj != nullptr){
        if(p->roditelj->element > p->element)
            p->roditelj->lijevoDijete = p;
        else
            p->roditelj->desnoDijete = p;
    }
    p->lijevoDijete->roditelj = p;
    if(p->lijevoDijete->desnoDijete != nullptr)
        p->lijevoDijete->desnoDijete->roditelj = p->lijevoDijete;
    if(p->roditelj == nullptr)
        korijen = p;
}

Stablo::Cvor* Stablo::Umetni(double element, double p){

    Stablo::Cvor *novi(new Stablo::Cvor(element,p));

    if(!korijen){
        korijen = novi;
        return korijen;
    }

    Stablo::Cvor *trenutni(korijen), *prethodni(nullptr);
    while(trenutni != nullptr){
        if(element > trenutni->element){
            prethodni = trenutni;
            trenutni = trenutni->desnoDijete;
        }
        else if(element < trenutni->element){
            prethodni = trenutni;
            trenutni = trenutni->lijevoDijete;
        }
        else return nullptr;
    }

    novi->roditelj = prethodni;
    if(prethodni->element > element)
        prethodni->lijevoDijete = novi;
    else
        prethodni->desnoDijete = novi;

    while(novi->roditelj != nullptr && novi->roditelj->prioritet < novi->prioritet){
        if(novi->roditelj->element > element)
            desnaRotacija(novi);
        else
            lijevaRotacija(novi);
    }

    return novi;
}

void Stablo::Izbrisi(double element){

    Stablo::Cvor *trenutni(Nadji(element));

    if(trenutni == nullptr)
        return;

    Cvor *temp;
    if(trenutni->lijevoDijete == nullptr && trenutni->desnoDijete != nullptr)
        temp = trenutni->desnoDijete;
    else if(trenutni->lijevoDijete != nullptr && trenutni->desnoDijete == nullptr)
        temp = trenutni->lijevoDijete;
    else if(trenutni->lijevoDijete != nullptr){
        temp = Najveci(trenutni->lijevoDijete);
        if(temp->roditelj != trenutni){
            temp->roditelj->desnoDijete = temp->lijevoDijete;
            if(temp->lijevoDijete != nullptr)
                temp->lijevoDijete->roditelj = temp->roditelj;
            trenutni->lijevoDijete->roditelj = temp;
            temp->lijevoDijete = trenutni->lijevoDijete;
        }
        temp->desnoDijete = trenutni->desnoDijete;
        if(trenutni->desnoDijete != nullptr)
            trenutni->desnoDijete->roditelj = temp;
    }
    else{
        if(trenutni->element < trenutni->roditelj->element)
            trenutni->roditelj->lijevoDijete = nullptr;
        else
            trenutni->roditelj->desnoDijete = nullptr;

        delete trenutni;
        return;
    }

    temp->roditelj = trenutni->roditelj;
    temp->prioritet = trenutni->prioritet;
    if(trenutni != korijen){
        if(temp->element > trenutni->roditelj->element)
            trenutni->roditelj->desnoDijete = temp;
        else
            trenutni->roditelj->lijevoDijete = temp;
    }
    if(trenutni == korijen)
            korijen = temp;
    delete trenutni;
}

pair<Stablo,Stablo> Stablo::Razdvoji(double k){
    Umetni(k,1.1);
    Stablo s1(korijen->lijevoDijete),s2(korijen->desnoDijete);
    return {s1,s2};
}

Stablo Spoji(Stablo &s1,Stablo &s2){
    Stablo::Cvor *temp(new Stablo::Cvor((s1.Najveci()->element + s2.Najmanji()->element)/2, -1));
    Stablo s(temp);
    s.korijen->lijevoDijete = s1.korijen;
    s.korijen->desnoDijete = s2.korijen;
    s.korijen->lijevoDijete->roditelj = s.korijen;
    s.korijen->desnoDijete->roditelj = s.korijen;

    Stablo::Cvor* trenutni = s.korijen;
    while(trenutni->lijevoDijete != nullptr || trenutni->desnoDijete != nullptr){

        if(trenutni->lijevoDijete == nullptr)
            s.lijevaRotacija(trenutni->desnoDijete);
        else if(trenutni->desnoDijete == nullptr)
            s.desnaRotacija(trenutni->lijevoDijete);
        else{
            if(trenutni->lijevoDijete->prioritet > trenutni->desnoDijete->prioritet)
                s.desnaRotacija(trenutni->lijevoDijete);
            else
                s.lijevaRotacija(trenutni->desnoDijete);
        }
    }
    s.Izbrisi(trenutni->element);
    return s;
}

Stablo Unija(Stablo &s1,Stablo &s2){
    if(s1.korijen == nullptr)
        return s2;
    if(s2.korijen == nullptr)
        return s1;
    if(s1.korijen->prioritet < s2.korijen->prioritet)
        swap(s1.korijen,s2.korijen);

    Stablo rezultat(s1.korijen);
    pair<Stablo,Stablo> r(s2.Razdvoji(s1.korijen->element));
    Stablo temp1(s1.korijen->lijevoDijete), temp2(s1.korijen->desnoDijete);

    Stablo r1(Unija(temp1,r.first));
    Stablo r2(Unija(temp2,r.second));

    rezultat.korijen->lijevoDijete = r1.korijen;
    if(rezultat.korijen->lijevoDijete != nullptr)
        rezultat.korijen->lijevoDijete->roditelj = rezultat.korijen;
    rezultat.korijen->desnoDijete = r2.korijen;
    if(rezultat.korijen->desnoDijete != nullptr)
        rezultat.korijen->desnoDijete->roditelj = rezultat.korijen;

    return rezultat;
}


//----------------------- POMOCNE FUNKCIJE ---------------------------------------------------

int Stablo::Nivo(Stablo::Stablo::Cvor* trenutni){
    if(trenutni == korijen)
        return 0;
    return Nivo(trenutni->roditelj)+1;
}

int Stablo::Visina(Stablo::Stablo::Cvor* trenutni){
    if(trenutni == nullptr)
        return -1;
    return 1 + max(Visina(trenutni->lijevoDijete), Visina(trenutni->desnoDijete));
}

void Stablo::Unisti(Stablo::Cvor *p){
    if(p == nullptr)
        return;
    Unisti(p->lijevoDijete);
    Unisti(p->desnoDijete);
    delete p;
    p = nullptr;
}

void Stablo::Ispisi(Stablo::Cvor *p){
    if(p == nullptr)
        return;
    Ispisi(p->lijevoDijete);
    if(p != korijen){
        if(p->lijevoDijete == nullptr && p->desnoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: NEMA"<<"|| Desno: NEMA"<<"|| Roditelj: "<<p->roditelj->element<<endl;
        else if(p->desnoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: "<<p->lijevoDijete->element<<"|| Desno: NEMA"<<"|| Roditelj: "<<p->roditelj->element<<endl;
        else if(p->lijevoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: NEMA"<<"|| Desno: "<<p->desnoDijete->element<<"|| Roditelj: "<<p->roditelj->element<<endl;
        else
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: "<<p->lijevoDijete->element<<"|| Desno: "<<p->desnoDijete->element<<"|| Roditelj: "<<p->roditelj->element<<endl;
    }
    else{
        if(p->lijevoDijete == nullptr && p->desnoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: NEMA"<<"|| Desno: NEMA"<<"|| Roditelj: NEMA"<<endl;
        else if(p->desnoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: "<<p->lijevoDijete->element<<"|| Desno: NEMA"<<"|| Roditelj: NEMA"<<endl;
        else if(p->lijevoDijete == nullptr)
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: NEMA"<<"|| Desno: "<<p->desnoDijete->element<<"|| Roditelj: NEMA"<<endl;
        else
            cout<<"Element: "<<p->element<<"|| Prioritet: "<<p->prioritet<<"|| Lijevo: "<<p->lijevoDijete->element<<"|| Desno: "<<p->desnoDijete->element<<"|| Roditelj: NEMA"<<endl;
    }
    Ispisi(p->desnoDijete);
}

void Stablo::Iscrtaj(){
    if(korijen == nullptr)
        return;
    queue<Stablo::Cvor*> red;
    red.push(korijen);
    int broj_Cvorova = 1;
    int stari_nivo = 1;
    int novi_nivo = 1;
    Stablo::Cvor* trenutni;
    while(broj_Cvorova > 0){
        trenutni = red.front();
        red.pop();
        if(trenutni!=nullptr){
            broj_Cvorova--;
            cout<<"("<<setw(2)<<trenutni->prioritet<<","<<setw(2)<<trenutni->element<<")";
            red.push(trenutni->lijevoDijete);
            red.push(trenutni->desnoDijete);
            if(trenutni->lijevoDijete != nullptr) broj_Cvorova++;
            if(trenutni->desnoDijete != nullptr) broj_Cvorova++;
        }
        else{
            cout<<"(               )";
            red.push(nullptr);
            red.push(nullptr);
        }
        novi_nivo++;
        if(novi_nivo >= 2*stari_nivo){
            cout<<endl;
            stari_nivo = novi_nivo;
        }
    }
    cout<<endl;
    cout<<endl;
}

#endif // RANDOMIZIRANOS_STABLO_CPP
