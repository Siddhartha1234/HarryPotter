#include "Camera2D.h"



Camera2D::Camera2D(): m_screenWidth(500),
					  m_screenHeight(500),
					  m_needsMatrixUpdate(true),
					  m_scale(1.0f),
					  m_position(0.0f,0.0f),
					  m_cameraMatrix(1.0f),
					  m_orthoMatrix(1.0f)
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::init(int screenWidth, int screenHeight)
{
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;
	m_orthoMatrix = glm::ortho(0.0f, (float)(m_screenWidth), 0.0f, (float)(m_screenHeight));
}

void Camera2D::update()
{
	if (m_needsMatrixUpdate)
	{
		//Camera Translation
		glm::vec3 translate(-m_position.x+m_screenWidth/2, -m_position.y+m_screenHeight/2, 0.0f);
		m_cameraMatrix = glm::translate(m_orthoMatrix, translate);
		glm::vec3 scale(m_scale, m_scale, 0.0f);
		m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale)*m_cameraMatrix;
		m_needsMatrixUpdate = false;
	}
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
{
	//invert y
	screenCoords.y = m_screenHeight-screenCoords.y;
	//make sure that zero is the centre
	screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);
	//scale the coordinates;
	screenCoords /= m_scale;
	//apply translation
	screenCoords += m_position;
	return screenCoords;

}
