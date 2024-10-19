#pragma once
#include "IObject_fwd.h"
#include <functional>
#include <vector>

namespace model
{
class IDocument
{
public:
	[[nodiscard]] virtual void AddObject(ObjectType type) = 0;
	virtual void DeleteObject(UUID uuid) = 0;

	virtual IObject& GetObject(UUID uuid) const = 0;
	virtual std::vector<const IObject&> GetAllObjects() const = 0;
	virtual void DoOnChange(std::function<void(UUID)>& onChange) = 0;

	~IDocument() = default;
};
} // namespace model