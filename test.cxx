#include "knapsack.h"
#include "knapsack_solver.h"
#include <iostream>
#include <algorithm>

namespace sc3
{
KnapsackProblem get_problem()
{
    std::deque< KnapsackItem > items = { { "map", 9, 150 }
                                       , { "compass", 13, 35 }
                                       , { "water", 153, 200 }
                                       , { "sandwich", 50, 160 }
                                       , { "glucose", 15, 60 }
                                       , { "tin", 68, 45 }
                                       , { "banana", 27, 60 }
                                       , { "apple", 39, 40 }
                                       , { "cheese", 23, 30 }
                                       , { "beer", 52, 10 }
                                       , { "suntan cream", 11, 70 }
                                       , { "camera", 32, 30 }
                                       , { "t-shirt", 24, 15 }
                                       , { "trousers", 48, 10 }
                                       , { "umbrella", 73, 40 }
                                       , { "waterproof trousers", 42, 70 }
                                       , { "waterproof overclothes", 43, 75 }
                                       , { "note-case", 22, 80 }
                                       , { "sunglasses", 7, 20 }
                                       , { "towel",  18, 12 }
                                       , { "socks", 4, 50 }
                                       , { "book", 30, 10 }
                                       , { "notebook", 90, 1 }
                                       , { "tent", 200, 150 }
    };

    // VITAL !!! TODO
    std::sort( items.begin(), items.end() );

    KnapsackProblem problem{ items, 500 };
    std::cout << problem.max_cost << std::endl;

    return std::move( problem );
}
} // namespace sc3

int main(int argc, char const* argv[])
{
    using namespace sc3;

    KnapsackSolver solver{ get_problem() };
    solver.set_two_point_crossover(true);
    solver.run();
    return 0;
}
