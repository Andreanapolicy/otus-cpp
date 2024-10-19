#pragma once
#include "../model/JSONSerializer.h"
#include "IEditorController.h"

namespace model
{
class IDocument;
}

namespace controller
{
class EditorController : public IEditorController
{
public:
	EditorController(const model::IDocument& document);

	void SaveDocument(const std::filesystem::path& path) const override;
	model::IDocumentUniquePtr LoadDocument(const std::filesystem::path& path) override;

private:
	const model::IDocument& m_document;
	model::JSONSerializer m_serializer;
};
} // namespace controller