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

    virtual Object* createNewObject(sf::Mouse) = 0;
    virtual void simulate() = 0; // must be defined in derived class
};

class Pin
{
public:
    enum pinType
    {
        INPUT,
        OUTPUT
    }; // enum for pin type (input or output pin)
    enum pinState
    {
        LOW, // 0
        HIGH, // 1
        HIGHZ // not determined
    }; // enum for pin state

    int index;

    Pin();
    ~Pin();

    pinType type;
    bool isSrc[MAX_CONNECTIONS];

    Pin *conntectedTo[MAX_CONNECTIONS];
    Object *wires[MAX_CONNECTIONS];
    int numConnections;
    sf::Vector2f pos;
    pinState state;
};

class Wire : public Object
{
private:
    Pin *pins[2];

public:
    Wire(Pin*, Pin*);
    ~Wire();
    sf::Vertex line[2];
};

class LogicElement : public Object
{
protected:
    Pin pins[4];
    int numPins;

public:
    LogicElement();
    LogicElement(int);
    virtual ~LogicElement() = 0;
    virtual void simulate() = 0;
};

class AndGate : public LogicElement
{
public:
    AndGate(bool);
    ~AndGate();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class OrGate : public LogicElement
{
public:
    OrGate(bool);
    ~OrGate();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class NotGate : public LogicElement
{
public:
    NotGate(bool);
    ~NotGate();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class XorGate : public LogicElement
{
public:
    XorGate(bool);
    ~XorGate();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class DFlipFlop : public LogicElement
{
public:
    DFlipFlop(bool);
    ~DFlipFlop();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class LogicOne : public LogicElement
{
public:
    LogicOne(bool);
    ~LogicOne();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class Gnd : public LogicElement
{
public:
    Gnd(bool);
    ~Gnd();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class Clock : public LogicElement
{
public:
    Clock(bool);
    ~Clock();

    Object* createNewObject(sf::Mouse);

private:
    sf::Clock clock;
    void simulate();
};

class LED : public LogicElement
{
public:
    LED(bool);
    ~LED();

    Object* createNewObject(sf::Mouse);

private:
    void simulate();
};

class Simulator
{
    private:
    std::vector<Object*> objects;
public:
    Simulator();
    void addObject(Object*);
};

#endif // !OBJECT_H
