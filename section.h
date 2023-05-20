#if defined(__APPLE__)

#define MY_SECTION "__DATA,__mysection"

#else // defined(__linux__) ?

#define MY_SECTION "__mysection"

#endif