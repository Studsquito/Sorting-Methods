#include <random>
#include <iostream>
#include <math.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void printNumbers(std::vector<int> set);
template<typename T>
void swap(T& a, T& b);

#define SIZE 20
#define WINDOWSIZE 800

struct rectangles {
    sf::Vector2f size;
    int height;
} data[SIZE];

int main(int argc, char* argv[]) {
    std::random_device rd;
    std::default_random_engine gen;
    std::uniform_int_distribution<int> dist(1, 750); // Generates a number from 1 - 750
    sf::RectangleShape rect;
    sf::Clock clock;
    sf::Time time;
    sf::Text timeText;
    sf::Text numText;
    sf::Font font;
    int iter = 0;
    int limit = SIZE - 1; // This keeps "track" of how many numbers are sorted
    bool finalTime = false; // Used to differentiate the current and final result

    // It sets the values of the height in our struct to a random value
    // The size of the rectangles are all the same, dependent on the window size and number of elements
    for(int i = 0; i < SIZE; i++) {
        data[i].height = dist(gen);
        data[i].size.x = WINDOWSIZE / SIZE;
        data[i].size.y = WINDOWSIZE;
    }

    sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "Bubble Sort");
    window.setFramerateLimit(60);

    if(!font.loadFromFile("DejaVuSans.ttf")) {
        exit(-1);
    }

    timeText.setFont(font);
    timeText.setFillColor(sf::Color::Green);
    timeText.setCharacterSize(24);
    numText.setFont(font);
    numText.setFillColor(sf::Color::Green);
    numText.setCharacterSize(24);

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event))
            if(event.type == sf::Event::Closed)
                window.close();

        window.clear(sf::Color::Black);
        numText.setString("n: " + std::to_string(SIZE));
        numText.setPosition(0, 25);
        window.draw(numText);
        // Still sorting....
        if(!finalTime) {
            // This entire block is to display the time
            time = clock.getElapsedTime();
            timeText.setString(std::to_string(time.asSeconds()) + " seconds");
            window.draw(timeText);
            for(int i = 0; i < SIZE; i++) {
                rect.setRotation(180); // Without this line, rectangles would be upside down
                rect.setOrigin(rect.getPoint(1));
                rect.setSize(sf::Vector2f(data[i].size.x, data[i].height));
                rect.setPosition(data[i].size.x * i, WINDOWSIZE);
                rect.setFillColor(sf::Color::White);
                rect.setOutlineColor(sf::Color::Black);
                // If one is higher than the other, swap them.
                if(data[iter].height > data[iter + 1].height)
                    swap(data[iter].height, data[iter + 1].height);
                // iter keeps track of what rectangle the program is currently on
                if(iter == i)
                    rect.setFillColor(sf::Color::Green);
                rect.setOutlineThickness(0.75);
                window.draw(rect);
            }
        }
        // Finished sorting
        else if(finalTime) {
            timeText.setString(std::to_string(time.asSeconds()) + " seconds");
            window.draw(timeText);
            for(int i = 0; i < SIZE; i++) {
                rect.setRotation(180);
                rect.setOrigin(rect.getPoint(1));
                rect.setSize(sf::Vector2f(data[i].size.x, data[i].height));
                rect.setPosition(data[i].size.x * i, WINDOWSIZE);
                rect.setFillColor(sf::Color::White);
                rect.setOutlineColor(sf::Color::Black);
                rect.setOutlineThickness(0.75);
                window.draw(rect);
            }
        }

        window.display();

        iter++; // Current rectangle
        // If the iterator is greater than the limit, it is done sorting for this round.
        // Set it equal to 0 and decrement limit, some of the rectangles would be sorted
        // at this point.
        if(iter >= limit) {
            iter = 0;
            limit--;
        }
        // Lets the program know that it is finished sorting.
        if(limit == 0) {
            finalTime = true;
            time = clock.getElapsedTime();
            clock.restart();
        }
    }

    return 0;
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
