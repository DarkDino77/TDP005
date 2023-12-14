 #include <SFML/Graphics.hpp>

/**
 * Steg 0: Skapa ett fönster
 *
 * Kompilera med:
 * g++ step00.cpp -lsfml-system -lsfml-graphics -lsfml-window
 */


const size_t width = 1024;
const size_t height = 768;

int main()
 {
     // Create the main window
     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
 
     // Start the game loop
     while (window.isOpen())
     {
         // Process events
         sf::Event event;
         while (window.pollEvent(event))
         {
             // Close window : exit
             if (event.type == sf::Event::Closed)
                 window.close();
         }
 
         // Clear screen
         window.clear();
 
         // Update the window
         window.display();
     }
 
     return EXIT_SUCCESS;
 }