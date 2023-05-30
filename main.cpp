#include "read.h"
#include "Simulation.h"
#include <array>
#include <utility>
#include "bad_file_exception.h"
#include "missing_data_exception.h"

int main(int argc, char* argv[])
{
    // [1] - menu contents, [2] - how many rounds
    if (argc < 7) {
        std::cerr << "Incorrect number of arguments." << std::endl;
        return 1;
    }

    try {
        size_t time = std::stoul(argv[2]);
        if (time == 0) throw std::invalid_argument("2");
        int small_tables = std::atoi(argv[3]);
        if (small_tables <= 0) throw std::invalid_argument("3");
        int standard_tables = std::atoi(argv[4]);
        if (standard_tables <= 0) throw std::invalid_argument("4");
        int big_tables = std::atoi(argv[5]);
        if (big_tables <= 0) throw std::invalid_argument("5");
        int waiters = std::atoi(argv[6]);
        if (waiters <= 0) throw std::invalid_argument("6");
        Read reader(argv[1]);
        const Menu &menu = reader.get_menu();

        // argv[3] = amount of small tables, [4] = standard, [5] = big
        std::array<std::pair<int, TableSize>, 3> tables = {
            std::make_pair<int, TableSize>(std::atoi(argv[3]), TableSize::small),
            std::make_pair<int, TableSize>(std::atoi(argv[4]), TableSize::standard),
            std::make_pair<int, TableSize>(std::atoi(argv[5]), TableSize::big),

        };

        // argv[6] amount of waiters

        Simulation sim(time, menu, tables, waiters);
        sim.start();
    }
    catch (const BadFileException& e) {
        std::cerr << "File not found." << std::endl;
        return 2;
    }
    catch (const MissingDataException& e) {
        std::cerr << "Missing data in file." << std::endl;
        return 3;
    }
    catch (const std::invalid_argument &e) {
        std::cerr << "Invalid argument no. " << e.what() << std::endl;
        return 4;
    }
}