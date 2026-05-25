#pragma once

#include "math/Vector2D.hpp"
#include "math/AABB.hpp"

#ifdef USE_LIST
#include "data/List.hpp"
#else
#define MAX_ENTITIES 32
#endif

namespace engine {
    namespace entities {
        class Entity;  // Forward declaration
    }

    namespace world {
        
        class Level {
        protected:
            // Flat 1D array representing the 2D map. 
            // Lowest possible memory footprint.
            char* world_m; 

            int rows_m;
            int cols_m;

#ifdef USE_LIST
            data::List<entities::Entity*> entities_list_m;
#else
            entities::Entity* entities_list_m[MAX_ENTITIES];
            int entities_count_m;
#endif

        public:
            Level(const char* map_data = nullptr, const int rows = 0, const int cols = 0);
            virtual ~Level();
        
        public:
            // Core map data access
            char get_tile(const int row, const int col) const;
            int rows() const;
            int cols() const;
            
            // Fast O(1) point-check (great for simple projectiles or raycasting)
            bool is_wall(const math::Vector2D& position) const;
            
            // Integer-hashing check for sliding entity hitboxes
            bool hitbox_overlaps_wall(const math::AABB& entity_box) const;
            
            // Forces derived classes (like Level1, Level2) to implement their own logic
            virtual void run() = 0; 
            
            void spawn_entity(entities::Entity* new_entity); 
        };
    }
}