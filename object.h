#ifndef OBJECT_H
#define OBJECT_H

class Object { // absract  // derived from logic gates
    protected:
    Object* next;
    bool locked;
    bool state;
    bool selected;

    public:
    sf::RenderWindow* window;
    sf::Texture texture;
    sf::Sprite sprite;

    virtual void simulate( ) == 0 ;  // must be defined in derived class
};


class Wire : public Object {
    private:
    Pin* pins[2];
    public:
    sf::Vertex line [2];
    
}

class Pin {
    private:
    enum pinType { INPUT, OUTPUT }; //enum for pin type (input or output pin) 
    enum pinState { HIGHZ, LOW, HIGH }; //enum for pin state 
    
    int index;
    

    public:
    

};

class LogicElement : public Object {
    Pin pins[4];
    int numPins;
};

class AndGate: public LogicElement{
    
    
};

class OrGate: public LogicElement{

    
};

class XorGate: public LogicElement{

    
};

class NotGate: public LogicElement{

    
};

class DFlipFlop: public LogicElement{

    
};

class LogicOne: public LogicElement{

    
};

class Gnd: public LogicElement{

    
};

class Clock: public LogicElement{
    sf::Clock clock;
    
};

class LED: public LogicElement{

    
};

#endif // !OBJECT_H

