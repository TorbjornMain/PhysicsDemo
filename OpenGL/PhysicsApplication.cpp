#include "PhysicsApplication.h"
#include "Plane.h"
#include "Circle.h"

using namespace glm;

bool PhysicsApplication::startup()
{
	glfwInit();

	window = glfwCreateWindow(1280, 720,
		"Computer Graphics",
		nullptr, nullptr);
	if (window == nullptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED) {
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);


	glClearColor(0.0f, 0.0f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST); // enables the depth buffer

	Gizmos::create();

	PhysicsObject* p = new Plane();
	((Plane*)p)->m_normal = glm::vec2(0.3, 1);
	p->m_position = glm::vec2(0, -2);
	m_physicsObjects.push_back(p);

	p = new Plane();
	((Plane*)p)->m_normal = glm::vec2(-0.3, 1);
	p->m_position = glm::vec2(1, -2);
	m_physicsObjects.push_back(p);

	p = new Circle(1);
	p->m_position = glm::vec2(0, 2);
	((RigidBody*)p)->m_resistution = 1;
	m_physicsObjects.push_back(p);

	camera.radius = 1;

	return true;
}

void PhysicsApplication::shutdown()
{
	Gizmos::destroy();

	glfwDestroyWindow(window);


	glfwTerminate();
}

bool PhysicsApplication::update()
{
	camera.update(window);

	float dt = 1.0f / 60.0f;


	for (auto it = m_physicsObjects.begin(); it != m_physicsObjects.end(); it++)
	{
		PhysicsObject* obj = *it;
		obj->Update(dt);
		// collisions - check this object with everything further up the list
		for (auto it2 = it; it2 != m_physicsObjects.end(); it2++)
		{
			if (it != it2)
			{
				PhysicsObject* obj2 = *it2;
				obj2->CheckCollision(*obj);
			}
		}

	}
	Sleep(1000 * dt);
	return (glfwWindowShouldClose(window) == false && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS);
}

void PhysicsApplication::draw()
{
	mat4 view = camera.getView();
	mat4 projection = camera.getProjection();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	Gizmos::clear();

	Gizmos::addTransform(glm::mat4(1));
	vec4 orange(1, 0.7f, 0.2f, 1.0f);
	vec4 red(1, 0, 0, 1);
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::add2DLine(vec2(-10 + i, 10), vec2(-10 + i, -10), i == 10 ? orange : white);
		Gizmos::add2DLine(vec2(10, -10 + i), vec2(-10, -10 + i), i == 10 ? orange : white);
	}

	for (auto it = m_physicsObjects.begin(); it != m_physicsObjects.end(); it++)
	{
		PhysicsObject* obj = *it;
		obj->Draw();
	}

	Gizmos::draw2D(projection * view);
	
	glfwSwapBuffers(window);
	glfwPollEvents();

	day++;
}
