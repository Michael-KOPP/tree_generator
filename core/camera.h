#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "core/defs.h"

enum camera_movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class camera {
public:
    camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), real yaw = -90.0f, real pitch = 0.0f);
    glm::mat4 get_view_matrix();
    void process_keyboard(camera_movement direction, real delta_time);
    void process_mouse_movement(real xoffset, real yoffset, bool constrain_pitch = true);

private:
    glm::vec3 position_;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    real yaw_;
    real pitch_;
    real movement_speed;
    real mouse_sensitivity;

    void update_camera_vectors();
};
