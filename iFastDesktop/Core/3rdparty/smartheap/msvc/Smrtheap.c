extern int SmartHeap_malloc;
extern int SmartHeap_new;
extern int SmartHeap_mfc;

static void *refSmartHeap_malloc = &SmartHeap_malloc;
static void *refSmartHeap_new = &SmartHeap_new;

#if defined(_DEBUG) && !defined(MEM_DEBUG)
#define MEM_DEBUG 1
#endif

#ifdef _DLL
#define MEM_DLL 1
#endif

#if defined(MFC)

#if !defined(_AFXDLL)

static void *refSmartHeap_mfc = &SmartHeap_mfc;

#ifdef MEM_DEBUG
#if _MSC_VER < 1000
#pragma comment(lib, "shmfc32md.lib")
#else
#pragma comment(lib, "shmfc4md.lib")
#endif /* _MSC_VER */
#else
#if _MSC_VER >= 1000
#ifdef _MT
#pragma comment(lib, "shmfc4m.lib")
#else
#pragma comment(lib, "shmfc4m.lib")
#endif /* _MT */
#endif /* _MSC_VER */
#endif /* MEM_DEBUG */

#endif /* !_AFXDLL */

#endif /* MFC */

#if defined(MEM_DEBUG)
#pragma comment(lib, "shdw32md.lib")
#elif defined(_DLL)
#ifdef _MT
#ifdef MEM_SMP
#pragma comment(lib, "shdsmpmt.lib")
#else
#pragma comment(lib, "shdw32mt.lib")
#endif /* MEM_SMP */
#else
#pragma comment(lib, "shdw32m.lib")
#endif /* _MT */

#else /* _DLL */

#ifdef WIN32
extern int __stdcall DllTerminateSmartHeap(void *handle, long reason, void *reserved);
static void *refDllTerminateSmartHeap = (void *)&DllTerminateSmartHeap;
#endif /* WIN32 */

#ifdef _MT
#ifdef MEM_SMP
#pragma comment(lib, "shlsmpmt.lib")
#else
#pragma comment(lib, "shlw32mt.lib")
#endif /* MEM_SMP */
#else
#pragma comment(lib, "shlw32m.lib")
#endif /* _MT */
#endif /* MEM_DEBUG */
