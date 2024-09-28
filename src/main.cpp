#include <SFML/Graphics.hpp>
#include <iostream>

#include "../include/ecs.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Quantum Game");

    ECS ecs;
    auto entity = ecs.createEntity();
    ecs.addComponent(entity, TestComponent{12});

if (ecs.hasComponent<TestComponent>(entity)) {
    auto& testComponent = ecs.getComponent<TestComponent>(entity);
    std::cout << "TestComponent testValue: " << testComponent.testValue << "\n";
}

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}
