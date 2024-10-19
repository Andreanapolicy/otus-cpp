#include "Document.h"
#include "ObjectFactory.h"
#include <exception>

namespace model
{
void Document::AddObject(ObjectType type)
{
	const auto object = ObjectFactory::CreateObject(type);
	auto uuid = object->GetUUID();
	//m_objectStorage.emplace(uuid, std::move(object));

	if (m_onChange)
	{
		m_onChange(uuid);
	}
}

void Document::DeleteObject(UUID uuid)
{
	// delete obj
	if (m_onChange)
	{
		m_onChange(uuid);
	}
}

IObject& Document::GetObject(UUID uuid) const
{
	auto it = m_objectStorage.find(uuid);

	if (it == m_objectStorage.end())
	{
		throw std::runtime_error("Error, there are no object by uuid " + uuid);
	}

	return *(it->second);
}

std::vector<UUID> Document::GetAllUUIDs() const
{
	return std::vector<UUID>(); // fill vector from map by IObject references;
}

void Document::DoOnChange(std::function<void(UUID)> onChange)
{
	m_onChange = onChange;
}
} // namespace model