#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "../../core/utils/internal-ptr.hpp"
#include <vector>
#include <unordered_map>


namespace ast
{
    /*
    * A list of all game object types
    */
    enum ObjectTypes
    {
        NONE,
        TRANSFORM_OBJECT,
        SPRITE,
        LAYER,
        PLAYER_SPAWN,
    };

    /*
    * The base class for all game objects
    */
    class GameObject : std::enable_shared_from_this<GameObject>
    {
    private:
        static unsigned int                                            _idCounter;

    protected:
        uint16_t                                                        _type;
        unsigned int                                                    _id;
        const char*                                                     _name;
        std::shared_ptr<GameObject>                                     _parent;
        std::unordered_map<const char*, std::shared_ptr<GameObject>>    _children;

    public:
        uint16_t& getType();
        const char* getName();
        unsigned int& getID();

        void setName(const char* value);
        
        virtual void setParent(std::shared_ptr<GameObject> value) = 0;
        virtual void addChild(std::shared_ptr<GameObject>& value) = 0;
        virtual void update(float dt) = 0;

        GameObject();
    };

    struct GameObjectPool
    {
        static std::unordered_map<const char*, std::shared_ptr<GameObject>> gameObjects;
    };
}

#endif