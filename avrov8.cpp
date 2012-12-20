#include <jni.h>
#include <iostream>
#include <v8.h>
#include <string>
#include <stdio.h>
#include <android/log.h>
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,"avrov8",__VA_ARGS__)
using namespace v8;

HandleScope handle_scope;

// Create a new context.
Persistent<Context> context;
std::string current_module_name;	
std::string lib_dir_path;	
	
Handle<String> ReadFile(const char* name) {
  FILE* file = fopen(name, "rb");
  if (file == NULL) return Handle<String>();

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
  Handle<String> result = String::New(chars, size);
  delete[] chars;
  return result;
}


const char* ToCString(const String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
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
	std::string full_file_path = lib_dir_path + current_module_name;
	LOGI("Loading js file :");
	LOGI(full_file_path.c_str());

    // Create a string containing the JavaScript source code.
    Handle<String> source = ReadFile(full_file_path.c_str());
    // Compile the source code.
    Handle<Script> script = Script::Compile(source);
	
	script->Run();
	LOGI("Finished Loding file.");
	
	
}

extern "C" {
	JNIEXPORT jstring JNICALL Java_me_sarim_myfirstapp_MainActivity_stringFromJNI( JNIEnv* env,jobject thiz,jstring sk1,jstring sk2  );
	JNIEXPORT void JNICALL Java_me_sarim_myfirstapp_MainActivity_loadjs( JNIEnv* env,jobject thiz,jstring sk1);
	JNIEXPORT void JNICALL Java_me_sarim_myfirstapp_MainActivity_killjs( JNIEnv* env,jobject thiz);
	JNIEXPORT jstring JNICALL Java_me_sarim_myfirstapp_MainActivity_avroparse( JNIEnv* env,jobject thiz,jstring sk1);
	

};

void GetJStringContent(JNIEnv *AEnv, jstring AStr, std::string &ARes) {
  if (!AStr) {
    ARes.clear();
    return;
  }

  const char *s = AEnv->GetStringUTFChars(AStr,NULL);
  ARes=s;
  AEnv->ReleaseStringUTFChars(AStr,s);
}


void Java_me_sarim_myfirstapp_MainActivity_loadjs(JNIEnv* env,jobject thiz,jstring sk1){
    std::string filedir;
    // Create a new context.
    context = Context::New();
    GetJStringContent(env,sk1,filedir);
    // Enter the created context for compiling and
    // running the hello world script. 
	lib_dir_path = filedir;

	Handle<ObjectTemplate> global = ObjectTemplate::New();
	
	global->Set(String::New("print"), FunctionTemplate::New(Print));
	global->Set(String::New("get_module_name"), FunctionTemplate::New(GetModuleName));
	
	context = Context::New(NULL, global);
	
	loadfile("lib/platform.js");
	loadfile("lib/utf8.js");
	loadfile("lib/suffixdict.js");
	loadfile("lib/autocorrect.js");
	loadfile("lib/avrodict.js");
	loadfile("lib/levenshtein.js");
	loadfile("lib/avrolib.js");
	loadfile("lib/avroregexlib.js");
	loadfile("lib/dbsearch.js");
	loadfile("lib/gi.js");
	loadfile("lib/suggestionbuilder.js");
	loadfile("lib/test.js");

	
}

void Java_me_sarim_myfirstapp_MainActivity_killjs( JNIEnv* env,jobject thiz){
	
	Context::Scope context_scope(context);
	context.Dispose();
	
}

jstring JNICALL Java_me_sarim_myfirstapp_MainActivity_avroparse( JNIEnv* env,jobject thiz,jstring sk1) {
	
  std::string banglatxt;
  GetJStringContent(env,sk1,banglatxt);
  Context::Scope context_scope(context);
  /*
  std::string code1 = "OmicronLab.Avro.Phonetic.parse('";
  std::string code2 = "');";
  std::string finalcode = code1 + banglatxt + code2;
  Handle<String> source2 = String::New(finalcode.c_str());
  
  Handle<Script> script2 = Script::Compile(source2);
   
  Handle<Value> result = script2->Run();
  */
  
  Handle<Object> global = context->Global();
  Handle<Value> avro_parse =   global->Get(String::New("testfunc"));
  Handle<Function> avro_parse_func = Handle<Function>::Cast(avro_parse);
  Handle<Value> args[1];
  Handle<Value> result;

  args[0] = v8::String::New(banglatxt.c_str());
  
  result = avro_parse_func->Call(global, 1, args);
  

  // Convert the result to an ASCII string and print it.
  String::Utf8Value ascii(result);
  //printf("%s\n", *ascii);
  //char * bntext = *ascii;
  std::string bntext = std::string(*ascii);
  
  return env->NewStringUTF(bntext.c_str());
}


jstring Java_me_sarim_myfirstapp_MainActivity_stringFromJNI( JNIEnv* env,jobject thiz,jstring sk1,jstring sk2 ){
	std::string name1,name2,namef;
	GetJStringContent(env,sk1,name1);
	GetJStringContent(env,sk2,name2);
	namef = name1 + std::string(" -JNI- ") + name2; 
    return env->NewStringUTF(namef.c_str());
}


