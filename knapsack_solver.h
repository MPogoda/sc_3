#pragma once
#include <deque>
#include <cstdint>
#include <memory>
#include <random>

namespace sc3
{
struct KnapsackProblem;
class KnapsackSolution;

class KnapsackSolver {
    typedef std::deque< KnapsackSolution > Population;
    uint64_t    population_size_; // 500
    uint64_t      recombination_probability_; // 70 / 100
    uint64_t    mutatuion_probability_; // 2
    uint64_t    max_generations_; // 100
    uint64_t    max_generations_without_improvement_; // 25
    bool        two_point_crossover_; // false


    std::random_device rd;
    std::default_random_engine engine;

    const KnapsackProblem& problem_;
    Population population_;
    uint64_t generation_count_;


    KnapsackSolution current_best() const;
    KnapsackSolution current_worst() const;
    const KnapsackSolution& select_parent() const;

    std::pair< KnapsackSolution, KnapsackSolution > do_crossover( const KnapsackSolution& parent1, const KnapsackSolution& parent2 ) const;

    std::pair< KnapsackSolution, KnapsackSolution > get_offspring() const;

    Population next_generation() const;

    KnapsackSolution evolve();
public:
    KnapsackSolver( const KnapsackProblem& problem, uint64_t pop_size = 500 );

    KnapsackSolution run();
}; // class KnapsackSolver

} // namespace sc3
