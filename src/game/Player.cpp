#include "Player.h"


void Player::Init()
{
	gameObject.lock()->SetName("Player");
	gameObject.lock()->SetTag("Player");

	transform = gameObject.lock()->AddComponent<Transform>();
	transform.lock()->Translate(glm::vec3((640 / 2), (480 / 2), 0.0f));
	transform.lock()->Scale(glm::vec3(10, 10, 1));

	meshRenderer = gameObject.lock()->AddComponent<MeshRenderer>("mesh");
	meshRenderer.lock()->GetMaterial()->SetShader(GetResources()->Load<Shader>("Shaders"));
	meshRenderer.lock()->GetMaterial()->SetValue("Player", GetResources()->Load<Texture>("Player/Link.png"));
}

void Player::Update()
{
	glm::vec3 position(0);
	glm::vec3 rotation(0);
	glm::vec3 scale(1.0f);

	InputController(position, rotation, scale);

	//std::cout << "Player Position = POS X: " << transform.lock()->GetPosition().x << ", POS Y: " << transform.lock()->GetPosition().y << std::endl;

	transform.lock()->Translate(position);
	//transform.lock()->TranslateObject(position);
	//transform.lock()->RotateObject(rotation);
	//transform.lock()->ScaleObject(scale);
	
	//transform.lock()->UpdateModelMatrix();

	//meshRenderer.lock()->Render();
	
	//Resources::SetUniform("in_ProjectionMat", engineCore.lock()->GetMainCamera()->GetComponent<Camera>()->GetProjectionMatrix());
	//Resources::SetUniform("in_ViewMat", glm::inverse(engineCore.lock()->GetMainCamera()->GetComponent<Camera>()->GetViewMatrix()));
}

void Player::InputController(glm::vec3 &position, glm::vec3 &rotation, glm::vec3 &scale)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (state[SDL_SCANCODE_UP]) position.y -= 2.5f;
	if (state[SDL_SCANCODE_DOWN]) position.y += 2.5f;
	if (state[SDL_SCANCODE_LEFT]) position.x -= 2.5f;
	if (state[SDL_SCANCODE_RIGHT]) position.x += 2.5f;

	//if (state[SDL_SCANCODE_W]) _pos.y -= 10.0f;
	//if (state[SDL_SCANCODE_S]) _pos.y += 10.0f;
	//if (state[SDL_SCANCODE_A]) _pos.x -= 10.0f;
	//if (state[SDL_SCANCODE_D]) _pos.x += 10.0f;

	//if (state[SDL_SCANCODE_E]) _rot.z -= 0.1f;
	//if (state[SDL_SCANCODE_Q]) _rot.z += 0.1f;

	if (state[SDL_SCANCODE_N]) scale += 0.5f;
	if (state[SDL_SCANCODE_M]) scale -= 0.5f;
}

Player::~Player()
{}


