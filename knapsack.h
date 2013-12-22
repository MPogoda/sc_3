#pragma once
#include <deque>
#include <string>

namespace sc3
{
struct KnapsackItem
{
    std::string name;
    uint64_t    cost;
    uint64_t    value;
}; // struct KnapsackItem

struct KnapsackProblem
{
    std::deque< KnapsackItem > items;
    uint64_t                   max_cost;
}; // struct KnapsackProblem

class KnapsackSolution
{
public:
    typedef std::deque< bool > Genome;
    typedef long double Fitness;
private:

    Genome genome_;
    const KnapsackProblem& problem_;
    Fitness fitness_;

    Fitness calculate_fitness() const;
public:
    const Genome& genome() const;
    Fitness fitness() const;
    void update_fitness();

    // mutate if rand( 0, size() ) < mutation_probability
    void mutate( uint64_t mutation_probability );

    KnapsackSolution( const KnapsackProblem& problem );
    KnapsackSolution( const KnapsackProblem& problem, Genome&& genome );
    void swap( KnapsackSolution& other );
}; // class KnapsackSolution

bool operator<( const KnapsackSolution& lhs, const KnapsackSolution& rhs);
} // namespace sc3
