#pragma once
#include <deque>
#include <cstdint>
#include <memory>
#include <random>

#include "knapsack.h"

namespace sc3
{
class KnapsackSolver {
    typedef std::deque< KnapsackSolution > Population;
    uint64_t    population_size_; // 500
    uint64_t    recombination_probability_; // 70 / 100
    uint64_t    mutation_probability_; // 2
    uint64_t    max_generations_; // 100
    uint64_t    max_generations_without_improvement_; // 25
    bool        two_point_crossover_; // false

    const KnapsackProblem problem_;
    Population population_;
    uint64_t generation_count_;

    KnapsackSolution current_best() const;
    KnapsackSolution current_worst() const;

    // pick to random parents, and then pick the best of them.
    const KnapsackSolution& select_parent() const;

    // make a crossover of two parents.
    // return pair of offsprings
    std::pair< KnapsackSolution, KnapsackSolution >
        do_crossover( const KnapsackSolution& parent1, const KnapsackSolution& parent2 ) const;

    // pick two parents
    // pick a random number in [0;100]
    // if it is < recombination_probability_ do a crossover of parents
    // else do nothing
    std::pair< KnapsackSolution, KnapsackSolution > get_offspring() const;

    // create a whole new generation
    Population next_generation() const;

    // swap current generation with the next one,
    // returns current_best
    KnapsackSolution evolve();
public:
    KnapsackSolver( const KnapsackProblem problem, uint64_t pop_size = 500 );

    void set_population_size( uint64_t value );
    void set_recombination_probability( uint64_t value );
    void set_mutation_probability( uint64_t value );
    void set_max_generations( uint64_t value );
    void set_max_generations_without_improvement( uint64_t value );
    void set_two_point_crossover( bool value );
    KnapsackSolution run();
}; // class KnapsackSolver

} // namespace sc3
