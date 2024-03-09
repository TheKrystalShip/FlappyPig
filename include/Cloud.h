#ifndef __TKS_FLAPPYPIG_CLOUD_H__
#define __TKS_FLAPPYPIG_CLOUD_H__

#include <SFML/Graphics.hpp>

#include <vector>

namespace TKS::FlappyPig
{
    class Cloud : public sf::Drawable
    {
    public:
        Cloud() = default;
        Cloud(sf::Texture &texture, bool initial = false);

        void update();
        bool isOffScreen();

    private:
        int _widthInPx{128};
        int _heightInPx{64};
        float _velocityX{0.f};
        sf::Sprite _sprite;
        sf::Texture _texture;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Clouds : public sf::Drawable
    {
    public:
        Clouds();
        void init();
        void update();
        void addCloud();

    private:
        std::vector<TKS::FlappyPig::Cloud> _clouds;
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
} // namespace TKS::FlappyPig

#endif // __TKS_FLAPPYPIG_CLOUD_H__
