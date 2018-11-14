#include "message_handler.hh"
#include "sema_manager.hh"

namespace ccls {
namespace {
struct Param : TextDocumentParam {};
REFLECT_STRUCT(Param, textDocument);
} // namespace

void MessageHandler::ccls_diagnostic(JsonReader &reader) {
  Param param;
  reflect(reader, param);
  std::string path = param.textDocument.uri.getPath();
  manager->scheduleDiag(path, 0);
}
} // namespace ccls
