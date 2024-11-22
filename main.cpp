#include <SFML/Graphics.hpp>
#include <iostream>

const std::string ASSETS_PATH = "#";
// Blocks:
//  air: 0
//  dirt: 1

const int WORLD_HEIGHT = 27;
const int WORLD_WIDTH = 50;
const int TILE_SIZE = 18;
const int WINDOW_WIDTH = WORLD_WIDTH * TILE_SIZE;
const int WINDOW_HEIGHT = WORLD_HEIGHT * TILE_SIZE;
int world[WORLD_HEIGHT][WORLD_WIDTH];


void generate_world(int world[WORLD_HEIGHT][WORLD_WIDTH])
{
    int air_generation_end = floor(WORLD_HEIGHT/2); // Height index at which air will stop generating
    int dirt_generation = floor(WORLD_HEIGHT/2); // Height index at which generation of dirt will start
    for (int i = 0; i < WORLD_HEIGHT; i++)
    {
        for (int j = 0; j < WORLD_WIDTH; j++)
        {
            if(i<air_generation_end)
            {
                world[i][j] = 0; // Generate air
            }
            else if (i>dirt_generation)
            {
                world[i][j] = 1; // Start generating dirt
            }
        }
    }
}

void render_world(sf::RenderWindow& window,int world[WORLD_HEIGHT][WORLD_WIDTH], sf::Sprite air, sf::Sprite dirt)
{
    sf::Sprite current_sprite;
    for (int i = 0; i < WORLD_HEIGHT; i++)
    {
        for (int j = 0; j < WORLD_WIDTH; j++)
        {
            if (world[i][j] == 0) {
                current_sprite = air;
            }
            else if (world[i][j] == 1) {
                current_sprite = dirt;
            }
            current_sprite.setPosition(j*TILE_SIZE, i*TILE_SIZE);
            window.draw(current_sprite);
        }
    }
}

void put_block(int world[WORLD_HEIGHT][WORLD_WIDTH], int y, int x, int block)
{
    if (world[y][x] == 0 && x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT) {
        world[y][x] = block; // Change element at (y,x) to block
    }
}

void break_block(int world[WORLD_HEIGHT][WORLD_WIDTH], int y, int x)
{
    if (x >= 0 && x < WORLD_WIDTH && y >= 0 && y < WORLD_HEIGHT) {
        world[y][x] = 0; // Remove block at (y,x), i.e. replace it with air
    }
}

int main()
{
    sf::Texture air_texture;
    sf::Texture dirt_texture;
    if(!air_texture.loadFromFile(ASSETS_PATH +"/air.png") || !dirt_texture.loadFromFile(ASSETS_PATH+ "/dirt.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    sf::Sprite air_sprite;
    sf::Sprite dirt_sprite;
    air_sprite.setTexture(air_texture);
    dirt_sprite.setTexture(dirt_texture);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "World Generator", sf::Style::Titlebar | sf::Style::Close);
    generate_world(world);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x = (pos.x / TILE_SIZE);
            int y = (pos.y / TILE_SIZE);
            break_block(world, y, x);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);
            int x = (pos.x / TILE_SIZE);
            int y = (pos.y / TILE_SIZE);
            put_block(world, y, x, 1);
        }

        window.clear();
        // Draw here
        render_world(window, world, air_sprite, dirt_sprite);
        window.display();
    }
}