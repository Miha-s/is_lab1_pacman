#include "RectObject.hpp"

RectObject::RectObject( const sf::Vector2f size )
    : m_rect{ size }
{
}

void
RectObject::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
    target.draw( m_rect, states );
}

void
RectObject::set_position( const sf::Vector2f& pos )
{
    m_rect.setPosition( pos );
}

sf::FloatRect
RectObject::get_global_bounds( ) const
{
    return m_rect.getGlobalBounds( );
}
