#ifndef RANDOMMOVEALGORITHM_HPP
#define RANDOMMOVEALGORITHM_HPP

#include "./MoveAlgorithm.hpp"
#include "Controllers/PseudoRandomGenerator.hpp"
#include "MapElements/MapInstance.hpp"

class RandomMoveAlgorithm : public MoveAlgorithm
{
protected:
    MapInstanceConstPtr m_map_instance;

private:
    PseudoRandomGeneratorConstPtr m_random_generator;
    static size_t counter;

public:
    RandomMoveAlgorithm( MapInstanceConstPtr map_instance, PseudoRandomGeneratorConstPtr random_generator );
    virtual MapPosition get_next_move( const MapPosition& current_pos ) const override;
};

#endif // RANDOMMOVEALGORITHM_HPP
