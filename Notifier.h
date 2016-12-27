//
// Created by avi on 30/11/16.
//

#ifndef ASS1_NOTIFIER_H
#define ASS1_NOTIFIER_H

#include <iostream>
#include <list>
#include "Listener.h"
using namespace std;
/**
 * Notify those who listen.
 */
class Notifier {
public:
    virtual void AddCallListener(Listener* l) = 0;
    virtual void RemoveCallListener(Listener* l) = 0;
    virtual void NotifyCall(list<Listener*> l) = 0;
};


#endif //ASS1_NOTIFIER_H
