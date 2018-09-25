#include "message_handler.h"
#include "pipeline.hh"
#include "query_utils.h"
#include "include_complete.h"
using namespace ccls;

namespace {
MethodType kMethodType = "$ccls/includes";

struct In_CclsIncludes : public RequestInMessage {
  MethodType GetMethodType() const override { return kMethodType; }
};
MAKE_REFLECT_STRUCT(In_CclsIncludes, id);
REGISTER_IN_MESSAGE(In_CclsIncludes);

struct Out_CclsIncludes : public lsOutMessage<Out_CclsIncludes> {
  lsRequestId id;
  std::vector<std::string> result;
};
MAKE_REFLECT_STRUCT(Out_CclsIncludes, jsonrpc, id, result);

struct Handler_CclsIncludes : BaseMessageHandler<In_CclsIncludes> {
  MethodType GetMethodType() const override { return kMethodType; }
  void Run(In_CclsIncludes *request) override {
    Out_CclsIncludes out;
    out.id = request->id;
    for (auto &item : include_complete->completion_items)
      out.result.push_back(item.detail);
    pipeline::WriteStdout(kMethodType, out);
  }
};
REGISTER_MESSAGE_HANDLER(Handler_CclsIncludes);
} // namespace
