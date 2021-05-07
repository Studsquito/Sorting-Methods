#include <random>
#include <vector>
#include <iostream>
#include <math.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

std::vector<int> bubbleSort(std::vector<int> set, std::vector<sf::RectangleShape>* rect);
void printNumbers(std::vector<int> set);
template<typename T>
void swap(T& a, T& b);
void updateRectangle(std::vector<sf::RectangleShape>* rect, int index);

#define SIZE 50

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(1, 100);
    sf::Vector2f windowSize(750, 750);
    std::vector<int> numbers;
    std::vector<sf::RectangleShape> rect;

    for(int i = 0; i < SIZE; i++) {
        numbers.push_back(dist(gen));
        rect.push_back(sf::RectangleShape(sf::Vector2f(
            windowSize.x / SIZE,
            numbers[i] * 7)));
        rect[i].setOrigin(rect[i].getPoint(3));
        rect[i].setPosition(rect[i].getSize().x * i, windowSize.y);
        rect[i].setFillColor(sf::Color::Red);
    }

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Bubble Sort");
    window.setFramerateLimit(60);

    numbers = bubbleSort(numbers, &rect);
    printNumbers(numbers);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        for(int i = 0; i < rect.size(); i++) {
            window.draw(rect[i]);
        }
        /* for(int i = 0; i < numbers.size() - 1; i++) {
            for(int j = 0; j < numbers.size() - i - 1; j++) {
                if(numbers[j > numbers[j + 1]]) {

                }
            }
        } */

        window.display();
    }

    return 0;
}

std::vector<int> bubbleSort(std::vector<int> set, std::vector<sf::RectangleShape>* rect) {
    if(set.empty())
        throw std::runtime_error("Invalid size in bubbleSort");
    for(int i = 0; i < set.size() - 1; i++) {
        for(int j = 0; j < set.size() - i - 1; j++) {
            if(set[j] > set[j + 1])
                swap(set[j], set[j + 1]);
        }
    }

    return set;
}

void printNumbers(std::vector<int> set) {
    if(set.empty())
        throw std::runtime_error("Set is empty in printNum");

    for(int i = 0; i < set.size(); i++) {
        std::cout << set[i] << std::endl;
    }
}

template<typename T>
void swap(T& a, T& b) {
    auto temp = a;
    a = b;
    b = temp;
}