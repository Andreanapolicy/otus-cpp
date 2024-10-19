#pragma once
#include "../controller/IDocumentController_fwd.h"
#include "../controller/IEditorController_fwd.h"
#include "../model/IDocument_fwd.h"
#include "../model/ObjectType.h"
#include "../model/UUID.h"
#include "ObjectView.h"
#include <memory>
#include <vector>

namespace view
{
class EditorView
{
public:
	EditorView(
		model::IDocumentUniquePtr document);

private:
	void OnChange(model::UUID uuid);
	void OnSave();
	void OnLoad();
	void OnNewDocument();
	void OnAddObject(model::ObjectType type);
	void Rebuild();

	model::IDocumentUniquePtr m_document;
	controller::IDocumentControllerUniquePtr m_documentController;
	controller::IEditorControllerUniquePtr m_editorController;
	std::vector<std::unique_ptr<ObjectView>> m_objectViews;
};
} // namespace view