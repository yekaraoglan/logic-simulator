#ifndef OBJECT_H
#define OBJECT_H


class Object { // absract  // derived from logic gates
    protected:
    Object* next;
    bool locked;
    bool state;
    bool selected;

    public:
    Object();
    ~Object();
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;

    virtual void simulate( ) == 0 ;  // must be defined in derived class
};


class Wire : public Object {
    private:
    Pin* pins[2];
    public:
    Wire();
    ~Wire();
    sf::Vertex line [2];
    
}

class Pin {
    private:
    enum pinType { INPUT, OUTPUT }; //enum for pin type (input or output pin) 
    enum pinState { HIGHZ, LOW, HIGH }; //enum for pin state 
    
    int index;
    
    public:
    Pin();
    ~Pin();

    pinType type;
    bool isSrc[MAX_CONNECTIONS];

    Pin* conntectedTo[MAX_CONNECTIONS];
    Object* wires[MAX_CONNECTIONS];
    int numConnections;
    sf::Vector2f pos;
    pinState state;


};

class LogicElement : public Object {
    Pin pins[4];
    int numPins;
    public:
    LogicElement();
    LogicElement(int);
    ~LogicElement();
    virtual void simulate() = 0;
};

class AndGate: public LogicElement{
    public:
    AndGate();
    AndGate(int);
    ~AndGate();
    private:
    void simulate();
    
};

class OrGate: public LogicElement{
    public:
    OrGate();
    ~Orgate();
    private:
    void simulate();
    
};

class XorGate: public LogicElement{
    public:
    XorGate();
    ~XorGate();
    private:
    void simulate();
};

class NotGate: public LogicElement{
    public:
    NotGate();
    ~NotGate();
    private:
    void simulate();
};

class DFlipFlop: public LogicElement{
    public:
    DFlipFlop();
    ~DFlipFlop();
    private:
    void simulate();
};

class LogicOne: public LogicElement{
    public:
    LogicOne();
    ~LogicOne();
    private:
    void simulate();
};

class Gnd: public LogicElement{
    public:
    Gnd()
    private:
    void simulate();
};

class Clock: public LogicElement{
    public:
    Clock()
    private:
    sf::Clock clock;
    void simulate();
};

class LED: public LogicElement{
    public:
    LED()
    private:
    void simulate();
    
};

class Simulator {
    public:
    Simulator();

};

#endif // !OBJECT_H

