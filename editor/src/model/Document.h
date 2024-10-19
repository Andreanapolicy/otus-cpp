#pragma once
#include "IDocument.h"
#include <memory>
#include <unordered_map>

namespace model
{
class Document : public IDocument
{
public:
	Document() = default;

	Document(const Document&) = delete;
	Document(Document&&) = delete;

	Document operator=(const Document&) = delete;
	Document operator=(Document&&) = delete;

	[[nodiscard]] void AddObject(ObjectType type) override;
	void DeleteObject(UUID uuid) override;
	IObject& GetObject(UUID uuid) const override;
	std::vector<const IObject&> GetAllObjects() const;
	void DoOnChange(std::function<void(UUID)>& onChange) override;

private:
	std::unordered_map<UUID, std::unique_ptr<IObject>> m_objectStorage;
	std::function<void(UUID)>& m_onChange;
};
} // namespace model