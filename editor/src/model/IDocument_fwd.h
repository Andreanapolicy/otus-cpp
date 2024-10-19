#pragma once
#include <memory>

namespace model
{
class IDocument;
using IDocumentUniquePtr = std::unique_ptr<IDocument>;
} // namespace model