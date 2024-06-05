#include <Wt/WApplication.h>
#include "Wordle.h"

/**
     * @brief Main method to start Wordle game.
     * @return the environment of the Wordle game.
     */
int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<Wordle>(env);
    });
}