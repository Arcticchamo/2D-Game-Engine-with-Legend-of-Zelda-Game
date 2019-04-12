#include <memory>
#include <string>
#include <vector>

class Shader;
class Texture;
struct MaterialAttribute;

class Material
{
private:
	std::weak_ptr<Shader> shader;
	std::vector<MaterialAttribute> attributes;
public:
	Material();
	~Material();

	void SetShader(std::weak_ptr<Shader> shader);
	std::shared_ptr<Shader> GetShader();
	void SetValue(std::string name, std::weak_ptr<Texture> value);
	void SetValue(std::string name, float value);
	void SetValue(std::string name, std::weak_ptr<Texture> textureValue, float floatValue);

	void Apply(); 
	void Remove();
};