//
// Created by loic on 18/04/2020.
//

#ifndef LD46_POST_EFFECT_HPP
#define LD46_POST_EFFECT_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class PostEffect : sf::NonCopyable
{
public:
    virtual ~PostEffect();

    virtual void apply(const sf::RenderTexture& input, sf::RenderTarget& output) = 0;

    static bool isSupported();

protected:
    static void applyShader(const sf::Shader& shader, sf::RenderTarget& output);
};


#endif //LD46_POST_EFFECT_HPP
