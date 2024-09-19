#include "CoinsController.hpp"

CoinsController::CoinsController( )
    : m_modeled_coin{ { 2, 2 } }
{
}

void
CoinsController::reset( MapInstanceConstPtr map_instance )
{
    m_map_instance = map_instance;
    reset_coins( );
}

void
CoinsController::poll( )
{
    if ( all_coins_collected( ) )
    {
        return;
    }

    const auto pos = m_collidable->get_map_position( );
    if ( !is_coin( pos ) )
    {
        return;
    }

    m_map_instance->position_object_at( m_modeled_coin, pos );
    if ( m_modeled_coin.intersects( *m_collidable ) )
    {
        m_remaining_coins--;

        m_coin_objects[ pos.row ][ pos.col ] = false;
    }
}

void
CoinsController::set_collidable( MapObjectConstPtr collidable )
{
    m_collidable = collidable;
}

void
CoinsController::reset_coins( )
{
    m_remaining_coins = 0;
    auto map_size = m_map_instance->size( );

    m_coin_objects.clear( );
    m_coin_objects.resize( map_size.height );

    for ( size_t row = 0; row < map_size.height; row++ )
    {
        m_coin_objects[ row ].resize( map_size.width );
        for ( size_t col = 0; col < map_size.width; col++ )
        {
            m_coin_objects[ row ][ col ] = !m_map_instance->is_wall( { row, col } );
            if ( m_coin_objects[ row ][ col ] )
            {
                m_remaining_coins++;
            }
        }
    }
}

bool
CoinsController::all_coins_collected( ) const
{
    return m_remaining_coins == 0;
}

bool
CoinsController::is_coin( const MapPosition& pos ) const
{
    return m_coin_objects[ pos.row ][ pos.col ];
}
