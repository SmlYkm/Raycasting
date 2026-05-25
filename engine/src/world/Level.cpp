#include "world/Level.hpp"

namespace engine {
    namespace world {

        Level::Level(const char* map_data, const int rows, const int cols) : 
            world_m(nullptr),
            rows_m(rows), 
            cols_m(cols),
#ifdef USE_LIST
            entities_list_m() {
#else
            entities_count_m(0) {
#endif
            // Input validation
            if (rows < 3 || cols < 3 || map_data == nullptr) {
                rows_m = 0;
                cols_m = 0;
                return;
            }

            int total_size = rows_m * cols_m;
            world_m = new char[total_size];

            for (int i = 0; i < total_size; ++i) {
                world_m[i] = map_data[i];
            }

            // Initialize the entity array if we aren't using the custom List
#ifndef USE_LIST
            for (int i = 0; i < MAX_ENTITIES; ++i) {
                entities_list_m[i] = nullptr;
            }
#endif
        }
        
        Level::~Level() {
            if (world_m != nullptr) {
                delete[] world_m;
                world_m = nullptr;
            }
        }
    
        char Level::get_tile(const int row, const int col) const {
            // Out-of-bounds safety net: 
            // If an entity glitches outside the map array, treat the void as a solid wall ('#')
            if (row < 0 || row >= rows_m || col < 0 || col >= cols_m) {
                return '#'; 
            }
            // 2D access on a 1D array: (Y * width) + X
            return world_m[row * cols_m + col];
        }

        bool Level::is_wall(const math::Vector2D& position) const {
            // Convert physical coordinates to integer grid cells
            int grid_x = position.x.floor().get_int();
            int grid_y = position.y.floor().get_int();

            char tile = get_tile(grid_y, grid_x);
            
            // Treat anything that isn't a blank space as solid geometry
            return tile != ' '; 
        }

        bool Level::hitbox_overlaps_wall(const math::AABB& entity_box) const {
            // 1. Hash the AABB corners down to the grid indices
            int min_grid_x = entity_box.topleft().x.floor().get_int();
            int min_grid_y = entity_box.topleft().y.floor().get_int();
            
            int max_grid_x = entity_box.bottomright().x.floor().get_int();
            int max_grid_y = entity_box.bottomright().y.floor().get_int();


            for (int row = min_grid_y; row <= max_grid_y; ++row) {
                for (int col = min_grid_x; col <= max_grid_x; ++col) {
                    if (get_tile(row, col) != ' ') {
                        return true;
                    }
                }
            }
            
            return false;
        }

        int Level::rows() const {
            return rows_m;
        }
        
        int Level::cols() const {
            return cols_m;
        }

        void Level::spawn_entity(entities::Entity* new_entity) {
            // Derived classes are the ones responsible allocating and
            // deallocating the entities, if they're dynamically allocated
            if (new_entity) {
#ifdef USE_LIST
                entities_list_m.insert_at_ending(new_entity);
#else
                if (entities_count_m < MAX_ENTITIES) { 
                    entities_list_m[entities_count_m++] = new_entity;
                }
#endif
            }
        }
    }
}