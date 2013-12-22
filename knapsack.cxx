#include "knapsack.h"
#include <cassert>
#include <random>

namespace sc3
{
KnapsackSolution::KnapsackSolution( const KnapsackProblem& problem )
    : genome_( problem.items.size() )
    , problem_( problem )
    , fitness_{ 0 }
{
    std::random_device rd;
    std::default_random_engine engine( rd() );
    std::uniform_int_distribution< int > dist( 0, 1 );

    for (auto& gene : genome_) {
        gene = static_cast< bool>( dist( engine ) );
    }

    update_fitness();
}

KnapsackSolution::KnapsackSolution( const KnapsackProblem& problem, KnapsackSolution::Genome&& genome )
    : genome_( genome )
    , problem_( problem )
    , fitness_{ calculate_fitness() }
{
}

KnapsackSolution::Fitness KnapsackSolution::calculate_fitness() const
{
    Fitness result{};
    uint64_t cost;

    for (int i = 0; i < genome_.size(); ++i) {
        result += genome_[ i ] * problem_.items[ i ].value;
        cost  += genome_[ i ] * problem_.items[ i ].cost;
    }

    if (cost > problem_.max_cost ) {
        result = std::numeric_limits< Fitness >::min();
    }

    return result;
}

void KnapsackSolution::update_fitness()
{
    fitness_ = calculate_fitness();
}

const KnapsackSolution::Genome& KnapsackSolution::genome() const
{
    return genome_;
}

KnapsackSolution::Fitness KnapsackSolution::fitness() const
{
    return fitness_;
}

bool operator<( const KnapsackSolution& lhs, const KnapsackSolution& rhs)
{
    return lhs.fitness() < rhs.fitness();
}

void KnapsackSolution::mutate( const uint64_t mutation_probability)
{
    std::random_device rd;
    std::default_random_engine engine{ rd() };
    std::uniform_int_distribution< uint64_t > dist{0, genome_.size() };

    for (auto& gene : genome_ ) {
        if (dist( engine ) < mutation_probability )
            gene = !gene;
    }

    update_fitness();
}

void KnapsackSolution::swap( KnapsackSolution& other )
{
    assert( &problem_ == & (other.problem_ ) );

    std::swap( genome_, other.genome_ );
    std::swap( fitness_, other.fitness_ );
}

} // namespace sc3
