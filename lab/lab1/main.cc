#include <SFML/Graphics.hpp>

int main () 
{
    sf::RenderWindow window{sf::VideoMode (1024 , 768) , "Hello World!"};

    while(!closed)
    {
        Event event;
        while(pollEvent(event))
        {
            processEvent(event)
        }
        update()
    }
    // Vänta i 5 sekunder , så att vi hinner se fönstret .
    sf::sleep(sf::seconds (5));

    return 0;
}