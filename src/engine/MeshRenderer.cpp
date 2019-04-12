#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Screen.h"
#include "Shader.h"
#include "Transform.h"

void MeshRenderer::Init(std::string path)
{
	mesh = GetResources()->Load<Mesh>(path);
	material = std::make_shared<Material>();
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Render()
{
	material->GetShader()->SetUniform("in_ProjectionMat", GetScreen()->GetProjectionMatrix());
	material->GetShader()->SetUniform("in_ViewMat", GetCurrentCamera()->GetComponent<Camera>()->GetViewMatrix());
	material->GetShader()->SetUniform("in_ModelMat", gameObject.lock()->GetComponent<Transform>()->GetModelMatrix());

	material->Apply();
	glUseProgram(material->GetShader()->GetId());
	glBindVertexArray(mesh.lock()->GetId());
	glDrawArrays(GL_TRIANGLES, 0, mesh.lock()->GetTriangleCount());
	material->Remove();

	glBindVertexArray(0);
	glUseProgram(0);
}

void MeshRenderer::SetMesh(std::weak_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

std::weak_ptr<Mesh> MeshRenderer::GetMesh()
{
	return mesh;
}

std::shared_ptr<Material> MeshRenderer::GetMaterial()
{
	return material;
}

MeshRenderer::~MeshRenderer()
{
}