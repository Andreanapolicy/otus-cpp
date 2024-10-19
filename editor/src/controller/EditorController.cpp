#include "EditorController.h"
#include "../model/IDocument.h"

namespace controller
{
EditorController::EditorController(const model::IDocument& document)
	: m_document{ document }
{
}

void EditorController::SaveDocument(const std::filesystem::path& path) const
{
	m_serializer.SaveDocument(path, m_document);
}

model::IDocumentUniquePtr EditorController::LoadDocument(const std::filesystem::path& path)
{
	return m_serializer.LoadDocument(path);
}
} // namespace controller