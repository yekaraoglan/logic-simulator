#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#define MAX_CONNECTIONS 16 // how many object is connected with this object

class Object
{ // absract  // derived from logic gates
protected:
    Object *next;
    bool locked;
    bool state;
    bool selected;

public:
    Object();
    ~Object();
    sf::RenderWindow *window;
    sf::Texture textures[2];
    sf::Sprite sprite;

    sf::Sprite getSprite();
    sf::Vector2f getPos();
    void setPos(int, int);

    virtual void simulate() = 0; // must be defined in derived class
};

class Pin
{
public:
    enum pinType
    {
        INPUT,
        OUTPUT
    }; // enum for pin typmenuObjects[i]e (input or output pin)
    enum pinState
    {
        LOW,  // 0
        HIGH, // 1
        HIGHZ // not determined
    };        // enum for pin state

    int index;

    Pin();
    ~Pin();

    pinType type;
    bool isSrc[MAX_CONNECTIONS];

    Pin *connectedTo[MAX_CONNECTIONS];
    Object *wires[MAX_CONNECTIONS];
    int numConnections;
    sf::Vector2f pos;
    sf::FloatRect rect;
    pinState state;
    void setPos(sf::Vector2f);
};

class Wire : public Object
{
private:
    Pin *pins[2];

public:
    Wire(Pin *, Pin *);
    ~Wire();
    sf::Vertex line[2];
    void simulate();
    Pin** getPins();
    void updateWirePos();
};

class LogicElement : public Object
{
protected:
    // std::vector<Pin> pins;
    Pin pins[4];
    int numPins;

public:
    LogicElement();
    LogicElement(int);
    virtual ~LogicElement() = 0;
    virtual void simulate() = 0;
    virtual LogicElement *createNewLogicElement(sf::Mouse) = 0;
    virtual void configurePins() = 0;
    // std::vector<Pin> getPins();
    Pin *getPins();
    int getNumPins();
};

class AndGate : public LogicElement
{
public:
    AndGate(bool);
    ~AndGate();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class OrGate : public LogicElement
{
public:
    OrGate(bool);
    ~OrGate();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class NotGate : public LogicElement
{
public:
    NotGate(bool);
    ~NotGate();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class XorGate : public LogicElement
{
public:
    XorGate(bool);
    ~XorGate();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class DFlipFlop : public LogicElement
{
public:
    DFlipFlop(bool);
    ~DFlipFlop();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class LogicOne : public LogicElement
{
public:
    LogicOne(bool);
    ~LogicOne();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class Gnd : public LogicElement
{
public:
    Gnd(bool);
    ~Gnd();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class Clock : public LogicElement
{
public:
    Clock(bool);
    ~Clock();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    sf::Clock clock;
    void simulate();
};

class LED : public LogicElement
{
public:
    LED(bool);
    ~LED();

    LogicElement *createNewLogicElement(sf::Mouse);
    void configurePins();

private:
    void simulate();
};

class Simulator
{
private:
    std::vector<LogicElement *> logicElements;
    std::vector<Wire *> wires;

public:
    Simulator();
    void addLogicElement(LogicElement *);
    void addWire(Wire *);
    std::vector<LogicElement *> getLogicElements();
    std::vector<Wire *> getWires();

    void simulate();
};

#endif // !OBJECT_H
