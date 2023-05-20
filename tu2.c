#include "section.h"

static int z __attribute__((used, section(MY_SECTION))) = 22;
