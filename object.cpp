#include "object.h"
#include <iostream>

// Create copies

LogicElement *AndGate::createNewLogicElement(sf::Mouse m)
{
    AndGate *g = new AndGate(false);
    g->setPos(m.getPosition().x - 76, m.getPosition().y - 95);
    g->configurePins();
    return g;
}

LogicElement *OrGate::createNewLogicElement(sf::Mouse m)
{
    OrGate *g = new OrGate(false);
    g->setPos(m.getPosition().x - 76, m.getPosition().y - 95);
    g->configurePins();
    return g;
}

LogicElement *NotGate::createNewLogicElement(sf::Mouse m)
{
    NotGate *g = new NotGate(false);
    g->setPos(m.getPosition().x - 76, m.getPosition().y - 95);
    g->configurePins();
    return g;
}

LogicElement *XorGate::createNewLogicElement(sf::Mouse m)
{
    XorGate *g = new XorGate(false);
    g->setPos(m.getPosition().x - 76, m.getPosition().y - 95);
    g->configurePins();
    return g;
}

LogicElement *DFlipFlop::createNewLogicElement(sf::Mouse m)
{
    DFlipFlop *g = new DFlipFlop(false);
    g->setPos(m.getPosition().x - 80, m.getPosition().y - 99);
    g->configurePins();
    return g;
}

LogicElement *LogicOne::createNewLogicElement(sf::Mouse m)
{
    LogicOne *g = new LogicOne(false);
    g->setPos(m.getPosition().x - 80, m.getPosition().y - 99);
    g->configurePins();
    return g;
}

LogicElement *Gnd::createNewLogicElement(sf::Mouse m)
{
    Gnd *g = new Gnd(false);
    g->setPos(m.getPosition().x - 80, m.getPosition().y - 99);
    g->configurePins();
    return g;
}

LogicElement *Clock::createNewLogicElement(sf::Mouse m)
{
    Clock *g = new Clock(false);
    g->setPos(m.getPosition().x - 80, m.getPosition().y - 99);
    g->configurePins();
    return g;
}

LogicElement *LED::createNewLogicElement(sf::Mouse m)
{
    LED *g = new LED(false);
    g->setPos(m.getPosition().x - 80, m.getPosition().y - 99);
    g->configurePins();
    return g;
}

/************************************************/

Object::Object()
{
    // std::cout << "Object created" << std::endl;
}

Object::~Object()
{
    // std::cout << "Object destroyed" << std::endl;
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
    // std::cout << "Wire created" << std::endl;

    pins[0] = pin1;
    pins[1] = pin2;

    pins[0]->wires[pins[0]->numConnections] = this;
    pins[0]->numConnections++;
    pins[1]->wires[pins[1]->numConnections] = this;
    pins[1]->numConnections++;

    line[0] = sf::Vertex(sf::Vector2f(pins[0]->pos.x + pins[0]->rect.left+8, pins[0]->pos.y + pins[0]->rect.top+5));
    line[1] = sf::Vertex(sf::Vector2f(pins[1]->pos.x + pins[1]->rect.left+8, pins[1]->pos.y + pins[1]->rect.top+5));
}

Wire::~Wire()
{
    // std::cout << "Wire destroyed" << std::endl;
}

void Wire::simulate()
{

}

void Wire::updateWirePos()
{
    line[0] = sf::Vertex(sf::Vector2f(pins[0]->pos.x + pins[0]->rect.left+8, pins[0]->pos.y + pins[0]->rect.top+5));
    line[1] = sf::Vertex(sf::Vector2f(pins[1]->pos.x + pins[1]->rect.left+8, pins[1]->pos.y + pins[1]->rect.top+5));
}

Pin::Pin()
{
    numConnections = 0;
    // std::cout << "Pin created" << std::endl;
}

Pin::~Pin()
{
    // std::cout << "Pin destroyed" << std::endl;
}

void Pin::setPos(sf::Vector2f pos)
{
    rect.left = pos.x - 8;
    rect.top = pos.y - 8;
    rect.width = 16;
    rect.height = 16;
}

LogicElement::LogicElement()
{
    // std::cout << "LogicElement created" << std::endl;
}

LogicElement::LogicElement(int numPins) : numPins(numPins)
{
    this->numPins = numPins;
    // std::cout << "LogicElement created" << std::endl;
}

// std::vector<Pin> LogicElement::getPins()
// {
//     return pins;
// }

Pin *LogicElement::getPins()
{
    return pins;
}

int LogicElement::getNumPins()
{
    return numPins;
}

LogicElement::~LogicElement()
{
    // std::cout << "LogicElement destroyed" << std::endl;
    for (int i=0; i<numPins; i++)
    {
        for(int j=0; j<pins[i].numConnections; j++)
        {
            delete pins[i].wires[j];
        }
    }
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
    // std::cout << "AndGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGHZ;
    pins[1].state = Pin::pinState::HIGHZ;
    pins[2].state = Pin::pinState::HIGHZ;
}

void AndGate::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 15));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 50));
    pins[2].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 30));
}

void AndGate::simulate()
{
    if ((pins[0].state & pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    // std::cout << "AndGate simulated" << std::endl;
}

AndGate::~AndGate()
{
    // std::cout << "AndGate destroyed" << std::endl;
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
    // std::cout << "OrGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGHZ;
    pins[1].state = Pin::pinState::HIGHZ;
    pins[2].state = Pin::pinState::HIGHZ;
}

void OrGate::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 15));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 50));
    pins[2].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 30));
}

void OrGate::simulate()
{
    if ((pins[0].state | pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    // std::cout << "OrGate simulated" << std::endl;
}

OrGate::~OrGate()
{
    // std::cout << "OrGate destroyed" << std::endl;
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
    // std::cout << "NotGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGHZ;
    pins[1].state = Pin::pinState::HIGHZ;
}

void NotGate::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 33));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 33));
}

void NotGate::simulate()
{
    if (pins[0].state)
        pins[1].state = Pin::pinState::LOW;
    else
        pins[1].state = Pin::pinState::HIGH;

    // std::cout << "NotGate simulated" << std::endl;
}

NotGate::~NotGate()
{
    // std::cout << "NotGate destroyed" << std::endl;
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
    // std::cout << "XorGate created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGHZ;
    pins[1].state = Pin::pinState::HIGHZ;
    pins[2].state = Pin::pinState::HIGHZ;
}

void XorGate::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 15));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y + 50));
    pins[2].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 30));
}

void XorGate::simulate()
{
    if ((pins[0].state ^ pins[1].state))
        pins[2].state = Pin::pinState::HIGH;
    else
        pins[2].state = Pin::pinState::LOW;

    // std::cout << "XorGate simulated" << std::endl;
}

XorGate::~XorGate()
{
    // std::cout << "XorGate destroyed" << std::endl;
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
    // std::cout << "DFlipFlop created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;
    pins[1].type = Pin::pinType::INPUT;
    pins[2].type = Pin::pinType::OUTPUT;
    pins[3].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGHZ;
    pins[1].state = Pin::pinState::HIGHZ;
    pins[2].state = Pin::pinState::HIGHZ;
    pins[3].state = Pin::pinState::HIGHZ;
}

void DFlipFlop::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x + 10, sprite.getPosition().y + 25));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x + 10, sprite.getPosition().y + 40));
    pins[2].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 25));
    pins[3].setPos(sf::Vector2f(sprite.getPosition().x + 95, sprite.getPosition().y + 60));
}

void DFlipFlop::simulate()
{
    // std::cout << "DFlipFlop simulated" << std::endl;
}

DFlipFlop::~DFlipFlop()
{
    // std::cout << "DFlipFlop destroyed" << std::endl;
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
    // std::cout << "LogicOne created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGH;
}

void LogicOne::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x + 30, sprite.getPosition().y + 60));
}

void LogicOne::simulate()
{
    pins[0].state = Pin::pinState::HIGH;

    // std::cout << "LogicOne simulated" << std::endl;
}

LogicOne::~LogicOne()
{
    // std::cout << "LogicOne destroyed" << std::endl;
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
    // std::cout << "Gnd created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::LOW;
}

void Gnd::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x + 30, sprite.getPosition().y + 5));
}

void Gnd::simulate()
{
    pins[0].state = Pin::pinState::LOW;

    // std::cout << "Gnd simulated" << std::endl;
}

Gnd::~Gnd()
{
    // std::cout << "Gnd destroyed" << std::endl;
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
    // std::cout << "Clock created" << std::endl;

    pins[0].type = Pin::pinType::OUTPUT;

    pins[0].state = Pin::pinState::HIGH;
}

void Clock::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x + 80, sprite.getPosition().y + 30));
}

void Clock::simulate()
{
    // 1 HIGH 1 LOW oscillation
    // std::cout << "Clock simulated" << std::endl;
    sf::Time elapsedTime = clock.getElapsedTime();

    if (elapsedTime.asSeconds() >= 1)
    {
        if (pins[0].state != Pin::pinState::LOW) pins[0].state = Pin::pinState::LOW;
        else pins[0].state = Pin::pinState::HIGH;

        clock.restart();
    }
}

Clock::~Clock()
{
    // std::cout << "Clock destroyed" << std::endl;
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
    // std::cout << "LED created" << std::endl;

    pins[0].type = Pin::pinType::INPUT;

    pins[0].state = Pin::pinState::LOW;
}

void LED::configurePins()
{
    pins[0].setPos(sf::Vector2f(sprite.getPosition().x + 23, sprite.getPosition().y + 80));
    pins[1].setPos(sf::Vector2f(sprite.getPosition().x + 40, sprite.getPosition().y + 80));
}

void LED::simulate()
{
    // texture[0] for LOW
    // texture[1] for HIGH
    if (pins[0].state)
        sprite.setTexture(textures[1]);
    else
        sprite.setTexture(textures[0]);

    // std::cout << "LED simulated" << std::endl;
}

LED::~LED()
{
    // std::cout << "LED destroyed" << std::endl;
}

Simulator::Simulator()
{

}

void Simulator::addLogicElement(LogicElement *l)
{
    logicElements.push_back(l);
}

void Simulator::deleteLogicElement(int idx)
{
    LogicElement * l = logicElements[idx];
    logicElements.erase(logicElements.begin() + idx);
    delete l;
    logicElements.shrink_to_fit();
}

std::vector<LogicElement *> Simulator::getLogicElements()
{
    return logicElements;
}

void Simulator::addWire(Wire *l)
{
    wires.push_back(l);
}

std::vector<Wire *> Simulator::getWires()
{
    return wires;
}

void Simulator::simulate()
{
    wires.shrink_to_fit();

    for (int i=0; i<wires.size(); i++)
    {
        for (int j=0; j<logicElements.size(); j++)
        {
            logicElements[j]->simulate();
        }

        for (int j=0; j<wires.size(); j++)
        {
            wires[j]->getPins()[1]->state = wires[j]->getPins()[0]->state;
        }
    }
}

Pin** Wire::getPins()
{
    return pins;
}
