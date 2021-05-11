#include <random>
#include <iostream>
#include <math.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void bubbleSort(std::vector<int>& set, std::vector<sf::RectangleShape>& rect);
void printNumbers(std::vector<int> set);
template<typename T>
void swap(T& a, T& b);
std::string getPair(sf::Vector2f position);

#define SIZE 50
#define WINDOWSIZE 800

struct rectangles {
    sf::Vector2f position;
    int height;
} data[SIZE];

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(1, WINDOWSIZE);
    sf::RectangleShape rect;
    int iter = 0;
    int limit = SIZE - 1;

    for(int i = 0; i < SIZE; i++) {
        data[i].height = dist(gen);
        data[i].position.x = WINDOWSIZE / SIZE;
        data[i].position.y = WINDOWSIZE;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "Bubble Sort");
    window.setFramerateLimit(60);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);

        for(int i = 0; i < SIZE; i++) {
            rect.setRotation(180);
            rect.setOrigin(rect.getPoint(1));
            rect.setSize(sf::Vector2f(data[i].position.x, data[i].height));
            rect.setPosition(data[i].position.x * i, WINDOWSIZE);
            rect.setFillColor(sf::Color::White);
            rect.setOutlineColor(sf::Color::Black);
            if(data[iter].height > data[iter + 1].height)
                swap(data[iter].height, data[iter + 1].height);
            if(iter == i)
                rect.setFillColor(sf::Color::Green);
            rect.setOutlineThickness(0.75);
            window.draw(rect);
        }
        window.display();

        iter++;
        if(iter >= limit) {
            iter = 0;
            limit--;
        }
    }

    return 0;
}

void bubbleSort(std::vector<int>& set, std::vector<sf::RectangleShape>& rect) {
    if(set.empty())
        throw std::runtime_error("Invalid size in bubbleSort");
    for(int i = 0; i < set.size() - 1; i++) {
        for(int j = 0; j < set.size() - i - 1; j++) {
            if(set[j] > set[j + 1]) {
                swap(set[j], set[j + 1]);
                swap(rect[j], rect[j + 1]);
                auto temp = rect[j].getPosition();
                rect[j].setPosition(rect[j + 1].getPosition());
                rect[j + 1].setPosition(temp);
            }
        }
    }
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

std::string getPair(sf::Vector2f position) {
    return "(" + std::to_string(position.x) +
        ", " + std::to_string(position.y) + ")";
}