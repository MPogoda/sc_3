#include "knapsack_solver.h"
#include "knapsack.h"
#include <algorithm>
#include <iterator>
#include <iostream>

namespace sc3
{
KnapsackSolver::KnapsackSolver( const KnapsackProblem& problem, const uint64_t pop_size )
    : population_size_{ pop_size }
    , recombination_probability_{ 70 }
    , mutatuion_probability_{ 2 }
    , max_generations_{ 100 }
    , max_generations_without_improvement_{ 25 }
    , two_point_crossover_{ false }
    , problem_( problem )
    , population_( population_size_, problem_ )
{
}

KnapsackSolution KnapsackSolver::current_best() const
{
    return *std::max_element( population_.begin(), population_.end() );
}

KnapsackSolution KnapsackSolver::current_worst() const
{
    return *std::min_element( population_.begin(), population_.end() );
}

const KnapsackSolution& KnapsackSolver::select_parent() const
{
    std::random_device rd;
    std::default_random_engine engine;
    std::uniform_int_distribution< uint64_t > dist{0, problem_.items.size() };

    auto& candidate1 = population_[ dist( engine ) ];
    auto& candidate2 = population_[ dist( engine ) ];

    return (candidate2 < candidate1) ? candidate1 : candidate2;
}

std::pair< KnapsackSolution, KnapsackSolution >
KnapsackSolver::do_crossover(const KnapsackSolution& parent1, const KnapsackSolution& parent2 ) const
{
    std::random_device rd;
    std::default_random_engine engine;
    std::uniform_int_distribution< uint64_t > dist{0, problem_.items.size() - 1 };

    KnapsackSolution::Genome genome1( problem_.items.size() );
    KnapsackSolution::Genome genome2( problem_.items.size() );

    if (two_point_crossover_) {
    } else {
        uint64_t crossover_point = dist( engine );

        auto& parent1genome = parent1.genome();
        auto& parent2genome = parent2.genome();

        auto parIter1end = parent1genome.begin(); std::advance( parIter1end, crossover_point );
        auto parIter2end = parent2genome.begin(); std::advance( parIter2end, crossover_point );

        auto offIter1cr = genome1.begin(); std::advance( offIter1cr, crossover_point );
        auto offIter2cr = genome2.begin(); std::advance( offIter2cr, crossover_point );

        std::copy( parent1genome.begin(), parIter1end, genome1.begin() );
        std::copy( parIter2end, parent2genome.end(), genome1.begin() );

        std::copy( parent2genome.begin(), parIter2end, genome2.begin() );
        std::copy( parIter1end, parent1genome.end(), genome2.begin() );
    }

    return std::make_pair( KnapsackSolution( problem_, std::move( genome1 ) )
                         , KnapsackSolution( problem_, std::move( genome2 ) )
            );

}

std::pair< KnapsackSolution, KnapsackSolution >
KnapsackSolver::get_offspring() const
{
    const auto& parent1 = select_parent();
    const auto& parent2 = select_parent();

    std::random_device rd;
    std::default_random_engine engine;
    std::uniform_int_distribution< int > dist{ 0, 100 };

    int test = dist( engine );

    if (test < recombination_probability_ ) {
        return do_crossover( parent1, parent2 );
    } else {
        return std::make_pair( parent1, parent2 );
    }
}

KnapsackSolver::Population KnapsackSolver::next_generation() const
{
    Population new_population{};
    while( new_population.size() < population_size_ ) {
        auto offsrpings = get_offspring();

        new_population.emplace_back( std::move( offsrpings.first ) );
        new_population.emplace_back( std::move( offsrpings.second ) );
    }

    if (new_population.size() > population_size_ )
        new_population.pop_back();

    return std::move( new_population );
}

KnapsackSolution KnapsackSolver::evolve()
{
    next_generation().swap( population_ );

    for (auto& solution : population_ ) {
        solution.mutate( mutatuion_probability_ );
    }

    return current_best();
}

KnapsackSolution KnapsackSolver::run()
{
    auto best = current_best();
    uint64_t no_change{ 0 };

    generation_count_ = 0;

    while ( (no_change < max_generations_without_improvement_ )
         && (generation_count_ < max_generations_ ) ) {

        auto new_best = evolve();

        if (new_best < best) {
            ++no_change;
        } else {
            no_change = 0;
            best.swap( new_best );
        }

        const long double avg_fitness = std::accumulate( population_.begin(), population_.end()
                                                 , static_cast< long double >( 0 )
                                                 ,
                        [] ( const long double lhs, const KnapsackSolution& rhs )
                        {
                            return lhs + static_cast< long double >( rhs.fitness() );
                        }
                ) / static_cast< long double >( population_size_ );

        auto worst = current_worst().fitness();

        std::cout << "Best: " << best.fitness() << "; ";
        std::cout << "Avg:  " << avg_fitness << "; ";
        std::cout << "Worst: " << worst << std::endl;

        ++generation_count_;
    }

    return std::move( best );
}

} // namespace sc3
