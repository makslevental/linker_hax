#include "section.h"
#include <stdio.h>

static test x SECTION_ATTRIBUTE(struct_section) = {.a = 1, .b = 'a'};
static int xx SECTION_ATTRIBUTE(int_section) = 4;


int main() {
    long sz = SECTION_SIZE(struct_section);
    int i;

    printf("struct_section size is %ld\n", sz);

    for (i = 0; i < sz; ++i) {
        test c = SECTION_ITEM(struct_section, i);
        printf("a = %d, b = %c\n", c.a, c.b);
    }

    sz = SECTION_SIZE(int_section);
    printf("int_section size is %ld\n", sz);

    for (i = 0; i < sz; ++i) {
        int c = SECTION_ITEM(int_section, i);
        printf("%d\n", c);
    }

    return 0;
}