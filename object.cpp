#include "object.h"
#include <iostream>

// Create copies

Object *AndGate::createNewObject(sf::Mouse m)
{
    AndGate *g = new AndGate(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *OrGate::createNewObject(sf::Mouse m)
{
    OrGate *g = new OrGate(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *NotGate::createNewObject(sf::Mouse m)
{
    NotGate *g = new NotGate(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *XorGate::createNewObject(sf::Mouse m)
{
    XorGate *g = new XorGate(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *DFlipFlop::createNewObject(sf::Mouse m)
{
    DFlipFlop *g = new DFlipFlop(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *LogicOne::createNewObject(sf::Mouse m)
{
    LogicOne *g = new LogicOne(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *Gnd::createNewObject(sf::Mouse m)
{
    Gnd *g = new Gnd(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *Clock::createNewObject(sf::Mouse m)
{
    Clock *g = new Clock(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

Object *LED::createNewObject(sf::Mouse m)
{
    LED *g = new LED(false);
    g->setPos(m.getPosition().x, m.getPosition().y);

    return g;
}

/************************************************/

Object::Object()
{
    std::cout << "Object created" << std::endl;
}

Object::~Object()
{
    std::cout << "Object destroyed" << std::endl;
}

sf::Sprite Object::getSprite()
{
    return sprite;
}

sf::Vector2f Object::getPos()
{
    return sprite.getPosition();
}

void Object::setPos(int x, int y)
{
    sprite.setPosition(x, y);
}

Wire::Wire(Pin *pin1, Pin *pin2)
{
    std::cout << "Wire created" << std::endl;

    pins[0] = pin1;
    pins[1] = pin2;
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

LogicElement::LogicElement(int numPins) : numPins(numPins)
{
    this->numPins = numPins;
    std::cout << "LogicElement created" << std::endl;
}

LogicElement::~LogicElement()
{
    std::cout << "LogicElement destroyed" << std::endl;
}

AndGate::AndGate(bool is_locked) : LogicElement(3)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(0, 15));
    }
    textures[0].loadFromFile("TemplateProject/assets/AND.png");
    sprite.setTexture(textures[0]);
    std::cout << "AndGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;
}

void AndGate::simulate()
{
    if ((pins[0].state & pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    std::cout << "AndGate simulated" << std::endl;
}

AndGate::~AndGate()
{
    std::cout << "AndGate destroyed" << std::endl;
}

OrGate::OrGate(bool is_locked) : LogicElement(3)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(0, 90));
    }
    textures[0].loadFromFile("TemplateProject/assets/OR.png");
    sprite.setTexture(textures[0]);
    std::cout << "OrGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;
}

void OrGate::simulate()
{
    if ((pins[0].state | pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    std::cout << "OrGate simulated" << std::endl;
}

OrGate::~OrGate()
{
    std::cout << "OrGate destroyed" << std::endl;
}

NotGate::NotGate(bool is_locked) : LogicElement(2)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(0, 165));
    }
    textures[0].loadFromFile("TemplateProject/assets/NOT.png");
    sprite.setTexture(textures[0]);
    std::cout << "NotGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::OUTPUT;
}

void NotGate::simulate()
{
    if (pins[0].state)
        pins[1].state = Pin::pinState::LOW;
    else
        pins[1].state = Pin::pinState::HIGH;

    std::cout << "NotGate simulated" << std::endl;
}

NotGate::~NotGate()
{
    std::cout << "NotGate destroyed" << std::endl;
}

XorGate::XorGate(bool is_locked) : LogicElement(3)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(0, 240));
    }
    textures[0].loadFromFile("TemplateProject/assets/XOR.png");
    sprite.setTexture(textures[0]);
    std::cout << "XorGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;
}

void XorGate::simulate()
{
    if ((pins[0].state ^ pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    std::cout << "XorGate simulated" << std::endl;
}

XorGate::~XorGate()
{
    std::cout << "XorGate destroyed" << std::endl;
}

DFlipFlop::DFlipFlop(bool is_locked) : LogicElement(4)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(0, 315));
    }
    textures[0].loadFromFile("TemplateProject/assets/DFF.png");
    sprite.setTexture(textures[0]);
    std::cout << "DFlipFlop created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;
    pins[3].type = Pin::pinType::OUTPUT;
}

void DFlipFlop::simulate()
{
    std::cout << "DFlipFlop simulated" << std::endl;
}

DFlipFlop::~DFlipFlop()
{
    std::cout << "DFlipFlop destroyed" << std::endl;
}

LogicOne::LogicOne(bool is_locked) : LogicElement(1)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(25, 415));
    }
    textures[0].loadFromFile("TemplateProject/assets/VDD.png");
    sprite.setTexture(textures[0]);
    std::cout << "LogicOne created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;
}

void LogicOne::simulate()
{
    pins[0].state = Pin::pinState::HIGH;

    std::cout << "LogicOne simulated" << std::endl;
}

LogicOne::~LogicOne()
{
    std::cout << "LogicOne destroyed" << std::endl;
}

Gnd::Gnd(bool is_locked) : LogicElement(1)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(25, 500));
    }
    textures[0].loadFromFile("TemplateProject/assets/GND.png");
    sprite.setTexture(textures[0]);
    std::cout << "Gnd created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;
}

void Gnd::simulate()
{
    pins[0].state = Pin::pinState::LOW;

    std::cout << "Gnd simulated" << std::endl;
}

Gnd::~Gnd()
{
    std::cout << "Gnd destroyed" << std::endl;
}

Clock::Clock(bool is_locked) : LogicElement(1)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(20, 565));
    }
    textures[0].loadFromFile("TemplateProject/assets/CLOCK.png");
    sprite.setTexture(textures[0]);
    std::cout << "Clock created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;
}

void Clock::simulate()
{
    // 1 HIGH 1 LOW oscillation
    std::cout << "Clock simulated" << std::endl;
}

Clock::~Clock()
{
    std::cout << "Clock destroyed" << std::endl;
}

LED::LED(bool is_locked) : LogicElement(1)
{
    this->locked = is_locked;
    if (locked)
    {
        sprite.setPosition(sf::Vector2f(25, 640));
    }
    textures[0].loadFromFile("TemplateProject/assets/LEDOFF.png");
    textures[1].loadFromFile("TemplateProject/assets/LEDON.png");
    sprite.setTexture(textures[0]);
    std::cout << "LED created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
}

void LED::simulate()
{   
    // texture[0] for LOW
    // texture[1] for HIGH
    if(pins[0].state) sprite.setTexture(textures[1]);
    else sprite.setTexture(textures[0]);

    std::cout << "LED simulated" << std::endl;
}

LED::~LED()
{
    std::cout << "LED destroyed" << std::endl;
}

Simulator::Simulator()
{
}

void Simulator::addObject(Object *o)
{
    objects.push_back(o);
}
