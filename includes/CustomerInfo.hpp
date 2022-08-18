/*
 * File: CustomerInfo.hpp
 * Description: Definition of CustomerInfo class
 */
#pragma once
#include "helper.hpp"
#include "Date.hpp"

class CustomerInfo {
public:
    int guestNumber;
    int roomNumber;
    Date startDate;
    Date endDate;
    Payment payMethod;

    // Constructor
    CustomerInfo();
    CustomerInfo(int guestNum, int roomNum, Date start, Date end, Payment method);
    CustomerInfo(const CustomerInfo& src);

    // Methods
    std::string getPaymentString() const;

    // Operator
    CustomerInfo operator=(const CustomerInfo& src);
    friend std::ostream& operator<<(std::ostream& os, const CustomerInfo& obj);
};