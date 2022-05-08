#include "object.h"
#include <iostream>


Object::Object(){
    std::cout << "Object created" << std::endl;
}

Object::~Object()
{
    std::cout << "Object destroyed" << std::endl;
}

Wire::Wire(){
    std::cout << "Wire created" << std::endl;
}

Wire::~Wire()
{
    std::cout << "Wire destroyed" << std::endl;
}

Pin::Pin(){
    std::cout << "Pin created" << std::endl;
}

Pin::~Pin()
{
    std::cout << "Pin destroyed" << std::endl;
}

LogicElement::LogicElement(){
    std::cout << "LogicElement created" << std::endl;
}

LogicElement::LogicElement(int numPins) : numPins(numPins){
    this->numPins = numPins;
    std::cout << "LogicElement created" << std::endl;
}

LogicElement::~LogicElement()
{
    std::cout << "LogicElement destroyed" << std::endl;
}

AndGate::AndGate(bool is_locked): LogicElement(3){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(0, 15));
    }
    texture.loadFromFile("TemplateProject/assets/AND.png");
    sprite.setTexture(texture);
    std::cout << "AndGate created" << std::endl;
}

void AndGate::simulate(){
    std::cout << "AndGate simulated" << std::endl;
}

AndGate::~AndGate()
{
    std::cout << "AndGate destroyed" << std::endl;
}

OrGate::OrGate(bool is_locked) : LogicElement(3){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(0, 90));
    }
    texture.loadFromFile("TemplateProject/assets/OR.png");
    sprite.setTexture(texture);
    std::cout << "OrGate created" << std::endl;
}

void OrGate::simulate()
{
    std::cout << "OrGate simulated" << std::endl;
}

OrGate::~OrGate()
{
    std::cout << "OrGate destroyed" << std::endl;
}

NotGate::NotGate(bool is_locked) : LogicElement(2){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(0, 165));
    }
    texture.loadFromFile("TemplateProject/assets/NOT.png");
    sprite.setTexture(texture);
    std::cout << "NotGate created" << std::endl;
}

void NotGate::simulate()
{
    std::cout << "NotGate simulated" << std::endl;
}

NotGate::~NotGate()
{
    std::cout << "NotGate destroyed" << std::endl;
}

XorGate::XorGate(bool is_locked) : LogicElement(3){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(0, 240));
    }
    texture.loadFromFile("TemplateProject/assets/XOR.png");
    sprite.setTexture(texture);
    std::cout << "XorGate created" << std::endl;
}

void XorGate::simulate()
{
    std::cout << "XorGate simulated" << std::endl;
}

XorGate::~XorGate()
{
    std::cout << "XorGate destroyed" << std::endl;
}

DFlipFlop::DFlipFlop(bool is_locked) : LogicElement(4){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(0, 315));
    }
    texture.loadFromFile("TemplateProject/assets/DFF.png");
    sprite.setTexture(texture);
    std::cout << "DFlipFlop created" << std::endl;
}

void DFlipFlop::simulate()
{
    std::cout << "DFlipFlop simulated" << std::endl;
}

DFlipFlop::~DFlipFlop()
{
    std::cout << "DFlipFlop destroyed" << std::endl;
}

LogicOne::LogicOne(bool is_locked) : LogicElement(1){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(25, 415));
    }
    texture.loadFromFile("TemplateProject/assets/VDD.png");
    sprite.setTexture(texture);
    std::cout << "LogicOne created" << std::endl;
}

void LogicOne::simulate()
{
    std::cout << "LogicOne simulated" << std::endl;
}

LogicOne::~LogicOne()
{
    std::cout << "LogicOne destroyed" << std::endl;
}

Gnd::Gnd(bool is_locked) : LogicElement(1){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(25, 500));
    }
    texture.loadFromFile("TemplateProject/assets/GND.png");
    sprite.setTexture(texture);
    std::cout << "Gnd created" << std::endl;
}

void Gnd::simulate()
{
    std::cout << "Gnd simulated" << std::endl;
}

Gnd::~Gnd()
{
    std::cout << "Gnd destroyed" << std::endl;
}

Clock::Clock(bool is_locked) : LogicElement(1){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(20, 565));
    }
    texture.loadFromFile("TemplateProject/assets/CLOCK.png");
    sprite.setTexture(texture);
    std::cout << "Clock created" << std::endl;
}

void Clock::simulate()
{
    std::cout << "Clock simulated" << std::endl;
}

Clock::~Clock()
{
    std::cout << "Clock destroyed" << std::endl;
}

LED::LED(bool is_locked) : LogicElement(1){
    this->locked = is_locked;
    if (locked){
        sprite.setPosition(sf::Vector2f(25, 640));
    }
    texture.loadFromFile("TemplateProject/assets/LEDON.png");
    sprite.setTexture(texture);
    std::cout << "LED created" << std::endl;
}

void LED::simulate()
{
    std::cout << "LED simulated" << std::endl;
}

LED::~LED()
{
    std::cout << "LED destroyed" << std::endl;
}


