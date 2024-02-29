#include "camera.h"

camera::camera(glm::vec3 position, glm::vec3 up, real yaw, real pitch):
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movement_speed(1.f),
    mouse_sensitivity(0.01f)
{
    position_ = position;
    world_up = up;
    yaw_ = yaw;
    pitch_ = pitch;
    update_camera_vectors();
}

glm::mat4 camera::get_view_matrix()
{
    return glm::lookAt(position_, position_ + front, up);
}

void camera::process_keyboard(camera_movement direction, real delta_time)
{
    real velocity = movement_speed * delta_time;
    if (direction == camera_movement::FORWARD)
        position_ += front * velocity;
    if (direction == camera_movement::BACKWARD)
        position_ -= front * velocity;
    if (direction == camera_movement::LEFT)
        position_ -= right * velocity;
    if (direction == camera_movement::RIGHT)
        position_ += right * velocity;
}

void camera::process_mouse_movement(real xoffset, real yoffset, bool constrain_pitch)
{
    xoffset *= mouse_sensitivity;
    yoffset *= mouse_sensitivity;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (constrain_pitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    update_camera_vectors();
}

void camera::update_camera_vectors()
{
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    new_front.y = sin(glm::radians(pitch_));
    new_front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front = glm::normalize(new_front);
    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}
