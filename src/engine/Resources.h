#include "Resource.h"

#include <string>
#include <vector>

class Resources
{
private:
	std::vector<std::shared_ptr<Resource>> resources;
public:

	template<class R>
	std::shared_ptr<R> Load(std::string path)
	{
		path = "../Resources/" + path;

		for (std::vector<std::shared_ptr<Resource>>::iterator it = resources.begin(); it != resources.end(); it++)
		{
			if ((*it)->GetFilePath() == path)
			{
				std::shared_ptr<R> temp = std::dynamic_pointer_cast<R>(*it);
				if (temp)
				{
					return temp;
				}
			}
		}

		//std::shared_ptr<res> r = res::Init(path);
		std::shared_ptr<R> res = std::make_shared<R>();
		res = res->Init(path);
		resources.push_back(res);
		return res;
	}
};