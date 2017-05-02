#include <nan.h>
#include "worker.h"

NAN_METHOD(RenderMustache) {
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

  v8::Local<v8::Object> bufferObj = info[0]->ToObject();
  char* bufferData = node::Buffer::Data(bufferObj);
  size_t bufferLength = node::Buffer::Length(bufferObj);

  v8::Local<v8::Function> cb = info[1].As<v8::Function>();

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { bufferObj };

  Nan::Callback *callback = new Nan::Callback(cb);
  Nan::AsyncQueueWorker(
    new MustacheWorker(callback, bufferData, bufferLength)
  );
}

NAN_MODULE_INIT(Init) {
    Nan::Set(target,
        Nan::New<v8::String>("renderMustache").ToLocalChecked(),
        Nan::GetFunction(
          Nan::New<v8::FunctionTemplate>(RenderMustache)
        ).ToLocalChecked()
    );
}

NODE_MODULE(binding, Init)
  
  
#include <nan.h>
#include <SnapChat/mustache.h>

class MustacheWorker : public Nan::AsyncWorker {
    public:
        MustacheWorker(Nan::Callback *callback, char *bufferData, size_t bufferLength)
        : Nan::AsyncWorker(callback),
          bufferData(bufferData),
          bufferLength(bufferLength) {}
        ~MustacheWorker() {}

        void Execute () {
          // this function executes in the worker thread
          SnapChat::Mustache::Render(bufferData);
        }

        void HandleOKCallback () {
            // we are now back in the event loop's thread
            v8::Local<v8::Value> argv[] = {
              Nan::NewBuffer(bufferData, bufferLength).ToLocalChecked()
            };
            callback->Call(1, argv);
        }

    private:
        char *bufferData;
        size_t bufferLength;
};

