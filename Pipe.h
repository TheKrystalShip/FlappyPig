#ifndef __TKS_FLAPPYPIG_PIPE_H__
#define __TKS_FLAPPYPIG_PIPE_H__

#include "Player.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <functional>

namespace TKS::FlappyPig
{
    class PipeHitbox : public sf::Sprite
    {
    public:
        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect m_hitbox;
    };

    class Pipe : public sf::Drawable
    {
    public:
        Pipe() = default;
        Pipe(sf::Texture &texture);

        void update();
        bool isOffscreen() const;
        bool collides(TKS::FlappyPig::PlayerHitbox& obj);

    private:
        int m_width;
        int m_height;
        float m_velocity;
        bool m_collided;
        TKS::FlappyPig::PipeHitbox m_topPipe;
        TKS::FlappyPig::PipeHitbox m_bottomPipe;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };

    class Pipes : public sf::Drawable
    {
    public:
        Pipes();
        void init();
        void update(std::function<void(void)> scoreCallback, std::function<void(void)> collisionCallback, TKS::FlappyPig::Player& player);
        void addPipe();
    private:
        std::vector<TKS::FlappyPig::Pipe> m_pipes;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig

#endif // !__TKS_FLAPPYPIG_PIPE_H__
