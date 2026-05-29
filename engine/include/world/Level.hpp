#pragma once

#include "math/AABB.hpp"

#ifdef USE_LIST
#include "data/List.hpp"
#else
#define MAX_ENTITIES 64
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
            int   rows_m;
            int   cols_m;

#ifdef USE_LIST
            data::List<entities::Entity*> entities_list_m;
#else
            entities::Entity* entities_list_m[MAX_ENTITIES];
            int entities_count_m;
#endif

        public:
            Level(
                const char* map_data = nullptr, const int rows = 0, const int cols = 0
            );
            virtual ~Level();
        
        public:
            char get_tile(const int row, const int col) const;
            int  rows() const;
            int  cols() const;
            bool is_wall(const math::Vector2D& position) const;
            bool is_wall(const math::FixedPointInt32& i, const math::FixedPointInt32& j) const;
                        
            virtual void run() = 0; 
            
            void spawn_entity(entities::Entity* new_entity); 
        };
    }
}