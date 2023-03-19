#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraFrontDirection = glm::normalize(cameraPosition - cameraTarget);
        this->cameraRightDirection = glm::normalize(glm::cross(cameraUp, this->cameraFrontDirection));
        this->cameraUpDirection = glm::cross(this->cameraFrontDirection, this->cameraRightDirection);
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    glm::vec3 Camera::getCameraTarget()
    {
        return cameraTarget;
    }

    //update the camera internal parameters following a camera move event  
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        
        glm::vec3 vec = glm::vec3(0.0f);

        switch (direction) {
            case MOVE_FORWARD:
                vec = -this->cameraFrontDirection * speed;
                break;
            case MOVE_BACKWARD:
                vec = 1.0f * this->cameraFrontDirection * speed;
                break;
            case MOVE_RIGHT:
                vec = 1.0f * this->cameraRightDirection * speed;
                break;
            case MOVE_LEFT:
                vec = -this->cameraRightDirection * speed;
                break;
            case MOVE_UP:
                vec = this->cameraUpDirection * speed;
                break;
            case MOVE_DOWN:
                vec = -1.0f * this->cameraUpDirection * speed;
                break;
        }
        cameraPosition = cameraPosition + vec;
        cameraTarget = cameraTarget + vec;   
    }

    void Camera::scenePreview(float anglePreview) {

        this->cameraPosition = glm::vec3(13.0f, 10.0f, 2.0f);

        // rotate
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(anglePreview), glm::vec3(0, 1, 0));

        // compute the new position of the camera 
        // previous position * rotation matrix
        this->cameraPosition = glm::vec4(rotation * glm::vec4(this->cameraPosition, 1));
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        glm::vec3 f;
        f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        f.y = sin(glm::radians(pitch));
        f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        this->cameraFrontDirection = glm::normalize(f);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
    }
}