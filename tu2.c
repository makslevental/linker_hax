#include "section.h"

static test z SECTION_ATTRIBUTE(struct_section) = {.a = 3, .b = 'c'};

static int zz SECTION_ATTRIBUTE(int_section) = 22;
