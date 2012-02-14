#ifndef CODERUNNER_H
#define CODERUNNER_H
#include "CROptions.h"
#include "ContentParser.h"
#include "FileHandle.h"

class CodeRunner{
  private:
  public:
	static void CheckPrerequisites();
	static void ChDir(const char* dir);
	static void Run();
	static void GoToSleep();

 };
#endif
