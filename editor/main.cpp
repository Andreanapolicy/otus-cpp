#include "src/controller/DocumentController.h"
#include "src/controller/EditorController.h"
#include "src/model/Document.h"
#include "src/view/EditorView.h"

int main()
{
	auto document = std::make_unique<model::Document>();
	view::EditorView editorView(std::move(document));

	return 0;
}