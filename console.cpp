#include <iostream>

// Blocks:
//  air: 0
//  dirt: 1


const int WORLD_HEIGHT = 27;
const int WORLD_WIDTH = 50;


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

void render_world(int world[WORLD_HEIGHT][WORLD_WIDTH])
{
    for (int i = 0; i < WORLD_HEIGHT; i++)
    {
        for (int j = 0; j < WORLD_WIDTH; j++)
        {
            std::cout << world[i][j];
        }
        std::cout << "\n";
    }
}

void put_block(int world[WORLD_HEIGHT][WORLD_WIDTH], int y, int x, int block)
{
    world[y][x] = block; // Change element at (y,x) to block
}

void break_block(int world[WORLD_HEIGHT][WORLD_WIDTH], int y, int x)
{
    world[y][x] = 0; // Remove block at (y,x), i.e. replace it with air
}


int main()
{
    int world[WORLD_HEIGHT][WORLD_WIDTH];
    generate_world(world);
    render_world(world);
    std::cout << "------------------------------------------------------------" << "\n";
    put_block(world,14,0,2);
    render_world(world);
    std::cout << "------------------------------------------------------------" << "\n";
    break_block(world,14,0);
    render_world(world);
    std::cout << "------------------------------------------------------------" << "\n";
    return 0;
}