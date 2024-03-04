#ifndef __TKS_FLAPPYPIG_PLAYER_H__
#define __TKS_FLAPPYPIG_PLAYER_H__

#include <SFML/Graphics.hpp>

namespace TKS::FlappyPig
{
    class PlayerHitbox : public sf::Sprite
    {
    public:
        void setHitbox(const sf::FloatRect& hitbox);
        sf::FloatRect getGlobalHitbox() const;

    private:
        sf::FloatRect m_hitbox;
    };

    class Player : public sf::Drawable
    {
    public:
        Player() = default;
		Player(sf::Texture& texture);

        void update();
        void jump();
        void jump(const float lift);

        int getLives() const;
        void setLives(const int lives);
        void loseLife();
        void gainLife();
        TKS::FlappyPig::PlayerHitbox& getSprite();

	private:
        int m_width;
        int m_height;
        int m_lives;
        float m_velocity;
        TKS::FlappyPig::PlayerHitbox m_sprite;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig

#endif // !__TKS_FLAPPYPIG_PLAYER_H__
