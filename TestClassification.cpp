//
// Created by Olcay Taner Yıldız on 26.01.2019.
//

#include <iostream>
#include "Instance/Instance.h"
#include "Attribute/ContinuousAttribute.h"
#include "Attribute/DiscreteIndexedAttribute.h"

int main(){
    Instance instance("true");
    Attribute* attribute1 = new ContinuousAttribute(3.0);
    instance.addAttribute(attribute1);
    Attribute* attribute2 = new DiscreteIndexedAttribute("true", 0, 4);
    instance.addAttribute(attribute2);
    cout << instance.continuousAttributeSize();
}
