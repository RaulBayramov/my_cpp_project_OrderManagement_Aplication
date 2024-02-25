#include "OrderManagement.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    std::string businesses[] = { "ABC Company", "XYZ Corporation", "123 Services", "Quick Solutions", "Tech Innovators",
                                 "Global Enterprises", "Creative Minds", "Swift Services", "Power Systems", "Dynamic Solutions" };

    srand(time(0));
    OrderManagement orderManager;

    for (int i = 0; i < 20; ++i) {
        std::string businessName = businesses[rand() % 10];
        int orderNumber = rand() % 1000 + 1000;
        double customerRating = (rand() % 101) / 100.0;

        orderManager.addOrder(orderNumber, customerRating, businessName);
    }

    OrderManagement orderTemp = orderManager;
    orderTemp.print();
    OrderManagement s1;
    s1 = orderManager;

    std::cout << "\n****************************MINIJEBIS OPERATORI (DEEP COPY)****************************\n";
    s1.print();
    return 0;
}
