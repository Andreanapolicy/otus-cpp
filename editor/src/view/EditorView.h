#pragma once
#include "../controller/IDocumentController_fwd.h"
#include "../controller/IEditorController_fwd.h"
#include "../model/IDocument_fwd.h"
#include "../model/ObjectType.h"
#include "../model/UUID.h"
#include <memory>
#include <vector>

namespace view
{
class ObjectView;

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

	controller::IEditorControllerUniquePtr m_editorController;
	controller::IDocumentControllerUniquePtr m_documentController;
	model::IDocumentUniquePtr m_document;
	std::vector<std::unique_ptr<ObjectView>> m_objectViews;
};
} // namespace view