#include <lib/timer_list.h>

#include <unity.h>

#include <stdlib.h>


const Timer* first(const void* tl) { return ((TimerList*)tl)->first; }
const Timer* last(const void* tl) { return ((TimerList*)tl)->last; }
const Timer* next(const Timer* t) { return t->next; }
const Timer* prev(const Timer* t) { return t->prev; }
const Timer* id(const void* t) { return t; }

char* timersToString(const void* timer, const Timer* (*next)(const Timer*)) {
    const uint16_t size = 256;
    char* s = (char*)malloc(size);
    uint8_t cc = 0;
    const Timer* ct = (const Timer*)timer;
    while (ct) {
        int n = snprintf(s + cc, size - cc, "(%s %d)", (const char*)ct->func, ct->delta);
        if ((n + 1) > (size - cc)) { TEST_FAIL(); }
        cc += n;
        ct = next(ct);
    }
    return s;
}

char* toString(const void* list, const Timer* (*first)(const void* tl), const Timer* (*next)(const Timer*)) {
    return timersToString(first(list), next);
}

char* toStringForward(const TimerList* tl) {
    return toString(tl, &first, &next);
}

char* toStringBackward(const TimerList* tl) {
    return toString(tl, &last, &prev);
}

#define TEST_TL_EQUALS_FORWARD(tl, expected) \
{                                            \
    char *s = toStringForward((tl));         \
    TEST_MESSAGE(s);                         \
    TEST_ASSERT_EQUAL_STRING((expected), s); \
    free(s);                                 \
}


#define TEST_TL_EQUALS_BACKWARD(tl, expected) \
{                                             \
    char *s = toStringBackward((tl));         \
    TEST_MESSAGE(s);                          \
    TEST_ASSERT_EQUAL_STRING((expected), s);  \
    free(s);                                  \
}

#define TEST_TS_EQUALS(timer, expected)      \
{                                            \
    char *s = timersToString((timer), &next);\
    TEST_MESSAGE(s);                         \
    TEST_ASSERT_EQUAL_STRING((expected), s); \
    free(s);                                 \
}


void setUp(void) {}

void tearDown(void) {}

void test_tlInit(void) {
    TimerList tl;
    tlInit(&tl);
    TEST_ASSERT_NULL(tl.first);
    TEST_ASSERT_NULL(tl.last);
    TEST_ASSERT_EQUAL_UINT16(0, tl.base);
}

void test_tlInsert_01(void) {
    TimerList tl;
    Timer t;
    t.func = (TimerFunc)"A";
    tlInit(&tl);
    tlInsert(&tl, &t, 1);
    TEST_ASSERT_NULL(t.next);
    TEST_ASSERT_NULL(t.prev);
    TEST_ASSERT_EQUAL_PTR(tl.first, &t);
    TEST_ASSERT_EQUAL_PTR(tl.last, &t);
    char* s = toStringForward(&tl);
    TEST_MESSAGE(s);
    free(s);
}

void test_tlInsert_at_end(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc)"A";

    Timer B;
    B.func = (TimerFunc)"B";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 2);

    TEST_ASSERT_EQUAL_PTR(tl.first, &A);
    TEST_ASSERT_EQUAL_PTR(tl.last, &B);
    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(B 1)(A 1)");
}

void test_tlInsert_at_begin(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc)"A";

    Timer B;
    B.func = (TimerFunc)"B";

    tlInsert(&tl, &A, 2);
    tlInsert(&tl, &B, 1);

    TEST_ASSERT_EQUAL_PTR(&B, tl.first);
    TEST_ASSERT_EQUAL_PTR(&A, tl.last);

    TEST_TL_EQUALS_FORWARD(&tl, "(B 1)(A 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(A 1)(B 1)");
}

void test_tlInsert_in_between(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc)"A";

    Timer B;
    B.func = (TimerFunc)"B";

    Timer C;
    C.func = (TimerFunc)"C";

    tlInsert(&tl, &A, 3);
    tlInsert(&tl, &B, 1);
    tlInsert(&tl, &C, 2);

    TEST_ASSERT_EQUAL_PTR(&B, tl.first);
    TEST_ASSERT_EQUAL_PTR(&A, tl.last);
    TEST_TL_EQUALS_FORWARD(&tl, "(B 1)(C 1)(A 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(A 1)(C 1)(B 1)");
}

void test_tlDelete_at_begin(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 2);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)(C 1)");

    tlDelete(&tl, &A);

    TEST_TL_EQUALS_FORWARD(&tl, "(B 2)(C 1)");
}

void test_tlDelete_in_the_middle(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 2);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)(C 1)");

    tlDelete(&tl, &B);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(C 2)");
}

void test_tlDelete_at_end(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 2);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)(C 1)");

    tlDelete(&tl, &C);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(B 1)(A 1)");
}

void test_tlRebase_at_begin(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 2);
    tlInsert(&tl, &B, 3);
    tlInsert(&tl, &C, 4);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 2)(B 1)(C 1)");

    tlRebase(&tl, 1);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 1)(C 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 1)(B 1)(A 1)");
}

void test_tlRebase_in_the_middle(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 2);
    tlInsert(&tl, &B, 3);
    tlInsert(&tl, &C, 4);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 2)(B 1)(C 1)");

    Timer* expired = tlRebase(&tl, 3);

    TEST_ASSERT_EQUAL(3, tl.base);

    TEST_TL_EQUALS_FORWARD(&tl, "(C 1)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 1)");
    TEST_TS_EQUALS(expired, "(A 2)(B 3)");
}

void test_tlRebase_at_end(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 2);
    tlInsert(&tl, &B, 3);
    tlInsert(&tl, &C, 4);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 2)(B 1)(C 1)");

    Timer* expired = tlRebase(&tl, 4);

    TEST_ASSERT_EQUAL(4, tl.base);

    TEST_TL_EQUALS_FORWARD(&tl, "");
    TEST_TL_EQUALS_BACKWARD(&tl, "");
    TEST_TS_EQUALS(expired, "(A 2)(B 3)(C 4)");
}

void test_tlInsert_same_delay(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 1);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 0)(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)(B 0)(A 1)");
}

void test_tlRebase_same_delay(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 1);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 0)(C 2)");

    Timer* expired = tlRebase(&tl, 1);

    TEST_TL_EQUALS_FORWARD(&tl, "(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)");
    TEST_TS_EQUALS(expired, "(A 1)(B 1)");
}

void test_tlDelete_same_delay_0(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 1);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 0)(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)(B 0)(A 1)");

    tlDelete(&tl, &A);

    TEST_TL_EQUALS_FORWARD(&tl, "(B 1)(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)(B 1)");
}

void test_tlDelete_same_delay_1(void) {
    TimerList tl;
    tlInit(&tl);

    Timer A;
    A.func = (TimerFunc) "A";

    Timer B;
    B.func = (TimerFunc) "B";

    Timer C;
    C.func = (TimerFunc) "C";

    tlInsert(&tl, &A, 1);
    tlInsert(&tl, &B, 1);
    tlInsert(&tl, &C, 3);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(B 0)(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)(B 0)(A 1)");

    tlDelete(&tl, &B);

    TEST_TL_EQUALS_FORWARD(&tl, "(A 1)(C 2)");
    TEST_TL_EQUALS_BACKWARD(&tl, "(C 2)(A 1)");
}

int main(int argc, char* argv[]) {
    UNITY_BEGIN();

    RUN_TEST(test_tlInit);
    RUN_TEST(test_tlInsert_01);
    RUN_TEST(test_tlInsert_at_end);
    RUN_TEST(test_tlInsert_at_begin);
    RUN_TEST(test_tlInsert_in_between);
    RUN_TEST(test_tlDelete_at_begin);
    RUN_TEST(test_tlDelete_in_the_middle);
    RUN_TEST(test_tlDelete_at_end);
    RUN_TEST(test_tlRebase_at_begin);
    RUN_TEST(test_tlRebase_in_the_middle);
    RUN_TEST(test_tlRebase_at_end);
    RUN_TEST(test_tlInsert_same_delay);
    RUN_TEST(test_tlRebase_same_delay);
    RUN_TEST(test_tlDelete_same_delay_0);
    RUN_TEST(test_tlDelete_same_delay_1);

    return UNITY_END();
}
