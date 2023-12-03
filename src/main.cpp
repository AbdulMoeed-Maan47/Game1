#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

// Initializing dimensions
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX;    // Total number of rows i.e. i
const int gameColumns = resolutionY / boxPixelsY; // Total number of columns i.e. j
int gameGrid[gameRows][gameColumns] = {};         // Initializing Game Grid i.e. 2D array

// Initializing constants for player and bullet position at the start of every game
const int x = 0;
const int y = 1;
const int exists = 2; // bool 2=1=true

// Declaring functions
void drawPlayer(sf::RenderWindow &window, float player[], sf::Sprite &playerSprite);
void moveBullet(float bullet[], sf::Clock &bulletClock);
void drawBullet(sf::RenderWindow &window, float bullet[], sf::Sprite &bulletSprite);

int main()
{
    srand(time(0));

    // Declaring RenderWindow
    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);
    sf::Event event;

    // Used to position your window on every launch
    window.setPosition(sf::Vector2i(100, 0));

    // Initializing Background Music.
    sf::Music bgMusic;
    bgMusic.openFromFile("Game1/assets/Music/field_of_hopes.ogg");
    bgMusic.play();
    bgMusic.setVolume(50);

    // Initializing Background.
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    backgroundTexture.loadFromFile("Game1/assets/Textures/background.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.20)); // Reduces Opacity to 25%

    // Initializing Player and Player Sprites.
    float player[2] = {};
    player[x] = (gameColumns / 2) * boxPixelsX;
    player[y] = (gameColumns * 3 / 4) * boxPixelsY;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    playerTexture.loadFromFile("assets/Textures/player.png");
    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    // Initializing Bullet and Bullet Sprites.
    float bullet[3] = {};
    bullet[x] = player[x];
    bullet[y] = player[y] - boxPixelsY;
    bullet[exists] = true;
    sf::Clock bulletClock;
    sf::Texture bulletTexture;
    sf::Sprite bulletSprite;
    bulletTexture.loadFromFile("assets/Textures/bullet.png");
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

    // Game Loop
    while (window.isOpen())
    {
        window.draw(backgroundSprite);
        drawPlayer(window, player, playerSprite);
        if (bullet[exists] == true)
        {
            moveBullet(bullet, bulletClock);
            drawBullet(window, bullet, bulletSprite);
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        // window.clear();

        window.display();
    }
}

// Defining Functions
void drawPlayer(sf::RenderWindow &window, float player[], sf::Sprite &playerSprite)
{
    playerSprite.setPosition(player[x], player[y]);
    window.draw(playerSprite);
}
void moveBullet(float bullet[], sf::Clock &bulletClock)
{
    if (bulletClock.getElapsedTime().asMilliseconds() < 20)
        return;

    bulletClock.restart();
    bullet[y] -= 10;
    if (bullet[y] < -32)
        bullet[exists] = false;
}
void drawBullet(sf::RenderWindow &window, float bullet[], sf::Sprite &bulletSprite)
{
    bulletSprite.setPosition(bullet[x], bullet[y]);
    window.draw(bulletSprite);
}
