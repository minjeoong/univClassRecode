#include "Camera.h"

// TODO: fill up the following function properly 
void Camera::set_rotation(const glm::quat& _q)
{
  glm::mat4 rotationMatrix = glm::mat4_cast(_q);
  set_pose(rotationMatrix);
}

// TODO: re-write the following function properly 
const glm::quat Camera::get_rotation() const
{
  glm::mat4 viewMatrix = this->get_view_matrix();
  return glm::quat_cast(viewMatrix);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::quat& _q, const glm::vec3& _t)
{
  glm::mat4 rotationMatrix = glm::mat4_cast(_q);

  rotationMatrix[3][0] = -_t[0];
  rotationMatrix[3][1] = -_t[1];
  rotationMatrix[3][2] = _t[2];

  set_pose(rotationMatrix);
}

// TODO: fill up the following function properly 
void Camera::get_pose(glm::quat& _q, glm::vec3& _t) const
{
  _q = get_rotation();
  _t = position_;
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_pose() const
{
  glm::mat4 pose(1.0f);
  pose[0] = glm::vec4(right_dir_, 0.0f);
  pose[1] = glm::vec4(up_dir_, 0.0f);
  pose[2] = glm::vec4(front_dir_, 0.0f);
  pose[3] = glm::vec4(position_, 1.0f);
  return pose;}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::mat4& _frame)
{
  // +x_cam: right direction of the camera    (it should be a unit vector whose length is 1)
  // right_dir_ = ..... ; // +x
  // +y_cam: up direction of the camera       (it should be a unit vector whose length is 1)   
  // up_dir_    = ..... ;    // +y
  // -z_cam: front direction of the camera    (it should be a unit vector whose length is 1)
  // front_dir_ = ..... ;    // -z
  // pos_cam: position of the camera
  // position_  = ..... ;    // pos

    right_dir_ = glm::vec3(_frame[0][0], _frame[1][0], _frame[2][0]);
    up_dir_    = glm::vec3(_frame[0][1], _frame[1][1], _frame[2][1]);
    front_dir_ = glm::vec3(-_frame[0][2], -_frame[1][2], -_frame[2][2]);
    position_  = glm::vec3(-_frame[3][0], -_frame[3][1], -_frame[3][2]);
}

// TODO: fill up the following function properly 
void Camera::set_pose(const glm::vec3& _pos, const glm::vec3& _at, const glm::vec3& _up_dir)
{
  // up_dir_    = ..... ;
  // front_dir_ = ..... ;    // -z_cam direction
  // right_dir_ = ..... ;    // +x_cam direction
  // up_dir_    = ..... ;    // +y_cam direction

  // position_  = ..... ;      // pos

  glm::vec3 camDirection = glm::normalize(_at - _pos); // Opposite of the camera's actual orientation
  
  up_dir_    = _up_dir;
  front_dir_ = -camDirection;    // -z_cam direction
  right_dir_ = glm::normalize(glm::cross(up_dir_, front_dir_));    // +x_cam direction
  up_dir_    = glm::cross(front_dir_, right_dir_);    // +y_cam direction

  position_  = _at;      // pos
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_view_matrix() const
{
  return glm::lookAt(position_, position_ + front_dir_, up_dir_);
}

// TODO: rewrite the following function properly 
const glm::mat4 Camera::get_projection_matrix() const
{
  // TODO: Considering the followings,
  //       You must return a proper projection matrix
  //       i) camera mode: it can be either kOrtho or kPerspective
  //       ii) zoom-in/-out: if the camera mode is kOrtho, 
  //                         utilize ortho_scale_ for zoom-in/-out
  //                         if the camera mode is kPerspective,
  //                         utilize fovy_ for zoom-in/-out
  //       iii) aspect ratio: utilize aspect_ in the both camera modes
  //       iv) near/far clipping planes: utilize near_, far_

  if (mode_ == kOrtho) {
    float ortho_width = ortho_scale_ * aspect_;
    float ortho_height = ortho_scale_;
    return glm::ortho(-ortho_width, ortho_width, -ortho_height, ortho_height, near_, far_);
  } else {
    return glm::perspective(glm::radians(fovy_), aspect_, near_, far_);
  }
 }

// TODO: fill up the following functions properly 
void Camera::move_forward(float delta)
{
  position_ += delta * front_dir_;

}

// TODO: fill up the following functions properly 
void Camera::move_backward(float delta)
{
  position_ -= delta * front_dir_;

}

// TODO: fill up the following functions properly 
void Camera::move_left(float delta)
{
  position_ -= delta * right_dir_;

}

// TODO: fill up the following functions properly 
void Camera::move_right(float delta)
{
  position_ += delta * right_dir_;

}

// TODO: fill up the following functions properly 
void Camera::move_up(float delta)
{
  position_ += delta * up_dir_;

}

// TODO: fill up the following functions properly 
void Camera::move_down(float delta)
{
  position_ -= delta * up_dir_;

}
