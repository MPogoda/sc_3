#include "knapsack.h"
#include <cassert>
#include <random>
#include <algorithm>

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

    fit();
    fitness_ = calculate_fitness();
}

KnapsackSolution::KnapsackSolution( const KnapsackProblem& problem, KnapsackSolution::Genome&& genome )
    : genome_( genome )
    , problem_( problem )
    , fitness_{ 0 }
{
    fit();
    fitness_ = calculate_fitness();
}

KnapsackSolution::Fitness KnapsackSolution::calculate_fitness() const
{
    Fitness result{ 0 };

    for (int i = 0; i < genome_.size(); ++i) {
        result += genome_[ i ] * problem_.items[ i ].value;
    }

    return result;
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

    fit();
    fitness_ = calculate_fitness();
}

void KnapsackSolution::swap( KnapsackSolution& other )
{
    assert( &problem_ == & (other.problem_ ) );

    std::swap( genome_, other.genome_ );
    std::swap( fitness_, other.fitness_ );
}

void KnapsackSolution::fit()
{
    // calculate cost
    uint64_t cost{ 0 };
    for (int i = 0; i < genome_.size(); ++i) {
        cost  += genome_[ i ] * problem_.items[ i ].cost;
    }

    // remove gene with lowest (value/cost) ratio
    // until total cost will be acceptable
    uint64_t it{ 0 };
    const uint64_t endIt = genome_.size();
    while (cost > problem_.max_cost ) {
        for ( ; !genome_[it] && (endIt != it); ++it)
            ;

        if (endIt == it) assert( false );
        genome_[ it ] = false;
        cost -= problem_.items[ it ].cost;
        ++it;
    }

}

bool operator<( const KnapsackItem& lhs, const KnapsackItem& rhs)
{
    long double lhsv = static_cast< long double >( lhs.value )/ static_cast< long double >(lhs.cost );
    long double rhsv = static_cast< long double >( rhs.value )/ static_cast< long double >( rhs.cost );

    return lhsv < rhsv;
}
} // namespace sc3
