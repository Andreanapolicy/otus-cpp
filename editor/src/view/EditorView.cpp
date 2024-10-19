#pragma once
#include "EditorView.h"
#include "../controller/DocumentController.h"
#include "../controller/EditorController.h"
#include "../model/IDocument.h"
#include <functional>

namespace view
{
EditorView::EditorView(
	model::IDocumentUniquePtr document)
	: m_document{ std::move(document) }
	, m_documentController{ std::make_unique<controller::DocumentController>(*document) }
	, m_editorController{ std::make_unique<controller::EditorController>(*document) }
{
	// m_document->DoOnChange(...);
	// subscribe on UI
	// draw and start + loop
}

void EditorView::OnChange(model::UUID uuid)
{
	// look for all objects in vector
	// look for new uuid and add objects views + subscribe
	// look for unused uuid and delete objects
}

void EditorView::OnSave()
{
	std::filesystem::path path; // get path
	m_editorController->SaveDocument(path);
}

void EditorView::OnLoad()
{
	std::filesystem::path path; // get path
	m_document = std::move(m_editorController->LoadDocument(path));
	// reconstruct m_documentController
	// reconstruct m_editorController

	// m_document->DoOnChange(...);
}

void EditorView::OnAddObject(model::ObjectType type)
{
	m_documentController->AddObject(type);
}

void EditorView::Rebuild()
{
	m_objectViews.clear();
	// create all objectViews;
}
} // namespace view