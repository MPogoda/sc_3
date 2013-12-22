#pragma once
#include <deque>
#include <string>

namespace sc3
{
struct KnapsackItem
{
    std::string name;
    uint64_t    cost; // cost to store
    uint64_t    value; // value (the more the better)
}; // struct KnapsackItem

// compares (value / cost) of two items.
bool operator<( const KnapsackItem& lhs, const KnapsackItem& rhs );

struct KnapsackProblem
{
    std::deque< KnapsackItem > items; // expect items to be sorted
    uint64_t                   max_cost;
}; // struct KnapsackProblem

class KnapsackSolution
{
public:
    typedef std::deque< bool > Genome;
    typedef uint64_t Fitness;
private:
    Genome genome_;
    const KnapsackProblem& problem_;
    Fitness fitness_;

    // calculate fitness of genome
    Fitness calculate_fitness() const;

    // adjust genome so its fitness becomes > 0
    // simply removes items with the lowest (value/cost) ratio.
    void fit();
public:
    // reference to stored genome
    const Genome& genome() const;
    Fitness fitness() const;

    // for every bit mutate it if rand( 0, size() ) < mutation_probability
    void mutate( uint64_t mutation_probability );

    // create with random genome
    KnapsackSolution( const KnapsackProblem& problem );
    // create with given genome
    KnapsackSolution( const KnapsackProblem& problem, Genome&& genome );

    void swap( KnapsackSolution& other );
}; // class KnapsackSolution

// compares by fitness
bool operator<( const KnapsackSolution& lhs, const KnapsackSolution& rhs);
} // namespace sc3
