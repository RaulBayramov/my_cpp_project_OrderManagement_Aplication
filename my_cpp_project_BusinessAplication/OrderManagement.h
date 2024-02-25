#pragma once
#include <string>

class OrderManagement {
public:
    OrderManagement(int capacity = 10);//constructor
    OrderManagement(const OrderManagement& other);//copy constructor
    OrderManagement& operator=(const OrderManagement& other);//minijebis operatori(Assignment operator)
    ~OrderManagement();//destruktori

    void addOrder(int orderNumber, double reything, const std::string& name);//??????? ??????????? ????? ???????? ????????????
    int processOrder();//punktsia, romelits gamoiq’eneba shek’vetebis dasamushaveblad
    int getProcessedOrder();//punktsia, romelits gamoiq’eneba damushavebuli shek’vetebis misaghebad
    void print() const;//punktsia, romelits gamoiq’eneba siis ek’ranze dasabech’dad

private:
    class Sheqveta {
    public:
        int orderNumber;
        double customerRating;
        std::string name;
        Sheqveta* prev;
        Sheqveta* next;
        //shekveta klasis konstruktori
        Sheqveta(int orderNumber = 0, double customerRating = 0, const std::string& name = "", Sheqveta* prev = nullptr, Sheqveta* next = nullptr)
            : orderNumber(orderNumber), customerRating(customerRating), name(name), prev(prev), next(next) {}
    };

    Sheqveta* lowRatingOrders;//dabali reit’inguli shek’vetebis sia
    Sheqveta* highRatingOrders;//maghali reit’inguli shek’vetebis sia
    int* processedOrders;//damushavebuli shek’vetebis sia
    int processedOrdersSize;//damushavebuli shek’vetebis raodenoba
    int processedOrdersCapacity;//damushavebuli shek’vetebis motsuloba

    void addToEnd(Sheqveta*& head, Sheqveta* newSheqveta);//punktsia, romelits gamoiq’eneba siis bolos k’vandzis dasamat’eblad
    void insertSorted(Sheqveta*& head, Sheqveta* newNode);//punktsia, romelits gamoiq’eneba k’vandzebis tanmimdevrulad dasamat’eblad
    void removeFromList(Sheqveta*& head, int orderNumber);//punktsia, romelits gamoiq’eneba siidan k’vandzis amosaghebad
    void addToProcessedOrders(int orderNumber);//punktsia, romelits gamoiq’eneba shek’vetis dasamat’eblad damushavebuli shek’vetebis siashi
    void printList(const Sheqveta* head) const;//punktsia, romelits gamoiq’eneba siis ek’ranze dasabech’dad
    void copyList(const Sheqveta* source, Sheqveta*& destination);//punktsia, romelits gamoiq’eneba k’vandzebis erti siidan meore siashi k’op’irebistvis
    void deleteList(Sheqveta*& head); //punktsia, romelits gamoiq’eneba siashi k’vandzebis ts’asashlelad
    void printProcessedOrders() const;

};
