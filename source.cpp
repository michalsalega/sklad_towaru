//Michał Sałęga
#include <iostream>
using namespace std;


struct Place{
    unsigned short inStock;
    char etykieta[2];

    Place(){
        inStock = 0;
        etykieta[0] = 0;
        etykieta[1] = 0;
    }

    unsigned short addStock(unsigned short A){
        if((A + inStock) >= 65535){
            unsigned short tmp = 65535 - inStock;
            inStock = 65535;
            return tmp;
        }else{
            inStock += A;
            return A;
        }
    }

    unsigned short substractStock(unsigned short A){
        if((inStock - A) <= 0){
            unsigned short tmp = inStock;
            inStock = 0;
            return tmp;
        }else{
            inStock -= A;
            return A;
        }
    }


};

struct Shelf{
    Place places[128];
    unsigned short counter;
    unsigned inStock;

    Shelf(){
        counter = 0;
        inStock = 0;
        //createPlaces(0);
    }

    unsigned addAll(){
        unsigned sum = 0;
        for(int i = 0; i < counter; i++){
            sum += places[i].inStock;
        }
        return sum;
    }

    void createPlaces(unsigned short p){
        if(p > counter){
            for(int i = counter; i < p; i++){
                places[i].inStock = 0;
                places[i].etykieta[0] = 0;
                places[i].etykieta[1] = 0;
            }
        }else if(p < counter){ // MOZLIWE ZE NIE POTRZEBNE
            for(int i = p; i < counter; i++){
                places[i].inStock = 0;
                places[i].etykieta[0] = 0;
                places[i].etykieta[1] = 0;
            }
        }
        counter = p;
    }
};

struct Rack{
    Shelf shelves[128];
    unsigned short counter;

    Rack(){
        counter = 0;
        //createShelves(0, 0);
    }

    void createShelves(unsigned short s, unsigned short p){
        if(s > counter){
            for(unsigned short i = 0; i < s; i++){
                shelves[i].createPlaces(p);
            }
        }else if(s < counter){
            for(unsigned short i = 0; i < s; i++){
                shelves[i].createPlaces(p);
            }

            for(unsigned short i = s; i < counter; i++){
                shelves[i].createPlaces(0);
                shelves[i].inStock = 0;
            }
        }
        counter = s;
    }

};

struct Warehouse{
    Rack racks[128];
    unsigned short counter;
    Shelf handyShelf;

    Warehouse(){
        counter = 0;
        //createRacks(0, 0, 0);
    }

    void createRacks(unsigned short r, unsigned short s, unsigned short p){
        if(r > counter){
            for(unsigned short i = 0; i < r; i++){
                racks[i].createShelves(s, p);
            }

        }else if(r < counter){
            for(unsigned short i = 0; i < r; i++){
                racks[i].createShelves(s, p);
            }

            for(unsigned short i = r; i < counter; i++){
                racks[i].createShelves(0,0);
//                racks[i].counter = 0;
            }
        }
        counter = r;
    }

    void createHandyShelf(unsigned short p){
        handyShelf.createPlaces(p);
    }

};

struct Sklad{
    Warehouse warehouses[128];
    unsigned short counter;
    Rack handyRack;
    Shelf handyShelf;

    Sklad(){
        counter = 0;
    }


    void createWarehouses(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
        if(w > counter){
            for(unsigned short i = 0; i < w; i++){
                warehouses[i].createRacks(r, s, p);
            }
        }else if(w < counter){
            for(unsigned short i = 0; i < w; i++){
                warehouses[i].createRacks(r, s, p);
            }
            for(int i = w; i < counter; i++){
                warehouses[i].handyShelf.createPlaces(0);
                warehouses[i].createRacks(0,0,0);
//                warehouses[i].counter = 0;
            }
        }

        counter = w;
    }

    //--------------------------------SET--------------------------------------------------------------------

    void setap(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p > 128) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].racks[r].shelves[s].createPlaces(p);
            warehouses[w].racks[r].shelves[s].inStock = warehouses[w].racks[r].shelves[s].addAll();
        }
    }

    void setas(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
        if((w >= counter) || (r >= warehouses[w].counter) || (s > 128) || (p > 128) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].racks[r].createShelves(s, p);
        }
    }

    void setar(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
        if((w >= counter) || (r > 128) || (s > 128) || (p > 128) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].createRacks(r, s, p);
        }
    }

    void setaw(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
        if((w > 128) || (r > 128) || (s > 128) || (p > 128) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            createWarehouses(w, r, s, p);

        }
    }

    void sethw(unsigned short w, unsigned short p){
        if((w >= counter) || (p > 128) || (w < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].handyShelf.createPlaces(p);
        }
    }

    void sethr(unsigned short s, unsigned short p){
        if((s > 128) || (p > 128) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            handyRack.createShelves(s, p);
        }
    }

    void seths(unsigned short p){
        if((p > 128) || (p < 0)){
            cout << "error" << endl;
        }else{
            handyShelf.createPlaces(p);
            handyShelf.inStock = handyShelf.addAll();
        }
    }

    // --------------------------------------PUT--------------------------------------------------------------

    void putw(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned A){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p >= warehouses[w].racks[r].shelves[s].counter) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = warehouses[w].racks[r].shelves[s].places[p].addStock(A);
            warehouses[w].racks[r].shelves[s].inStock += tmp;
        }
    }

    void puth(unsigned short w, unsigned short p, unsigned A){
        if((w >= counter) || (p >= warehouses[w].handyShelf.counter) || (w < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = warehouses[w].handyShelf.places[p].addStock(A);
            warehouses[w].handyShelf.inStock += tmp;
        }
    }

    void putr(unsigned short s, unsigned short p, unsigned A){
        if((s >= handyRack.counter) || (p >= handyRack.shelves[s].counter) || (p < 0) || (s < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = handyRack.shelves[s].places[p].addStock(A);
            handyRack.shelves[s].inStock += tmp;
        }
    }

    void puts(unsigned short p, unsigned A){
        if((p >= handyShelf.counter) || (p < 0) || (A > 65535)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = handyShelf.places[p].addStock(A);
            handyShelf.inStock += tmp;
        }
    }

    //--------------------------------------FILL---------------------------------------------

    void clearWarehousesHandyShelves(){
        for(int i = 0; i < counter; i++){
            for(int j = 0; j < warehouses[i].handyShelf.counter; j++){
                warehouses[i].handyShelf.places[j].inStock = 0;
                warehouses[i].handyShelf.places[j].etykieta[0] = 0;
                warehouses[i].handyShelf.places[j].etykieta[1] = 0;
            }
            warehouses[i].handyShelf.inStock = 0;
        }
    }

    void addStockEverywhere(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned A){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < r; j++){
                for(int k = 0; k < s; k++){
                    warehouses[i].racks[j].shelves[k].inStock = A * warehouses[i].racks[j].shelves[k].counter;
                    for(int m = 0; m < p; m++){
                        warehouses[i].racks[j].shelves[k].places[m].inStock = A;

//                        putw(i,j,k,m,A);
                    }
                }
            }
        }
    }

    void createWarehousesHandyShelvesWithAddition(unsigned short p, unsigned A){
        for(int i = 0; i < counter; i++){
            warehouses[i].createHandyShelf(p);
            warehouses[i].handyShelf.inStock = A * warehouses[i].handyShelf.counter;
            for(int j = 0; j < p; j++){
                warehouses[i].handyShelf.places[j].inStock = A;
            }
        }
    }

    void fill(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned A){
        if((w > 128) || (r > 128) || (s > 128) || (p > 128) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{

            //------------------**********************************************
            for(int i = 0; i < counter; i++){
                for(int j = 0; j < warehouses[i].counter; j++){
                    for(int k = 0; k < warehouses[i].racks[j].counter; k++){
                        for(int m = 0; m < warehouses[i].racks[j].shelves[k].counter; m++){
                            warehouses[i].racks[j].shelves[k].places[m].inStock = 0;
                            warehouses[i].racks[j].shelves[k].places[m].etykieta[0] = 0;
                            warehouses[i].racks[j].shelves[k].places[m].etykieta[1] = 0;
                        }
                        warehouses[i].racks[j].shelves[k].counter = 0;
                        warehouses[i].racks[j].shelves[k].inStock = 0;
                    }
                    warehouses[i].racks[j].counter = 0;
                }
                warehouses[i].counter = 0;
            }

            counter = 0;
            clearWarehousesHandyShelves();

            for(int i = 0; i < handyShelf.counter; i++){
                handyShelf.places[i].inStock = 0;
                handyShelf.places[i].etykieta[0] = 0;
                handyShelf.places[i].etykieta[1] = 0;
            }
            handyShelf.inStock = 0;
            handyShelf.counter = 0;

            for(int i = 0; i < handyRack.counter; i++){
                for(int j = 0; j < handyRack.shelves[i].counter; j++){
                    handyRack.shelves[i].places[j].inStock = 0;
                    handyRack.shelves[i].places[j].etykieta[0] = 0;
                    handyRack.shelves[i].places[j].etykieta[1] = 0;
                }
                handyRack.shelves[i].counter = 0;
                handyRack.shelves[i].inStock = 0;
            }

            handyRack.counter = 0;

            setaw(w,r,s,p);
            handyRack.createShelves(s, p);
            for(int i = 0; i < s; i++){
                handyRack.shelves[i].inStock = A * handyRack.shelves[i].counter;
                for(int j = 0; j < p; j++){
                    handyRack.shelves[i].places[j].addStock(A);
                }
            }
            handyShelf.createPlaces(p);
            handyShelf.inStock = A * handyShelf.counter;

            for(int i = 0; i < p; i++){
                handyShelf.places[i].addStock(A);
            }

            createWarehousesHandyShelvesWithAddition(p, A);

            addStockEverywhere(w,r,s,p,A);
        }
    }

    // ------------------------------------------DELETE-----------------------------------------------

    void popw(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned A){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p >= warehouses[w].racks[r].shelves[s].counter) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = warehouses[w].racks[r].shelves[s].places[p].substractStock(A);
            warehouses[w].racks[r].shelves[s].inStock -= tmp;
        }
    }

    void poph(unsigned short w, unsigned short p, unsigned A){
        if((w >= counter) || (p >= warehouses[w].handyShelf.counter) || (w < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = warehouses[w].handyShelf.places[p].substractStock(A);
            warehouses[w].handyShelf.inStock -= tmp;
        }
    }

    void popr(unsigned short s, unsigned short p, unsigned A){
        if((s >= handyRack.counter) || (p >= handyRack.shelves[s].counter) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = handyRack.shelves[s].places[p].substractStock(A);
            handyRack.shelves[s].inStock -= tmp;
        }
    }

    void pops(unsigned short p, unsigned A){
        if((p >= handyShelf.counter) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short tmp = handyShelf.places[p].substractStock(A);
            handyShelf.inStock -= tmp;
        }
    }

    //----------------------------------MOVE----------------------------------------------------

    void movw(unsigned short wb, unsigned short rb, unsigned short sb, unsigned short we, unsigned short re, unsigned short se,
              unsigned short p, unsigned A){
        if((wb >= counter) || (we >= counter) || (rb >= warehouses[wb].counter) || (re >= warehouses[we].counter) ||
        (sb >= warehouses[wb].racks[rb].counter) || (se >= warehouses[we].racks[re].counter) ||
                (p >= warehouses[we].racks[re].shelves[se].counter) || (p >= warehouses[wb].racks[rb].shelves[sb].counter)
                || (wb < 0) || (we < 0) || (rb < 0) || (re < 0) || (sb < 0) || (se < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short valueB = warehouses[wb].racks[rb].shelves[sb].places[p].inStock;
            unsigned short valueE = warehouses[we].racks[re].shelves[se].places[p].inStock;
            unsigned leftE = 65535 - valueE;

            Place* tmpPlaceB = &(warehouses[wb].racks[rb].shelves[sb].places[p]);
            Place* tmpPlaceE = &(warehouses[we].racks[re].shelves[se].places[p]);

            if(valueB >= A){
                if((valueE + A) <= 65535){

                    warehouses[wb].racks[rb].shelves[sb].inStock -= tmpPlaceB->substractStock(A);
                    warehouses[we].racks[re].shelves[se].inStock += tmpPlaceE->addStock(A);
                }else{

                    warehouses[wb].racks[rb].shelves[sb].inStock -= tmpPlaceB->substractStock(leftE);
                    warehouses[we].racks[re].shelves[se].inStock += tmpPlaceE->addStock(leftE);
                }
            }else{
                if((valueE + A) <= 65535){

                    warehouses[wb].racks[rb].shelves[sb].inStock -= tmpPlaceB->substractStock(valueB);
                    warehouses[we].racks[re].shelves[se].inStock += tmpPlaceE->addStock(valueB);
                }else{
                    if(valueB >= (leftE)){
                        warehouses[wb].racks[rb].shelves[sb].inStock -= tmpPlaceB->substractStock(leftE);
                        warehouses[we].racks[re].shelves[se].inStock += tmpPlaceE->addStock(leftE);
                    }else{

                        warehouses[wb].racks[rb].shelves[sb].inStock -= tmpPlaceB->substractStock(valueB);
                        warehouses[we].racks[re].shelves[se].inStock += tmpPlaceE->addStock(valueB);
                    }
                }
            }
        }
    }

    void movh(unsigned short w, unsigned short r, unsigned short s, unsigned short p, unsigned A){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p >= warehouses[w].racks[r].shelves[s].counter) ||
                (p >= warehouses[w].handyShelf.counter) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short valueB = warehouses[w].racks[r].shelves[s].places[p].inStock;
            unsigned short valueE = warehouses[w].handyShelf.places[p].inStock;
            unsigned leftE = 65535 - valueE;

            Place* tmpPlaceB = &(warehouses[w].racks[r].shelves[s].places[p]);
            Place* tmpPlaceE = &(warehouses[w].handyShelf.places[p]);

            if(valueB >= A){
                if((valueE + A) <= 65535){

                    warehouses[w].racks[r].shelves[s].inStock -= tmpPlaceB->substractStock(A);
                    warehouses[w].handyShelf.inStock += tmpPlaceE->addStock(A);
                }else{

                    warehouses[w].racks[r].shelves[s].inStock -= tmpPlaceB->substractStock(leftE);
                    warehouses[w].handyShelf.inStock += tmpPlaceE->addStock(leftE);
                }
            }else{
                if((valueE + A) <= 65535){

                    warehouses[w].racks[r].shelves[s].inStock -= tmpPlaceB->substractStock(valueB);
                    warehouses[w].handyShelf.inStock += tmpPlaceE->addStock(valueB);
                }else{
                    if(valueB >= (leftE)){
                        warehouses[w].racks[r].shelves[s].inStock -= tmpPlaceB->substractStock(leftE);
                        warehouses[w].handyShelf.inStock += tmpPlaceE->addStock(leftE);
                    }else{

                        warehouses[w].racks[r].shelves[s].inStock -= tmpPlaceB->substractStock(valueB);
                        warehouses[w].handyShelf.inStock += tmpPlaceE->addStock(valueB);
                    }
                }
            }
        }
    }

    void movr(unsigned short w, unsigned short r, unsigned short sb, unsigned short se, unsigned short p, unsigned A){

        if((w >= counter) || (r >= warehouses[w].counter) || (sb >= warehouses[w].racks[r].counter) || (se >= handyRack.counter) || (p >= warehouses[w].racks[r].shelves[sb].counter) ||
                (p >= handyRack.shelves[se].counter) || (w < 0) || (r < 0) || (sb < 0) || (se < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short valueB = warehouses[w].racks[r].shelves[sb].places[p].inStock;
            unsigned short valueE = handyRack.shelves[se].places[p].inStock;
            unsigned leftE = 65535 - valueE;

            Place* tmpPlaceB = &(warehouses[w].racks[r].shelves[sb].places[p]);
            Place* tmpPlaceE = &(handyRack.shelves[se].places[p]);

            if(valueB >= A){
                if((valueE + A) <= 65535){

                    warehouses[w].racks[r].shelves[sb].inStock -= tmpPlaceB->substractStock(A);
                    handyRack.shelves[se].inStock += tmpPlaceE->addStock(A);
                }else{

                    warehouses[w].racks[r].shelves[sb].inStock -= tmpPlaceB->substractStock(leftE);
                    handyRack.shelves[se].inStock += tmpPlaceE->addStock(leftE);
                }
            }else{
                if((valueE + A) <= 65535){

                    warehouses[w].racks[r].shelves[sb].inStock -= tmpPlaceB->substractStock(valueB);
                    handyRack.shelves[se].inStock += tmpPlaceE->addStock(valueB);
                }else{
                    if(valueB >= (leftE)){
                        warehouses[w].racks[r].shelves[sb].inStock -= tmpPlaceB->substractStock(leftE);
                        handyRack.shelves[se].inStock += tmpPlaceE->addStock(leftE);
                    }else{

                        warehouses[w].racks[r].shelves[sb].inStock -= tmpPlaceB->substractStock(valueB);
                        handyRack.shelves[se].inStock += tmpPlaceE->addStock(valueB);
                    }
                }
            }
        }

    }

    void movs(unsigned short s, unsigned short p, unsigned A){
        if((s >= handyRack.counter) || (p >= handyRack.shelves[s].counter) || (p >= handyShelf.counter) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            unsigned short valueB = handyRack.shelves[s].places[p].inStock;
            unsigned short valueE = handyShelf.places[p].inStock;
            unsigned leftE = 65535 - valueE;

            Place* tmpPlaceB = &(handyRack.shelves[s].places[p]);
            Place* tmpPlaceE = &(handyShelf.places[p]);

            if(valueB >= A){
                if((valueE + A) <= 65535){

                    handyRack.shelves[s].inStock -= tmpPlaceB->substractStock(A);
                    handyShelf.inStock += tmpPlaceE->addStock(A);
                }else{

                    handyRack.shelves[s].inStock -= tmpPlaceB->substractStock(leftE);
                    handyShelf.inStock += tmpPlaceE->addStock(leftE);
                }
            }else{
                if((valueE + A) <= 65535){

                    handyRack.shelves[s].inStock -= tmpPlaceB->substractStock(valueB);
                    handyShelf.inStock += tmpPlaceE->addStock(valueB);
                }else{
                    if(valueB >= (leftE)){
                        handyRack.shelves[s].inStock -= tmpPlaceB->substractStock(leftE);
                        handyShelf.inStock += tmpPlaceE->addStock(leftE);
                    }else{

                        handyRack.shelves[s].inStock -= tmpPlaceB->substractStock(valueB);
                        handyShelf.inStock += tmpPlaceE->addStock(valueB);
                    }
                }
            }
        }
    }
    //--------------------------GETS-------------------------

    void gete(){
        long long sum = 0;

        for(short i = 0; i < counter; i++){
            Warehouse* tmpWarehouse = &(warehouses[i]);
            for(short j = 0; j < tmpWarehouse->counter; j++){
                Rack* tmpRack = &(tmpWarehouse->racks[j]);
                for(short k = 0; k < tmpRack->counter; k++){
//                    Shelf* tmpShelf = &(tmpRack->shelves[k]);
                    sum += tmpRack->shelves[k].inStock;

//                    for(short m = 0; m < tmpShelf->counter; m++){
//                        sum += tmpShelf->places[m].inStock;
////                        sum += warehouses[i].racks[j].shelves[k].places[m].inStock;
//                    }
                }
            }
        }

        for(int i = 0; i < counter; i++){
//            sum += warehouses[i].handyShelf.inStock;
            for(int j = 0; j < warehouses[i].handyShelf.counter; j++){
                sum += warehouses[i].handyShelf.places[j].inStock;
            }
        }

        for(int i = 0; i < handyRack.counter; i++){
//            sum += handyRack.shelves[i].inStock;
            for(int j = 0; j < handyRack.shelves[i].counter; j++){
                sum += handyRack.shelves[i].places[j].inStock;
            }
        }

        sum += handyShelf.inStock;
//        for(int i = 0; i < handyShelf.counter; i++){
//            sum += handyShelf.places[i].inStock;
//        }

        cout << sum << endl;
    }

    void getw(unsigned short w){
        if((w >= counter) || (w < 0)){
            cout << "error" << endl;
        }else{
            long long sum = 0;
            for(int j = 0; j < warehouses[w].counter; j++){
                for(int k = 0; k < warehouses[w].racks[j].counter; k++){
                   // sum += warehouses[w].racks[j].shelves[k].inStock;
                    for(int m = 0; m < warehouses[w].racks[j].shelves[k].counter; m++){
                        sum += warehouses[w].racks[j].shelves[k].places[m].inStock;
                    }
                }
            }

            for(int i = 0; i < warehouses[w].handyShelf.counter; i++){
                sum += warehouses[w].handyShelf.places[i].inStock;
            }
//            sum += warehouses[w].handyShelf.inStock;

            cout << sum << endl;
        }
    }

    void getrw(unsigned short w, unsigned short r){
        long long sum = 0;
        if((w >= counter) || (r >= warehouses[w].counter) || (w < 0) || (r < 0)){
            cout << "error" << endl;
        }else{
            for(int k = 0; k < warehouses[w].racks[r].counter; k++){
                for(int m = 0; m < warehouses[w].racks[r].shelves[k].counter; m++){
                    sum += warehouses[w].racks[r].shelves[k].places[m].inStock;
                }
            }
            cout << sum << endl;
        }
    }

    void getrh(){
        long long sum = 0;
        for(int i = 0; i < handyRack.counter; i++){
            for(int j = 0; j < handyRack.shelves[i].counter; j++){
                sum += handyRack.shelves[i].places[j].inStock;
            }
        }
        cout << sum << endl;
    }

    void getsw(unsigned short w, unsigned short r, unsigned short s){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (w < 0) || (r < 0) || (s < 0)){
            cout << "error" << endl;
        }else{
            long long sum = 0;
            for(int i = 0; i < warehouses[w].racks[r].shelves[s].counter; i++){
                sum += warehouses[w].racks[r].shelves[s].places[i].inStock;
            }
            cout << sum << endl;
        }
    }

    void getsh(unsigned short w){
        long long sum = 0;
        if((w >= counter) || (w < 0)){
            cout << "error" << endl;
        }else{
            for(int i = 0; i < warehouses[w].handyShelf.counter; i++){
                sum += warehouses[w].handyShelf.places[i].inStock;
            }
            cout << sum << endl;
        }

    }

    void getsr(unsigned short s){
        if((s >= handyRack.counter) || (s < 0)){
            cout << "error" << endl;
        }else{
            long long sum = 0;
            for(int i = 0; i < handyRack.shelves[s].counter; i++){
                sum += handyRack.shelves[s].places[i].inStock;
            }
//            sum += handyRack.shelves[s].inStock;
            cout << sum << endl;
        }
    }

    void gets(){
        long long sum = 0;
        for(int i = 0; i < handyShelf.counter; i++){
            sum += handyShelf.places[i].inStock;
        }
        cout << sum << endl;
    }

    //*********************************************************************************************************************

     void setlw(unsigned short w, unsigned short r, unsigned short s, unsigned short p, char label[2]){
        if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p >= warehouses[w].racks[r].shelves[s].counter) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].racks[r].shelves[s].places[p].etykieta[0] = label[0];
            warehouses[w].racks[r].shelves[s].places[p].etykieta[1] = label[1];
        }
    }

    void setlh(unsigned short w, unsigned short p, char label[2]){
        if((w >= counter) || (p >= warehouses[w].handyShelf.counter) || (p < 0) || (w < 0)){
            cout << "error" << endl;
        }else{
            warehouses[w].handyShelf.places[p].etykieta[0] = label[0];
            warehouses[w].handyShelf.places[p].etykieta[1] = label[1];
        }
     }

     void setlr(unsigned short s, unsigned short p, char label[2]){
         if((s >= handyRack.counter) || (p >= handyRack.shelves[s].counter) || (s < 0) || (p < 0)){
             cout << "error" << endl;
         }else{
             handyRack.shelves[s].places[p].etykieta[0] = label[0];
             handyRack.shelves[s].places[p].etykieta[1] = label[1];
         }
     }

     void setls(unsigned short p, char label[2]){
         if((p >= handyShelf.counter) || (p < 0)){
             cout << "error" << endl;
         }else{
             handyShelf.places[p].etykieta[0] = label[0];
             handyShelf.places[p].etykieta[1] = label[1];
         }
     }


     void getlw(unsigned short w, unsigned short r, unsigned short s, unsigned short p){
         if((w >= counter) || (r >= warehouses[w].counter) || (s >= warehouses[w].racks[r].counter) || (p >= warehouses[w].racks[r].shelves[s].counter) || (w < 0) || (r < 0) || (s < 0) || (p < 0)){
             cout << "error" << endl;
         }else{
             if((warehouses[w].racks[r].shelves[s].places[p].etykieta[0] == 0) && (warehouses[w].racks[r].shelves[s].places[p].etykieta[0] == 0)){
                 cout << "--" << endl;
             }else{
                 cout << warehouses[w].racks[r].shelves[s].places[p].etykieta << endl;
             }
         }
     }

     void getlh(unsigned short w, unsigned short p){
         if((w >= counter) || (p >= warehouses[w].handyShelf.counter) || (w < 0) || (p < 0)){
             cout << "error" << endl;
         }else{
             if((warehouses[w].handyShelf.places[p].etykieta[0] == 0) && (warehouses[w].handyShelf.places[p].etykieta[0] == 0)){
                 cout << "--" << endl;
             }else{
                 cout << warehouses[w].handyShelf.places[p].etykieta << endl;
             }
         }
     }

     void getlr(unsigned short s, unsigned short p){
         if((s >= handyRack.counter) || (p >= handyRack.shelves[s].counter) || (s < 0) || (p < 0)){
             cout << "error" << endl;
         }else{
             if((handyRack.shelves[s].places[p].etykieta[0] == 0) && (handyRack.shelves[s].places[p].etykieta[0] == 0)){
                 cout << "--" << endl;
             }else{
                 cout << handyRack.shelves[s].places[p].etykieta << endl;
             }
         }
     }

     void getls(unsigned short p){
         if((p >= handyShelf.counter) || (p < 0)){
             cout << "error" << endl;
         }else{
             if((handyShelf.places[p].etykieta[0] == 0) && (handyShelf.places[p].etykieta[0] == 0)){
                 cout << "--" << endl;
             }else{
                 cout << handyShelf.places[p].etykieta << endl;
             }
         }
     }
};

int main() {
    static Sklad sklad;
    unsigned short w,r,s,p;
    unsigned short we,re,se,wb,rb,sb;
    unsigned A;
    char label[2];

    std::string kodOperacji = "";

//    sklad.fill(120,120,120,120,65535);
//    cout << sklad.counter << endl;

    while(kodOperacji != "END"){
        cin >> kodOperacji;
        if(kodOperacji == "SET-AP"){
            cin >> w >> r >> s >> p;
            sklad.setap(w,r,s,p);
        }

        else if(kodOperacji == "SET-AS"){
            cin >> w >> r >> s >> p;
            sklad.setas(w,r,s,p);
        }

        else if(kodOperacji == "SET-AR"){
            cin >> w >> r >> s >> p;
            sklad.setar(w,r,s,p);
        }

        else if(kodOperacji == "SET-AW"){
            cin >> w >> r >> s >> p;
            sklad.setaw(w,r,s,p);
        }

        else if(kodOperacji == "SET-HW"){
            cin >> w >> p;
            sklad.sethw(w,p);
        }

        else if(kodOperacji == "SET-HR"){
            cin >> s >> p;
            sklad.sethr(s,p);
        }

        else if(kodOperacji == "SET-HS"){
            cin >> p;
            sklad.seths(p);
        }

        else if(kodOperacji == "PUT-W"){
            cin >> w >> r >> s >> p >> A;
            sklad.putw(w,r,s,p,A);
        }

        else if(kodOperacji == "PUT-H"){
            cin >> w >> p >> A;
            sklad.puth(w,p,A);
        }

        else if(kodOperacji == "PUT-R"){
            cin >> s >> p >> A;
            sklad.putr(s,p,A);
        }

        else if(kodOperacji == "PUT-S"){
            cin >> p >> A;
            sklad.puts(p,A);
        }

        else if(kodOperacji == "FILL"){
            cin >> w >> r >> s >> p >> A;
            sklad.fill(w,r,s,p,A);
        }

        else if(kodOperacji == "POP-W"){
            cin >> w >> r >> s >> p >> A;
            sklad.popw(w,r,s,p,A);
        }

        else if(kodOperacji == "POP-H"){
            cin >> w >> p >> A;
            sklad.poph(w,p,A);
        }

        else if(kodOperacji == "POP-R"){
            cin >> s >> p >> A;
            sklad.popr(s,p,A);
        }

        else if(kodOperacji == "POP-S"){
            cin >> p >> A;
            sklad.pops(p,A);
        }

        else if(kodOperacji == "MOV-W"){
            cin >> wb >> rb >> sb >> we >> re >> se >> p >> A;
            sklad.movw(wb,rb,sb,we,re,se,p,A);
        }

        else if(kodOperacji == "MOV-H"){
            cin >> w >> r >> s >> p >> A;
            sklad.movh(w,r,s,p,A);
        }

        else if(kodOperacji == "MOV-R"){
            cin >> w >> r >> sb >> se >> p >> A;
            sklad.movr(w,r,sb,se,p,A);
        }

        else if(kodOperacji == "MOV-S"){
            cin >> s >> p >> A;
            sklad.movs(s,p,A);
        }

        else if(kodOperacji == "GET-E"){
            sklad.gete();
        }

        else if(kodOperacji == "GET-W"){
            cin >> w;
            sklad.getw(w);
        }

        else if(kodOperacji == "GET-RW"){
            cin >> w >> r;
            sklad.getrw(w,r);
        }

        else if(kodOperacji == "GET-RH"){
            sklad.getrh();
        }

        else if(kodOperacji == "GET-SW"){
            cin >> w >> r >> s;
            sklad.getsw(w,r,s);
        }

        else if(kodOperacji == "GET-SH"){
            cin >> w;
            sklad.getsh(w);
        }

        else if(kodOperacji == "GET-SR"){
            cin >> s;
            sklad.getsr(s);
        }

        else if(kodOperacji == "GET-S"){
            sklad.gets();
        }

        else if(kodOperacji == "SET-LW"){
            cin >> w >> r >> s >> p >> label[0] >> label[1];
            sklad.setlw(w,r,s,p,label);
        }

        else if(kodOperacji == "SET-LH"){
            cin >> w >> p >> label[0] >> label[1];
            sklad.setlh(w,p,label);
        }

        else if(kodOperacji == "SET-LR"){
            cin >> s >> p >> label[0] >> label[1];
            sklad.setlr(s,p,label);
        }

        else if(kodOperacji == "SET-LS"){
            cin >> p >> label[0] >> label[1];
            sklad.setls(p, label);
        }

        else if(kodOperacji == "GET-LW"){
            cin >> w >> r >> s >> p;
            sklad.getlw(w,r,s,p);
        }

        else if(kodOperacji == "GET-LH"){
            cin >> w >> p;
            sklad.getlh(w,p);
        }

        else if(kodOperacji == "GET-LR"){
            cin >> s >> p;
            sklad.getlr(s,p);
        }

        else if(kodOperacji == "GET-LS"){
            cin >> p;
            sklad.getls(p);
        }



/*Polecenia etykietowe:
        * ◦SET-LWwrspdd  - w  magazynie  w,  w  regale o numerze r, na półce o numerze s, miejscu o numerze pnadaje etykietę dd.
        * ◦SET-LHwpdd -    w magazynie w, w podręcznej półce, miejscu o numerze p nadaje etykietę wynoszącą dd.
        * ◦SET-LRspdd  - w podręcznym regale składu, na półce o numerze p, miejscu o numerze pnadaje etykietę dd.
        * ◦SET-LSpdd  - w podręcznej półce składu, miejscu o numerze p    nadaje etykietę dd.
        * ◦GET-LWwrsp  - wyświetla etykietę miejsca w magazynie o numerze w, w regale o numerze r, na półce o numerze s, o numerze p.
        * ◦GET-LHwp  - wyświetla etykietę miejsca w magazynie  o  numerze w, w podręcz nej półce, o numerze p.
        * ◦GET-LRsp - wyświetla etykietę miejsca w podręcznym regale składu, na półce o numerze p, o numerze p.
         * ◦GET-LSp   - wyświetla  etykietę  miejsce  w podręcznej  półce  składu, o numerze p.
        * ◦Jeżeli towar dany argumentemnie ma etykiety, to w jednej linii wyświe-tlany jest ciąg złożony z dwóch znaków minus.*/
    }

    return 0;
}
