#pragma once

#include "SFML/Graphics.hpp"

namespace sf
{
    template<class Archive, typename T>
    void serialize(Archive& archive, sf::Vector2<T>& t)
    {
        archive(t.x, t.y);
    }

    template <class Archive>
    void serialize(Archive& archive, sf::Vector2i& v)
    {
        archive(v.x, v.y);
    }

    template <class Archive>
    void serialize(Archive& archive, const sf::Vector2i& v)
    {
        archive(v.x, v.y);
    }

    template <class Archive>
    void serialize(Archive& archive, sf::Vector2f& f)
    {
        archive(f.x, f.y);
    }

    template <class Archive>
    void serialize(Archive& archive, const sf::Vector2f& f)
    {
        archive(f.x, f.y);
    }

    template <class Archive>
    void serialize(Archive& archive, sf::Vector2u& u)
    {
        archive(u.x, u.y);
    }

    template <class Archive>
    void serialize(Archive& archive, const sf::Vector2u& u)
    {
        archive(u.x, u.y);
    }

    template <class Archive>
    void serialize(Archive& archive, sf::IntRect& r)
    {
        archive(r.left, r.top, r.width, r.height);
    }

    template <class Archive>
    void serialize(Archive& archive, const sf::IntRect& r)
    {
        archive(r.left, r.top, r.width, r.height);
    }
}