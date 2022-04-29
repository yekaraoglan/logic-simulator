#include "object.h"
Object::Object()
{
    std::cout << "Object created" << std::endl;
}

Object::~Object()
{
    std::cout << "Object destroyed" << std::endl;
}

Wire::Wire()
{
    std::cout << "Wire created" << std::endl;
}

Wire::~Wire()
{
    std::cout << "Wire destroyed" << std::endl;
}

Pin::Pin()
{
    std::cout << "Pin created" << std::endl;
}

Pin::~Pin()
{
    std::cout << "Pin destroyed" << std::endl;
}

LogicElement::LogicElement()
{
    std::cout << "LogicElement created" << std::endl;
}

LogicElement::LogicElement(int numPins){
    this->numPins = numPins;
}

LogicElement::~LogicElement()
{
    std::cout << "LogicElement destroyed" << std::endl;
}

AndGate::AndGate(): LogicElement(3){
    std::cout << "AndGate created" << std::endl;
}

AndGate::~AndGate()
{
    std::cout << "AndGate destroyed" << std::endl;
}

OrGate::OrGate() : LogicElement(3)
{
    std::cout << "OrGate created" << std::endl;
}

OrGate::~OrGate()
{
    std::cout << "OrGate destroyed" << std::endl;
}

XorGate::XorGate() : LogicElement(3)
{
    std::cout << "XorGate created" << std::endl;
}

XorGate::~XorGate()
{
    std::cout << "XorGate destroyed" << std::endl;
}

NotGate::NotGate() : LogicElement(2)
{
    std::cout << "NotGate created" << std::endl;
}

NotGate::~NotGate()
{
    std::cout << "NotGate destroyed" << std::endl;
}


DFlipFlop::DFlipFlop() : LogicElement(4)
{
    std::cout << "DFlipFlop created" << std::endl;
}

DFlipFlop::~DFlipFlop()
{
}

LogicOne::LogicOne(): LogicElement(1)
{
    std::cout << "LogicOne created" << std::endl;
}
{
    std::cout << "LogicOne created" << std::endl;
}

LogicOne::~LogicOne()
{
}

OrGate::OrGate()
{
    std::cout << "OrGate created" << std::endl;
}

