#include "object.h"
#include "object.cpp"
#include <iostream>

/**
 * TODO:
    * - Set a background
    * - Smaller textures
    * - Bigger window
    * - Mouse - object interactions
 *  
 */

int main(){
    sf::RenderWindow window(sf::VideoMode(960, 720), "My window");
    AndGate andGate(true);
    OrGate orGate(true);
    NotGate notGate(true);
    XorGate xorGate(true);
    DFlipFlop dFlipFlop(true);
    LogicOne logicOne(true);
    Gnd gnd(true);
    LED led(true);
    Clock clock(true);

    // sf::Sprite background;
    // sf::Texture back_text;
    // back_text.loadFromFile("TemplateProject/assets/background.png");
    // background.setTexture(back_text);

    sf::Sprite start;
    sf::Texture start_text;
    start_text.loadFromFile("TemplateProject/assets/START.png");
    start.setTexture(start_text);
    start.setPosition(sf::Vector2f(150, 50));

    sf::Sprite stop;
    sf::Texture stop_text;
    stop_text.loadFromFile("TemplateProject/assets/STOP.png");
    stop.setTexture(stop_text);
    stop.setPosition(sf::Vector2f(400, 50));

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        // window.draw(background);
        window.draw(start);
        window.draw(stop);
        window.draw(andGate.sprite);
        window.draw(orGate.sprite);
        window.draw(notGate.sprite);
        window.draw(xorGate.sprite);
        window.draw(dFlipFlop.sprite);
        window.draw(logicOne.sprite);
        window.draw(gnd.sprite);
        window.draw(led.sprite);
        window.draw(clock.sprite);
        window.display();

    }
    return 0;
}
