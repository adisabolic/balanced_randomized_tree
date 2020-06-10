#include <iostream>
#include <random>
#include <ctime>
#include "RandomiziranoStablo.h"

using namespace std;

int main(){

    srand(time(0));
    Stablo s1;
    s1.Umetni(1);
    s1.Umetni(3);
    s1.Umetni(4);
    s1.Umetni(6);

    Stablo s2;
    s2.Umetni(2);
    s2.Umetni(5);
    s2.Umetni(7);

    cout<<"Prvo stablo: "<<endl;
    s1.Iscrtaj();
    cout<<"Drugo stablo: "<<endl;
    s2.Iscrtaj();
    cout<<"----------------------------------------------------"<<endl;

    cout<<"Trazi 4 u prvom stablu: "<<endl;
    if(s1.Nadji(4) != nullptr)
        cout<<s1.Nadji(4)->element<<endl;
    else
        cout<<"Nema ga!"<<endl;

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Trazi 4 u drugom stablu: "<<endl;
    if(s2.Nadji(4) != nullptr)
        cout<<s2.Nadji(4)->element<<endl;
    else
        cout<<"Nema ga!"<<endl;

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Brisi 4 iz prvog stabla: "<<endl;
    s1.Izbrisi(4);
    s1.Iscrtaj();

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Umetanje 4 u prvo stablo: "<<endl;
    s1.Umetni(4);
    s1.Iscrtaj();

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Unija: "<<endl;
    Stablo unija(Unija(s2,s1));
    unija.Iscrtaj();

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Razdvajanje unije na manje i vece od 3.5: "<<endl;
    pair<Stablo,Stablo> razdvojeni(unija.Razdvoji(3.5));
    cout<<"Manje: "<<endl;
    razdvojeni.first.Iscrtaj();
    cout<<"Vece: "<<endl;
    razdvojeni.second.Iscrtaj();

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Spajanje prethodna dva razdvojena stabla: "<<endl;
    Stablo spojeni(Spoji(razdvojeni.first,razdvojeni.second));
    spojeni.Iscrtaj();

    cout<<"----------------------------------------------------"<<endl;

    cout<<"Provjera da li je visina stabla log(n): (log2(100000) = 16.6)"<<endl;
    Stablo s;
    for(int i = 0 ; i < 100000 ; i++)
        s.Umetni(rand());
    cout<<"Visina je: "<<s.Visina()<<endl;


    return 0;

}
