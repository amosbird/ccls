#include "include_complete.hh"
#include "message_handler.hh"
#include "pipeline.hh"

namespace ccls {
void MessageHandler::ccls_includes(JsonReader &reader, ReplyOnce &reply) {
  std::vector<std::string> out;
  for (auto &item : include_complete->completion_items)
    out.push_back(item.detail);
  reply(out);
}
} // namespace ccls
