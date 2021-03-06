#ifndef RESOURCE_IDENTIFIERS_H
#define RESOURCE_IDENTIFIERS_H

// Forward declarations
namespace sf
{
    class Texture;
    class Font;
    class Shader;
    class Music;
    class SoundBuffer;
}

template <typename Resource, typename Identifier>
class ResourceHolder;



// Textures
namespace Textures
{
    enum ID
    {
        Particle,
        ParticleStar,
        Tiles,
        TilesFull,
        Player,
        Ui,
        MenuBackground,
        TitleBackground,
        WaterCan,
        Star,
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;


// Fonts
namespace Fonts
{
    enum ID
    {
        Main,
        Title
    };
}

typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;


// Shaders
namespace Shaders
{
    enum ID
    {
        BrightnessPass,
        DownSamplePass,
        GaussianBlurPass,
        AddPass
    };
}
typedef ResourceHolder<sf::Shader, Shaders::ID> ShaderHolder;


// Musics
namespace Musics
{
    enum ID
    {
        Main,
    };
}


// Sounds
namespace Sounds
{
    enum ID
    {
        Water,
        FieldUpgrade,
        FieldUpgradeFinal,
        FieldDecay,
        Fill,
        Select,
        Validate,
    };
}
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;


// Scripts
namespace Scripts
{
    enum ID
    {
        HelloWorld
    };
}



#endif // RESOURCE_IDENTIFIERS_H
