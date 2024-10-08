#include <SFML/Graphics.hpp>
#include <headers/sampler.hpp>
#include <headers/objectfactory.hpp>
#include <optional>

#pragma once

namespace sf {

enum SpawnerUpdate{
    NO_UPDATE,
    ACTIVE_TEXTURE,
    INACTIVE_TEXTURE
};

struct SpawnerData {
    Vector2f position;
    float delay;
    float offset;
    float minSpeed;
    float maxSpeed;
    float startTime;
    float endTime;
};

template<typename enemy>
class Spawner{

protected:
    bool active = false;
    bool spawnable = false;

    float m_startTime;
    float m_endTime;

    float m_offset;
    float m_delay;
    float m_enemyMinSpeed;
    float m_enemyMaxSpeed;
    float timeUntilNextSpawn;

    Vector2f m_position;

public:
    Sprite m_spawnerSprite;

protected:
    virtual enemy spawn(Sampler& sampler) = 0;

public:

    Spawner(){}

    /// @param delay required in seconds
    Spawner(const SpawnerData &data) {
        m_position = data.position;
        m_offset = data.offset;
        m_delay = data.delay;
        timeUntilNextSpawn = m_delay;
        m_enemyMinSpeed = data.minSpeed;
        m_enemyMaxSpeed = data.maxSpeed;
        m_startTime = data.startTime;
        m_endTime = data.endTime;
    }

    std::optional<enemy> spawnEnemy(Sampler& sampler) {
        if(!spawnable)
            return {};
        spawnable = false;
        return spawn(sampler);
    }

    /// @brief deltaTime and playTime required in seconds
    SpawnerUpdate update(const float deltaTime, const float playTime){
        bool nowActive = playTime >= m_startTime && playTime < m_endTime;
        if(!active && nowActive) {
            active = true;
            return ACTIVE_TEXTURE;
        } else if (active && !nowActive) {
            active = false;
            return INACTIVE_TEXTURE;
        }
        if(active && nowActive) {
            timeUntilNextSpawn -= deltaTime;
            if(timeUntilNextSpawn <= 0){
                timeUntilNextSpawn = m_delay;
                spawnable = true;
            }
        }
        return NO_UPDATE;
    }

    bool isActive() { return active; }

};

//------------------- CircularSpawner --------------------

class CircularSpawner : public Spawner<CircleEnemy> {

protected:
    Color m_color;
    float m_minRadius;
    float m_maxRadius;

protected:
    CircleEnemy spawn(Sampler& sampler) override;

public:
    CircularSpawner(){}
    CircularSpawner(const SpawnerData &data, const float minRadius, const float maxRadius, const Color color = Color::Black);
};

//------------------- RectangularSpawner --------------------

class RectangularSpawner : public Spawner<RectangleEnemy> {

protected:
    Color m_color;
    float m_minWidth;
    float m_maxWidth;
    float m_minHeight;
    float m_maxHeight;

protected:
    RectangleEnemy spawn(Sampler& sampler) override;

public:
    RectangularSpawner(){}
    RectangularSpawner(const SpawnerData &data, const float minWidth, const float maxWidth, const float minHeight, const float maxHeight, const Color color = Color::Black);
    
};

}

 
 