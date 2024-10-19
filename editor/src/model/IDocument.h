#pragma once
#include "IObject_fwd.h"
#include "ObjectType.h"
#include "UUID.h"
#include <functional>
#include <vector>

#ifndef DIAGRAMS_IDocument_H
#define DIAGRAMS_IDocument_H
#endif

namespace model
{
class IDocument
{
public:
	virtual void AddObject(ObjectType type) = 0;
	virtual void DeleteObject(UUID uuid) = 0;

	virtual IObject& GetObject(UUID uuid) const = 0;
	virtual std::vector<UUID> GetAllUUIDs() const = 0;
	virtual void DoOnChange(std::function<void(UUID)> onChange) = 0;

	~IDocument() = default;
};
} // namespace model