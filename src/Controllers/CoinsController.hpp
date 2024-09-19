#ifndef COINSCONTROLLER_HPP
#define COINSCONTROLLER_HPP

#include "MapElements/MapInstance.hpp"
#include "MapElements/MapObject.hpp"
#include "MapElements/RectObject.hpp"

class CoinsController
{
    std::vector< std::vector< size_t > > m_coin_objects;
    MapObjectConstPtr m_collidable;
    MapInstanceConstPtr m_map_instance;
    RectObject m_modeled_coin;
    size_t m_remaining_coins;

public:
    CoinsController( );

    void reset( MapInstanceConstPtr map_instance );

    void poll( );
    void set_collidable( MapObjectConstPtr collidable );
    void reset_coins( );
    bool all_coins_collected( ) const;
    bool is_coin( const MapPosition& pos ) const;
};

using CoinsControllerPtr = std::shared_ptr< CoinsController >;
using CoinsControllerConstPtr = std::shared_ptr< const CoinsController >;

#endif // COINSCONTROLLER_HPP
