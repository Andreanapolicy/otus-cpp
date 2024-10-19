#pragma once
#include "../model/ObjectType.h"
#include "../model/UUID.h"

namespace controller
{
class IDocumentController
{
public:
	virtual void AddObject(model::ObjectType type) = 0;
	virtual void DeleteObject(model::UUID uuid) = 0;

	~IDocumentController() = default;
};

} // namespace controller