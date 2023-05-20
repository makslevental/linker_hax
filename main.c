#include "section.h"
#include <stdio.h>

#if defined(__APPLE__)

extern int __start___mysection __asm("section$start$__DATA$__mysection");
extern int __stop___mysection __asm("section$end$__DATA$__mysection");

#define SECTION_SIZE(sect) \
    ((size_t) ((&__stop_##sect - &__start_##sect)))
#define GET_ITEM(i) (&__start___mysection)[i]

#else// defined(__linux__) ?

extern int __start___mysection[];
extern int __stop___mysection[];

#define SECTION_SIZE(sect) \
    ((size_t) ((__stop_##sect - __start_##sect)))
#define GET_ITEM(i) (__start___mysection)[i]

#endif

// If you don't reference x, y and z explicitly, they'll be dead-stripped.
// Prevent that with the "used" attribute.
static int x __attribute__((used, section(MY_SECTION))) = 4;

int main() {
    long sz = SECTION_SIZE(__mysection);
    long i;

    printf("Section size is %ld\n", sz);

    for (i = 0; i < sz; ++i) {
        printf("%d\n", GET_ITEM(i));
    }

    return 0;
}