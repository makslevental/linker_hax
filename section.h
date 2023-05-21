#ifdef __APPLE__

#define SECTION_START(name_, type_) extern type_ __start_##name_ __asm("section$start$__DATA$" #name_)
#define SECTION_END(name_, type_) extern type_ __stop_##name_ __asm("section$end$__DATA$" #name_)
#define SECTION_ATTRIBUTE(name_) __attribute__((section("__DATA," #name_), used, aligned(4))) __attribute__((noinline))
#define SECTION_SIZE(name_) \
    ((size_t) ((&__stop_##name_ - &__start_##name_)))
#define SECTION_ITEM(name_, i) (&__start_##name_)[i]

#else

#define SECTION_START(name_, type_) extern type_ __start_##name_[]
#define SECTION_END(name_, type_) extern type_ __stop_##name_[]
#define SECTION_ATTRIBUTE(name_) __attribute__((section("" #name_), used, aligned(4))) __attribute__((noinline))
#define SECTION_SIZE(name_) \
    ((size_t) ((__stop_##name_ - __start_##name_)))
#define SECTION_ITEM(name_, i) (__start_##name_)[i]

#endif

typedef struct {
    int a;
    char b;
} test;

SECTION_START(struct_section, test);
SECTION_END(struct_section, test);

SECTION_START(int_section, int);
SECTION_END(int_section, int);