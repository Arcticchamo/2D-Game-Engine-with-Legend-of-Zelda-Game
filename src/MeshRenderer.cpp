#include "GameObject.h"
#include "Mesh.h"
#include "MeshRenderer.h"


MeshRenderer::MeshRenderer()
{
}

void MeshRenderer::Start()
{
	
}

void MeshRenderer::Init()
{
	m_mesh = m_gameObject.lock()->GetComponent<Mesh>();
}

void MeshRenderer::Update()
{
	


}

void MeshRenderer::Destroy()
{
}

GLuint MeshRenderer::GetID()
{
	return m_mesh.lock()->GetID();
}

MeshRenderer::~MeshRenderer()
{
}