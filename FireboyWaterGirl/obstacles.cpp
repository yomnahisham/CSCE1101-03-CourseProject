#include "obstacles.h"

// Pavement, Fire, Water, Acid, Lever, Button, SlidingFloor, FireDoor, WaterDoor

Obstacles::Obstacles(ObstacleType type) : type(type) {
    switch (type) {
    case ObstacleType::Pavement:
        QPixmap(":/images/obstacle_type_1.png");
        break;
    case ObstacleType::Fire:
        // Special functionality for obstacle type 2
        break;
    case ObstacleType::Water:
        break;
    case ObstacleType::Acid:
        break;
    case ObstacleType::Lever:
        break;
    case ObstacleType::Button:
        break;
    case ObstacleType::SlidingFloor:
        break;
    case ObstacleType::FireDoor:
        break;
    case ObstacleType::WaterDoor:
        break;
        // Add more cases as needed
    }
}
