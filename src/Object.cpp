#include "Object.hpp"
#include <glm/gtc/matrix_transform.hpp>


Object::Object()
{
    /*m_position = glm::vec3(0.0f);
    m_rotation = glm::vec3(0.0f); 
    m_scale = glm::vec3(1.0f);*/
}

Transform& Object::GetTransform()
{
    return m_transform;
}

void Object::Render(Shader& shader)
{
    /*m_model = glm::mat4(1.0f);   
    m_model = glm::translate(m_model, m_position);
    m_model = glm::rotate(m_model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));//rotate 90 on the X axis
    m_model = glm::rotate(m_model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));//rotate 90 on the X axis
    m_model = glm::rotate(m_model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));//rotate 90 on the X axis
    m_model = glm::scale(m_model, m_scale);*/

    shader.setMat4("model", m_transform.GetMatrix());
}