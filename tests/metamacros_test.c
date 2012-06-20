/**
 * libextc metamacros testcase
 * ExtendedC
 *
 * by Justin Spahr-Summers
 *
 * Released 18. Jun 2012 into the public domain.
 */

#include "metamacros.h"
#include "metamacros_test.h"

#define test_stringify(INDEX, VALUE) \
    # INDEX metamacro_stringify(VALUE)

#define test_stringify_cxt(INDEX, CONTEXT, VALUE) \
    # INDEX CONTEXT metamacro_stringify(VALUE)

#define test_stringify_index(INDEX, CONTEXT) \
    # INDEX CONTEXT

#define test_concat(VALUE) \
    metamacro_stringify(VALUE)

#define test_empty_concat(VALUE) ""

void metamacros_test (void) {
    assert(metamacro_argcount(x) == 1);
    assert(metamacro_argcount(x, x) == 2);
    assert(metamacro_argcount(x, x, x) == 3);
    assert(metamacro_argcount(x, x, x, x) == 4);
    assert(metamacro_argcount(x, x, x, x, x) == 5);
    assert(metamacro_argcount(x, x, x, x, x, x) == 6);
    assert(metamacro_argcount(x, x, x, x, x, x, x) == 7);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x) == 8);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x) == 9);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x) == 10);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x) == 11);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x) == 12);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x) == 13);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 14);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 15);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 16);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 17);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 18);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 19);
    assert(metamacro_argcount(x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x, x) == 20);

    assert(0 == strcmp(metamacro_foreach(test_stringify,, 0), "00"));
    assert(0 == strcmp(metamacro_foreach(test_stringify,, 0, 1), "0011"));
    assert(0 == strcmp(metamacro_foreach(test_stringify,, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
        "001122334455667788991010111112121313141415151616171718181919"));

    assert(0 == strcmp(metamacro_foreach_cxt(test_stringify_cxt, ".", "foo", 0), "0foo0"));
    assert(0 == strcmp(metamacro_foreach_cxt(test_stringify_cxt, ".", "foo", 0, 1), "0foo0.1foo1"));
    assert(0 == strcmp(metamacro_foreach_cxt(test_stringify_cxt, ".", "foo", 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19),
        "0foo0.1foo1.2foo2.3foo3.4foo4.5foo5.6foo6.7foo7.8foo8.9foo9.10foo10.11foo11.12foo12.13foo13.14foo14.15foo15.16foo16.17foo17.18foo18.19foo19"));

    assert(0 == strcmp(metamacro_for_cxt(1, test_stringify_index, ".", "foo"), "0foo"));
    assert(0 == strcmp(metamacro_for_cxt(3, test_stringify_index, ".", "foo"), "0foo.1foo.2foo"));
    assert(0 == strcmp(metamacro_for_cxt(20, test_stringify_index,, ""), "012345678910111213141516171819"));

    assert(0 == strcmp(metamacro_foreach_concat(test_,, concat(foo)), "foo"));
    assert(0 == strcmp(metamacro_foreach_concat(test_empty_,, concat(foo)), ""));
    assert(0 == strcmp(metamacro_foreach_concat(test_,, concat(foo), empty_concat(foo), concat(bar)), "foobar"));
    assert(0 == strcmp(metamacro_foreach_concat(test_, ".", concat(foo), empty_concat(foo), concat(bar)), "foo..bar"));

    assert(metamacro_head(5, 1) == 5);
    assert(metamacro_head(1, 5) == 1);
    assert(0 == strcmp(metamacro_head("foo", "bar"), "foo"));

    assert(metamacro_tail(5, 1) == 1);
    assert(metamacro_tail(1, 5) == 5);
    assert(metamacro_head(metamacro_tail(1, 5, 1)) == 5);
    assert(metamacro_tail(metamacro_tail(1, 5, 3)) == 3);
    assert(0 == strcmp(metamacro_tail("bar", "foo", "foo")));

    assert(metamacro_inc(5) == 6);
    assert(metamacro_inc(0) == 1);
    assert(metamacro_inc(19) == 20);
    assert(metamacro_inc(metamacro_inc(5)) == 7);

    assert(metamacro_dec(5) == 4);
    assert(metamacro_dec(1) == 0);
    assert(metamacro_dec(20) == 19);
    assert(metamacro_dec(metamacro_dec(5)) == 3);

    assert(metamacro_dec(metamacro_inc(19)) == 19);
    assert(metamacro_dec(metamacro_inc(0)) == 0);
    assert(metamacro_inc(metamacro_dec(1)) == 1);
    assert(metamacro_inc(metamacro_dec(20)) == 20);
}
