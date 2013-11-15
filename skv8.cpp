#include <v8.h>
#include "skv8.h"
#include <stdio.h>
#include <string>

using namespace v8;


// Create a stack-allocated handle scope.
HandleScope handle_scope;

// Create a new context.
Persistent<Context> context;

std::string current_module_name;

Handle<String> ReadFile(const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) return v8::Handle<v8::String>();

  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  rewind(file);

  char* chars = new char[size + 1];
  chars[size] = '\0';
  for (int i = 0; i < size;) {
    int read = fread(&chars[i], 1, size - i, file);
    i += read;
  }
  fclose(file);
  v8::Handle<v8::String> result = v8::String::New(chars, size);
  delete[] chars;
  return result;
}

const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

Handle<Value> ReadFromFile(const Arguments& args){

	return ReadFile("candidate-selections.js");

}

Handle<Value> WriteToFile(const Arguments& args){

    String::Utf8Value str(args[0]);
    const char* strcontent = ToCString(str);

	const char* fname = "candidate-selections.js";

	FILE* file = fopen(fname, "wb");
	fprintf(file,"%s",strcontent);
	fclose(file);
	return Undefined();

}


Handle<Value> GetModuleName(const Arguments& args) {
	return String::New(current_module_name.substr(4,current_module_name.length()-7).c_str());
}

Handle<Value> Print(const Arguments& args) {
  bool first = true;
  for (int i = 0; i < args.Length(); i++) {
    HandleScope handle_scope;
    if (first) {
      first = false;
    } else {
      printf(" ");
    }
    String::Utf8Value str(args[i]);
    const char* cstr = ToCString(str);
    printf("%s", cstr);
  }
  printf("\n");
  fflush(stdout);
  return Undefined();
}


void loadfile(const char * filename){
    Context::Scope context_scope(context);
	current_module_name = std::string(filename);

    // Create a string containing the JavaScript source code.
    //Handle<String> source = String::New("k = Math.randomf() ;\n k + 1");
    Handle<String> source = ReadFile(filename);
    // Compile the source code.
    Handle<Script> script = Script::Compile(source);

	script->Run();
	printf("%s\n",filename);

}
void loadjs(){

    // Create a new context.

	Handle<ObjectTemplate> global = ObjectTemplate::New();

	global->Set(String::New("print"), FunctionTemplate::New(Print));
	global->Set(String::New("get_module_name"), FunctionTemplate::New(GetModuleName));
	global->Set(String::New("save_to_file"), FunctionTemplate::New(WriteToFile));
	global->Set(String::New("load_from_file"), FunctionTemplate::New(ReadFromFile));

	context = Context::New(NULL, global);

	loadfile("lib/platform.js");
	loadfile("lib/utf8.js");
	loadfile("lib/suffixdict.js");
	loadfile("lib/autocorrect.js");
	loadfile("lib/worddict.js");
  loadfile("lib/patterndict.js");
	loadfile("lib/levenshtein.js");
	loadfile("lib/avrolib.js");
	loadfile("lib/avroregexlib.js");
	loadfile("lib/dbsearch.js");
	loadfile("lib/gi.js");
	loadfile("lib/suggestionbuilder.js");
	loadfile("lib/test.js");


    // Enter the created context for compiling and
    // running the hello world script.

}

void CommitString(const char* word,const char* candidate){
	Context::Scope context_scope(context);
    Handle<Object> global = context->Global();
    Handle<Value> word_committed =   global->Get(String::New("word_committed"));
    Handle<Function> word_committed_func = Handle<Function>::Cast(word_committed);
    Handle<Value> args[2];
	args[1] = String::New(word);
	args[0] = String::New(candidate);
    word_committed_func->Call(global, 2, args);


}

std::vector<std::string> recvlists(std::string banglatxt){

  Context::Scope context_scope(context);
  Handle<Object> global = context->Global();
  Handle<Value> recv_list =   global->Get(String::New("recvlist"));
  Handle<Function> recv_list_func = Handle<Function>::Cast(recv_list);
  Handle<Value> args[1];
  Handle<Value> result;
// Local<Object> objwords;
  int length = 0,ii;
  std::vector<std::string> data;

  args[0] = v8::String::New(banglatxt.c_str());

  result = recv_list_func->Call(global, 1, args);

//  objwords = result->ToObject();
  Handle<Array> arr = result.As<Array>();

  length = arr->Length();//objwords->Get(v8::String::New("length"))->ToObject()->Uint32Value();

  for(ii = 0 ; ii < length ; ii++){
    Local<Value> element = arr->Get(ii);
    String::Utf8Value cstrword(element);
    //printf("%s",*cstrword);
    data.push_back(*cstrword);
  }

//  wlists = words;
  return data;


}

std::string avroparse(std::string banglatxt) {


  Context::Scope context_scope(context);
  //std::string code1 = "OmicronLab.Avro.Phonetic.parse('";
  //std::string code2 = "');";
  //std::string finalcode = code1 + banglatxt + code2;
  // Run the script to get the result.
  //Handle<String> source2 = String::New(finalcode.c_str());

  //Handle<Script> script2 = Script::Compile(source2);

 // Handle<Value> result = script2->Run();

  Handle<Object> global = context->Global();
  Handle<Value> avro_parse =   global->Get(String::New("testfunc"));
  Handle<Function> avro_parse_func = Handle<Function>::Cast(avro_parse);
  Handle<Value> args[1];
  Handle<Value> result;

  args[0] = v8::String::New(banglatxt.c_str());

  result = avro_parse_func->Call(global, 1, args);

  // Dispose the persistent context.
  //context.Dispose();

  // Convert the result to an ASCII string and print it.

  String::Utf8Value ascii(result);

  //printf("%s\n", *ascii);
  //char * bntext = *ascii;
  std::string bntext = std::string(*ascii);

  return bntext;
}
