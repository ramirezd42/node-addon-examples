#include <nan.h>
#include <SnapChat/mustache.h>

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsObject() || !info[0]->IsObject()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  
  if (!info[1]->IsFunction() || !info[1]->IsFunction()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }
  
  Local<Object> bufferObj = args[n]->ToObject();
  char* bufferData = Buffer::Data(bufferObj);
  
  SnapChat::RenderMustache(bufferData);
  
  v8::Local<v8::Function> cb = info[0].As<v8::Function>();
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New(outputFile).ToLocalChecked() };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::SetMethod(module, "exports", RunCallback);
}

NODE_MODULE(addon, Init)
