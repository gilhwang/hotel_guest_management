/*
 * File: CustomerInfo.cpp
 * Description: Implmentation of CustomerInfo methods
 */

#include "CustomerInfo.hpp"
#include "globals.hpp"

#define INVALID_NUM -1;

/*
 * Constructors
 */ 
// Default Constructor
CustomerInfo::CustomerInfo() {
    guestNumber = INVALID_NUM;
    roomNumber = INVALID_NUM;
    Date defaultDate(10,8,10);
    startDate = defaultDate;
    endDate = defaultDate;
    payMethod = Payment::unselected;
}

// Value Constructor
CustomerInfo::CustomerInfo(int guestNum, int roomNum, Date start, Date end, Payment method) {
    guestNumber = guestNum;
    roomNumber = roomNum;
    startDate = start;
    endDate = end;
    payMethod = method;
}

// Copy Constructor
CustomerInfo::CustomerInfo(const CustomerInfo& src) {
    guestNumber = src.guestNumber;
    roomNumber = src.roomNumber;
    startDate = src.startDate;
    endDate = src.endDate;
    payMethod = src.payMethod;
}

/*
 * Methods
 */
// Return payment method as string
std::string CustomerInfo::getPaymentString() const {
    int payment = static_cast<int>(payMethod);
    return PAYMENT_STRING[payment];
}



/*
 * Operators
 */
// Operator=
CustomerInfo CustomerInfo::operator=(const CustomerInfo& src) {
    guestNumber = src.guestNumber;
    roomNumber = src.roomNumber;
    startDate = src.startDate;
    endDate = src.endDate;
    payMethod = src.payMethod;

    return (*this);
}

// Operator<<
std::ostream& operator<<(std::ostream& os, const CustomerInfo& obj) {
    os << obj.guestNumber << "|" << obj.roomNumber <<  "|" << obj.startDate << "|"
       << obj.endDate << "|" << PAYMENT_STRING[static_cast<int>(obj.payMethod)];

    return os;
}