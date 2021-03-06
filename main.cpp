/**
 * @file main.cpp
 * @author Dogus Can Korkmaz, Yunus Emre Karaoglan, Serkan Basaran
 * @brief Main file for the project.
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "object.h"
#include "object.cpp"
#include <iostream>
#include <vector>



int main()
{

    /**
     * Creating window and setting it's size
     * Creating menu objects
     * Creating simulation object
     */
    
    sf::RenderWindow window(sf::VideoMode(960, 720), "My window");
    window.setPosition(sf::Vector2i(0, 0));
    sf::Vector2i windowPose = window.getPosition();
    AndGate andGate(true);
    OrGate orGate(true);
    NotGate notGate(true);
    XorGate xorGate(true);
    DFlipFlop dFlipFlop(true);
    LogicOne logicOne(true);
    Gnd gnd(true);
    LED led(true);
    Clock clock(true);
    bool isSimulating = false;

    Simulator sim;

    std::vector<LogicElement *> menuObjects;
    menuObjects.push_back(&andGate);
    menuObjects.push_back(&orGate);
    menuObjects.push_back(&notGate);
    menuObjects.push_back(&xorGate);
    menuObjects.push_back(&dFlipFlop);
    menuObjects.push_back(&logicOne);
    menuObjects.push_back(&gnd);
    menuObjects.push_back(&led);
    menuObjects.push_back(&clock);

    // sf::Sprite background;
    // sf::Texture back_text;
    // back_text.loadFromFile("TemplateProject/assets/background.png");
    // background.setTexture(back_text);

    /**
     * Adding Start and Stop buttons to the menu
     * Defining mouse and keyboard to get events
     */

    sf::Mouse mouse;
    sf::Keyboard keyboard;

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


    // Selection operation objects
    LogicElement *selected;
    sf::Sprite selectedSprite;
    bool draggingObject = false;
    bool relocatingObject = false;
    int selectedIdx = -1;
    sf::RectangleShape selectionRect;
    selectionRect.setFillColor(sf::Color::Transparent);
    selectionRect.setOutlineThickness(5);
    selectionRect.setOutlineColor(sf::Color::Red);

    // Sprites for the menu and the simulation
    std::vector<sf::Sprite> mainSprites;
    std::vector<sf::Sprite> addedSprites;

    bool drawingWire = false;
    sf::Vertex wire[2];
    Pin *selectedPins[2];

    // Adding menu sprites
    mainSprites.push_back(start);
    mainSprites.push_back(stop);
    mainSprites.push_back(andGate.sprite);
    mainSprites.push_back(orGate.sprite);
    mainSprites.push_back(notGate.sprite);
    mainSprites.push_back(xorGate.sprite);
    mainSprites.push_back(dFlipFlop.sprite);
    mainSprites.push_back(logicOne.sprite);
    mainSprites.push_back(gnd.sprite);
    mainSprites.push_back(led.sprite);
    mainSprites.push_back(clock.sprite);

    // for (int j = 0; j < mainSprites.size(); j++)
    // {
    //     std::cout << j << std::endl;
    //     std::cout << mainSprites[j].getGlobalBounds().width << std::endl;
    //     std::cout << mainSprites[j].getGlobalBounds().height << std::endl;
    // }
    
    // Main loop
    while (window.isOpen())
    {
        sf::Event event;

        // Detect event
        while (window.pollEvent(event))
        {
            window.clear();
            // window.draw(background);
            
            // Drawing menu objects
            for (int i = 0; i < mainSprites.size(); i++)
                window.draw(mainSprites[i]);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Detecting mouse click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                // Left click
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Detecting if the user clicked on the start or stop buttons
                    if(start.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && !isSimulating) isSimulating = true;
                    else if(stop.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && isSimulating) isSimulating = false;

                    // Detecting if the user clicked on a menu object
                    for (int i = 0; i < menuObjects.size(); i++)
                    {
                        if (menuObjects[i]->getSprite().getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                        {
                            selected = menuObjects[i];
                            selectedSprite = selected->getSprite();
                            draggingObject = true;
                            // std::cout << floatrect.top << " " << floatrect.left << " " << floatrect.width << " " << floatrect.height << std::endl;

                            std::cout << "Selected object" << std::endl;

                            break;
                        }
                    }

                    // Detecting if the user clicked on a logic element in the simulation
                    for (int j = 0; j < sim.getLogicElements().size(); j++)
                    {
                        if (sim.getLogicElements()[j]->getSprite().getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                        {
                            std::cout << "Clicked a placed element" << std::endl;
                            selectedIdx = j;

                            bool clickedPin = false;
                            
                            // Detecting if the user clicked on a pin, if so, draw a wire from that pins
                            for (int k = 0; k < sim.getLogicElements()[j]->getNumPins(); k++)
                            {
                                if (sim.getLogicElements()[j]->getPins()[k].rect.contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                                {
                                    std::cout << "Selected pin" << std::endl;

                                    clickedPin = true;

                                    if (!drawingWire)
                                    {
                                        selectedPins[0] = &sim.getLogicElements()[j]->getPins()[k];
                                        drawingWire = true;
                                    }
                                    else
                                    {
                                        selectedPins[1] = &sim.getLogicElements()[j]->getPins()[k];
                                        drawingWire = false;

                                        Wire *w = new Wire(selectedPins[0], selectedPins[1]);
                                        // sim.addWire(w);
                                        sim.updateWires();
                                    }

                                    wire[0] = sf::Vertex(sf::Vector2f(sim.getLogicElements()[j]->getPins()[k].rect.left + 8, sim.getLogicElements()[j]->getPins()[k].rect.top + 5));
                                    wire[1] = sf::Vertex(sf::Vector2f(mouse.getPosition(window).x, mouse.getPosition(window).y));

                                    break;
                                }
                            }

                            // If the user didn't click on a pin, then the user clicked on the element itself
                            if (!clickedPin && !drawingWire)
                            {
                                selected = sim.getLogicElements()[j];
                                selectedSprite = selected->getSprite();
                                draggingObject = true;
                                relocatingObject = true;
                            }

                            break;
                        }
                    }
                }
            }

            // Detecting mouse release
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                // Creating a copy of a logic element from the menu to the simulation
                if (selected != nullptr && !relocatingObject && draggingObject)
                {
                    draggingObject = false;
                    // Create new object
                    sim.addLogicElement(selected->createNewLogicElement(mouse));

                    addedSprites.push_back(selectedSprite);
                }

                // Relocating a logic element in the simulation
                else if (relocatingObject)
                {
                    draggingObject = false;
                    selected->setPos(mouse.getPosition(window).x - selectedSprite.getLocalBounds().width / 2, mouse.getPosition(window).y - selectedSprite.getLocalBounds().height / 2);
                    selected->getSprite().setPosition(mouse.getPosition(window).x - selectedSprite.getLocalBounds().width / 2, mouse.getPosition(window).y - selectedSprite.getLocalBounds().height / 2);
                    selected->configurePins();
                    relocatingObject = false;
                }

                if (draggingObject || relocatingObject)
                    selected = nullptr;
                // std::cout << "Dragging stopped" << std::endl;
            }

            // Dragging the object sprite
            if (draggingObject)
            {
                selectedSprite.setPosition(mouse.getPosition(window).x - selectedSprite.getLocalBounds().width / 2, mouse.getPosition(window).y - selectedSprite.getLocalBounds().height / 2);
                // addedSprites.push_back(selectedSprite);
                window.draw(selectedSprite);
                // std::cout << "Dragging" << std::endl;
            }

            // Drawing the wire
            if (drawingWire)
            {
                // std::cout << "Drawing wire" << std::endl;
                wire[1] = sf::Vertex(sf::Vector2f(mouse.getPosition(window).x, mouse.getPosition(window).y));
                window.draw(wire, 20, sf::Lines);
            }

            // Canceling the wire drawing
            if (drawingWire && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                drawingWire = false;

            if (selected != nullptr)
            {
                // Select the logic element in the simulation with red rectangle
                if (selectedIdx != -1)
                {
                    selectionRect.setSize(sf::Vector2f(selected->getSprite().getLocalBounds().width, selected->getSprite().getLocalBounds().height));
                    selectionRect.setPosition(selected->getSprite().getPosition());
                    window.draw(selectionRect);
                }

                // Delete the logic element in the simulation
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
                {
                    if (selectedIdx != -1)
                    {
                        sim.deleteLogicElement(selectedIdx);
                        sim.updateWires();
                        selectedIdx = -1;
                        selected = nullptr;
                    }
                }

                // Cancelling the selection of a logic element
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    if (selectedIdx != -1)
                    {
                        selectedIdx = -1;
                        selected = nullptr;
                    }
                }
            }
        }

        // If simulation is running, update the simulation
        if (isSimulating){
            sim.simulate();
        }

        // Drawing the simulation
        for (int i = 0; i < sim.getLogicElements().size(); i++)
        {
            window.draw(sim.getLogicElements()[i]->getSprite());
        }

        // Drawing the wires
        for (int i = 0; i < sim.getWires().size(); i++)
        {
            sim.getWires()[i]->updateWirePos();
            window.draw(sim.getWires()[i]->line, 20, sf::Lines);
        }        

        window.display();
    }
    return 0;
}
