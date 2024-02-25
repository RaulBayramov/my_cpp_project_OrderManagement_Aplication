#include "OrderManagement.h"
#include <iostream>

OrderManagement::OrderManagement(int capacity) {//constructor
    lowRatingOrders = nullptr;
    highRatingOrders = nullptr;
    processedOrdersSize = 0;
    processedOrdersCapacity = capacity;
    processedOrders = new int[processedOrdersCapacity];
}

OrderManagement::OrderManagement(const OrderManagement& other)//copy Constructor
    : processedOrdersSize(other.processedOrdersSize), processedOrdersCapacity(other.processedOrdersCapacity) {
    processedOrders = new int[processedOrdersCapacity];
    // jer daak’op’iret damushavebuli shek’vetebis masivi.
    for (int i = 0; i < processedOrdersSize; ++i) {
        processedOrders[i] = other.processedOrders[i];
    }
    //shemdeg daak’op’iret dabali da maghali reitingis siebi.
    copyList(other.lowRatingOrders, lowRatingOrders);
    copyList(other.highRatingOrders, highRatingOrders);
}

OrderManagement& OrderManagement::operator=(const OrderManagement& other) {//minijebis operatori
    if (this != &other) {//tu tavis tavs ar kopirebs
        //mimdinare damushavebuli shek’vetebis masivis gasuptaveba
        delete[] processedOrders;
        //mimdinare dabali shek’vetebis siis gasuptaveba
        deleteList(lowRatingOrders);
        //mimdinare magali reitunguli shek’vetebis siis gasuptaveba
        deleteList(highRatingOrders);
        //am obiekt’ze daak’op’iret skhva obiekt’is tvisebebi
        processedOrdersSize = other.processedOrdersSize;
        processedOrdersCapacity = other.processedOrdersCapacity;
        //shekmenit akhali damushavebuli rigis masivi da daak’op’iret skhva obiekt’is monatsemebi
        processedOrders = new int[processedOrdersCapacity];
        for (int i = 0; i < processedOrdersSize; ++i) {
            processedOrders[i] = other.processedOrders[i];
        }
        //daak’op’iret dabali reitunguli shek’vetebis sia skhva obiekt’idan
        copyList(other.lowRatingOrders, lowRatingOrders);
        //daak’op’iret magali reitinguli shek’vetebis sia skhva obiekt’idan
        copyList(other.highRatingOrders, highRatingOrders);
    }

    return *this; //daabrune obiekdi
}

OrderManagement::~OrderManagement() {//destructor
    delete[] processedOrders;
    deleteList(lowRatingOrders);
    deleteList(highRatingOrders);
}

void OrderManagement::addOrder(int orderNumber, double reything, const std::string& name) {
    //ikmneba akhali Sheqveta obiekt’i da initsializebulia sach’iro inpormatsiit.
    Sheqveta* newSheqveta = new Sheqveta(orderNumber, reything, name);
    //lambda funkcia: amots’mebs aris tu ara motsemuli shek’vetis nomeri siashi.
    auto isExists = [](Sheqveta* sheqveta, int olderNum) {
        while (sheqveta != nullptr) {
            if (sheqveta->orderNumber == olderNum) {//tu ipova
                return true; //daabrunebs trues
            }
            sheqveta = sheqveta->next;// tu ver ipova sheqveta sanam nullptr ikneba manamde shemdeg gvandze gadava
        }
        return false;//tu ver ipova daabrunebs false
        };
    //tu shek’vetis nomeri uk’ve arsebobs ert-ert siashi, akhali Sheqveta obiekt’i ts’aishleba da punktsia mtavrdeba
    if (isExists(lowRatingOrders, orderNumber) || isExists(highRatingOrders, orderNumber)) {
        delete newSheqveta;
        return;
    }
    //tu reit’ingi 0.75-ze nak’lebia, akhali shek’vet’a obiekt’i emat’eba "lowRatingOrders" siis bolos.
    if (reything < 0.75) {
        addToEnd(lowRatingOrders, newSheqveta);
    }
    //tu reit’ingi aris 0.75 an met’i, akhali Sheqveta obiekt’i tanmimdevrulad emat’eba "highRatingOrders" sias.
    //pirobidan gamomdinare rogorc stxovt
    else {
        insertSorted(highRatingOrders, newSheqveta);
    }
}

int OrderManagement::processOrder() {
    //maghali reitinguli shek’vetebis siis k’ont’roli
    if (highRatingOrders != nullptr) {
        //miighet p’irveli shek’vetis nomeri
        int orderNumber = highRatingOrders->orderNumber;
        //daamat’et sias, romelits sheitsavs damushavebul shek’vetebs
        addToProcessedOrders(orderNumber);
        //amoighet damushavebuli shek’veta maghali reitinguli shek’vetebis siidan
        removeFromList(highRatingOrders, orderNumber);
        //daabrunet damushavebuli shek’vetis nomeri
        return orderNumber;
    }  //dabali reitinguli shek’vetebis siis k’ont’roli
    else if (lowRatingOrders != nullptr) {
        //miighet p’irveli shek’vetis nomeri
        int orderNumber = lowRatingOrders->orderNumber;
        //daamat’et sias, romelits sheitsavs damushavebul shek’vetebs
        addToProcessedOrders(orderNumber);
        //amoighet damushavebuli shek’veta maghali reitinguli shek’vetebis siidan
        removeFromList(lowRatingOrders, orderNumber);
        //daabrunet damushavebuli shek’vetis nomeri
        return orderNumber;
    }
    else {
        return -1;//daabrunet -1, rata miutitot, rom shek’vetebi ar aris dasamushavebeli
    }
}



int OrderManagement::getProcessedOrder() {
    // tu damushavebuli shek’vetebis raodenoba nulze met’ia,
        //miighet bolo damat’ebuli brdzaneba masivshi da amoighet igi masividan.
    if (processedOrdersSize > 0) {
        int orderNumber = processedOrders[processedOrdersSize - 1];
        processedOrdersSize--;//vinaidan chven vak’lebt masivs, sheamtsiret masivis zoma ertit.
        return orderNumber; //daabrune nomeri
    }
    else {
        return -1;
    }
}

void OrderManagement::print() const { // begdvis punkcia
    std::cout << "Low Rating Orders:" << std::endl;
    printList(lowRatingOrders); //printList funkciis daxmarebit ger dabejdavs Low Rating Orders

    std::cout << "High Rating Orders:" << std::endl; ////printList funkciis daxmarebit ger dabejdavs High Rating Orders
    printList(highRatingOrders);
}


void OrderManagement::addToEnd(Sheqveta*& head, Sheqveta* newSheqveta) {//punktsia, romelits gamoiq’eneba siis bolos k’vandzis dasamat’eblad
    if (head == nullptr) { //tu sia tsarielia, gaak’etet akhali k’vandzi siis sataved.
        head = newSheqveta;
    }
    else {
        Sheqveta* temp = head;
        //gadadis siis bolos.
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        //daamat’et akhali k’vandzi siis bolos.
        temp->next = newSheqveta;
        //daaq’enet akhali k’vandzis ts’ina mimtitebeli bolo k’vandzze, romelits gansazghvrulia t’emp’ad.
        newSheqveta->prev = temp;
        //daaq’enet akhali k’vandzis shemdegi mimtitebeli nullptr-ze, radgan is bolo k’vandzia.
        newSheqveta->next = nullptr;
    }
}

void OrderManagement::insertSorted(Sheqveta*& head, Sheqveta* newNode) {
    //tu sia tsarielia an akhali k’vandzis momkhmarebelta reit’ingi metia satave k’vandzis momkhmarebelta reit’ingze
    //daamat’et akhali k’vandzi siis dasats’q’isshi.
    if (head == nullptr || head->customerRating < newNode->customerRating) {
        newNode->next = head;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
    }
    else {
        Sheqveta* temp = head;
        //sanam bolo elementi an akhali k’vandzis momkhmarebelta reit’ingi naklebia nan tolia satave k’vandzis momkhmarebelta reit’ingze
        while (temp->next != nullptr && temp->next->customerRating >= newNode->customerRating) {
            temp = temp->next; //head node(temp) = shemdeg kvandzs
        }
        newNode->next = temp->next; //axali kvandzi daamatet mis momdevno kvandzs
        if (temp->next != nullptr) {//tu temp bolo elementi ar aris
            temp->next->prev = newNode;//tempis shemdegi elementis previusi iyos axali nodi
        }
        temp->next = newNode; //tempis momdevno aris axali kvandzi
        newNode->prev = temp;//axalis previusi ki tempi
    }
}

void OrderManagement::removeFromList(Sheqveta*& head, int orderNumber) {
    // ikmneba droebiti Sheqveta pointeri da siis sataves miutitebs.
    Sheqveta* temp = head;
    // Temp midis siis bolomde an element’ze, romelits sheitsavs mititebul shek’vetis nomers.
    while (temp != nullptr && temp->orderNumber != orderNumber) {
        temp = temp->next;
    }
    //tu temp aris nullptr, es nishnavs, rom man ver ip’ova mititebuli shek’vetis nomris shemtsveli element’i, am shemtkhvevashi p’rotsesi ts’q’deba.
    if (temp == nullptr) {
        return;
    }
    //tu temp-is prev ar aris nullptr, temp element’i ar aris siis zeda nats’ilshi da chven vak’avshirebt ts’ina element’is shemdegs temp-is shemdegs.
    if (temp->prev != nullptr) {
        temp->prev->next = temp->next;
    }
    //tu temp-is prev aris nullptr, temp element’i aris siis dasats’q’isshi da chven vuk’avshirdebit head-s temp-is shemdegs.
    else {
        head = temp->next;
    }
    //tu shemdegi temp ar aris nullptr, temp element’i ar aris siis bolos da chven vuk’avshirebt shemdegi element’is prev-s prev of temp-s.
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    //vshlit temps
    delete temp;
}


void OrderManagement::addToProcessedOrders(int orderNumber) {
    // tu damushavebuli shek’vetebis raodenoba mis motsulobaze nak’lebia, shegvidzlia davamat’ot akhali shek’veta arsebuli masivis bolos.
    if (processedOrdersSize < processedOrdersCapacity) {
        processedOrders[processedOrdersSize] = orderNumber;
        processedOrdersSize++;//masivis element’ebis raodenobis gazrda ertit.
    }
    else {//tu size arasak’marisia, chven shevkmnit akhal masivs da davak’op’irebt monatsemebs.

        int newCapacity = processedOrdersCapacity * 2; //kapaziti gaazarde 2 jer
        int* newProcessedOrders = new int[newCapacity];
        //daak’op’iret arsebuli monatsemebi akhal masivshi.
        for (int i = 0; i < processedOrdersSize; ++i) {
            newProcessedOrders[i] = processedOrders[i];
        }
        //gazardet masivis zoma siganis rigis damat’ebit.
        newProcessedOrders[processedOrdersSize] = orderNumber;
        processedOrdersSize++;

        //wveli casale da miutite axalze
        delete[] processedOrders;
        processedOrders = newProcessedOrders;
        processedOrdersCapacity = newCapacity;
    }
}

void OrderManagement::printList(const Sheqveta* head) const {
    const Sheqveta* current = head;//current pointeri miututebs siis sataves(head's)
    while (current != nullptr) {//manam sanam current nullptr ikneba, anu siis bolo elementamde grceldeba
        std::cout << "Order Number: " << current->orderNumber  //monacemebis begdva
            << ", Customer Rating: " << current->customerRating
            << ", Business Name: " << current->name << std::endl;
        current = current->next; //shemdeg nodze gadasvla
    }
}
void OrderManagement::printProcessedOrders() const {
    std::cout << "Processed Orders:" << std::endl; //bejdavs damushavebuli sheqvetebs
    for (int i = 0; i < processedOrdersSize; ++i) {
        std::cout << processedOrders[i] << " ";
    }
    std::cout << std::endl;
}



void OrderManagement::copyList(const Sheqveta* source, Sheqveta*& destination) {
    deleteList(destination); // ??????????? ????

    const Sheqveta* current = source; // siis gadasvlistvis ikmneba pointeri current romelic sources tolia(parametrshi mititebulia)
    Sheqveta* tail = nullptr; //bolo elementis sanaxavad ikmneba taili
    while (current != nullptr) {//tu list carieli ar aris 
        Sheqveta* newNode = new Sheqveta(current->orderNumber, current->customerRating, current->name);//????? ???? ?????? (newNode) ???????? ????????? ??????? ????? ???????.
        newNode->prev = nullptr;
        if (tail != nullptr) {//tu bolo ar aris nullptr
            tail->next = newNode; //tailis shemdegi gvandzi ikneba axali gvandzi
            newNode->prev = tail; //da tail ikneba axali kvadzis cina kvadzi
        }
        else {//tu tail aris nullptr
            destination = newNode;
        }
        tail = newNode; //bolo aris 
        current = current->next;
    }
}

void OrderManagement::deleteList(Sheqveta*& head) {//bmuli siis washla
    while (head != nullptr) {//tu listi carieli ar aris
        Sheqveta* temp = head;//bmuli siis dasacgiss miutitebs temp
        head = head->next;//head udris shedeg kvandzs
        delete temp; //cashale temp, anu head;
    }//manam sanam head nullptr ikneba gagrceldeba ciqli
}
