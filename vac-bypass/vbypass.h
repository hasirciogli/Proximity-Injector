

namespace BypassLoader
{
    void LoaderLoop();
};

namespace LibraryLoader
{
	bool inject(DWORD processName, char* dllPath);
}