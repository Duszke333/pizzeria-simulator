#include "read.h"
#include "Simulation.h"


int main(int argc, char* argv[])
{
    // [1] - menu contents, [2] - how many rounds
    // Suggestion - take also number of tables: for example [3] == 5 -> 5 small, 5 standard and 5 big tables are created
    if (argc < 3) {
        std::cerr << "Incorrect number of arguments." << std::endl;
        return 1;
    }

    Read reader(argv[1]);
    Menu menu = reader.get_menu();

    size_t time = std::stoul(argv[2]);

    Simulation sim(time);
    sim.start();
}