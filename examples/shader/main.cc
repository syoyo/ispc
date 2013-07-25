#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/JIT.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/SourceMgr.h"     // SMDiagnostic
#include "llvm/Support/raw_ostream.h"

// ISPC related stuff.
#include "shader.h"

using namespace llvm;

llvm::ExecutionEngine* gEE;
typedef void (*shader_proc)(struct ispc::ShadeSample* samples, int32_t n);

shader_proc gShaderFunc;

static shader_proc JITCompile(llvm::Module *Mod) {

  std::string Error;
  gEE = llvm::ExecutionEngine::createJIT(Mod, &Error);
  if (!gEE) {
    llvm::errs() << "unable to make execution engine: " << Error << "\n";
    return NULL;
  }

  llvm::Function *EntryFn = Mod->getFunction("shader");
  if (!EntryFn) {
    llvm::errs() << "'shader' function not found in module.\n";
    return NULL;
  }

  void *ptr = gEE->recompileAndRelinkFunction(EntryFn);
  assert(ptr);

  shader_proc shaderFunc = reinterpret_cast<shader_proc>(ptr);

  return shaderFunc;
}

static void
Render(
  float* rgba,
  int width,
  int height)
{

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      ispc::ShadeSample ss;

      ss.Cs.v[0] = x / (float)width;
      ss.Cs.v[1] = y / (float)height;
      ss.Cs.v[2] = 0.0f;

      ss.Os.v[0] = 1.0f;
      ss.Os.v[1] = 1.0f;
      ss.Os.v[2] = 1.0f;
      ss.Os.v[3] = 1.0f;

      // @todo { Batch call of shader function for better performance. }
      gShaderFunc(&ss, 1);

      rgba[4*(y*width+x)+0] = ss.Ci.v[0];
      rgba[4*(y*width+x)+1] = ss.Ci.v[1];
      rgba[4*(y*width+x)+2] = ss.Ci.v[2];
      rgba[4*(y*width+x)+3] = ss.Oi.v[0];

    }
  }

}

static unsigned char
clamp(float f)
{
    int i = (int)(f * 255.5);

    if (i < 0) i = 0;
    if (i > 255) i = 255;

    return (unsigned char)i;
}

static void
SavePPM(const char *fname, float* fimg, int w, int h)
{
    std::vector<unsigned char> img(w*h*3);

    // RGBA -> RGB
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++)  {
            float a = fimg[4*(y*w+x)+3];
            img[3 * (y * w + x) + 0] = clamp(fimg[4 *(y * w + x) + 0] * a);
            img[3 * (y * w + x) + 1] = clamp(fimg[4 *(y * w + x) + 1] * a);
            img[3 * (y * w + x) + 2] = clamp(fimg[4 *(y * w + x) + 2] * a);
        }
    }

    FILE *fp = fopen(fname, "wb");
    if (!fp) {
        perror(fname);
        exit(1);
    }

    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", w, h);
    fprintf(fp, "255\n");
    fwrite(&img[0], w * h * 3, 1, fp);
    fclose(fp);
    printf("Wrote image file %s\n", fname);
}


int
main(
  int argc,
  char **argv)
{
  llvm::InitializeNativeTarget();
  llvm::llvm_shutdown_obj Y; // Call llvm_shutdown() on exit.

  LLVMContext& Context = llvm::getGlobalContext();

  std::string input = "shader.bc";

  if (argc > 1) {
    input = std::string(argv[1]);
  }
  
  SMDiagnostic Err;

  Module* M = ParseIRFile(input, Err, Context);

  if (!M) {
    Err.print(argv[0], llvm::errs());
    return 1;
  }

  gShaderFunc = JITCompile(M);
  assert(gShaderFunc);

  int width = 512;
  int height = 512;
  std::vector<float> rgba(width*height*4);
  Render(&rgba[0], width, height);
  SavePPM("output.ppm", &rgba[0], width, height);

  return 0;
}
