#include <core/string.hpp>

#include <cstring>

#include <unittest/unittest.hpp>

int main () {
  using namespace unittest;

  test("basic-string-ref") = {
    task("default-constructor") = [] {
      constexpr core::string_ref ref { };
      assert::equal(ref.length(), 0);
      assert::equal(ref.size(), 0);
      assert::is_true(ref.empty());
      assert::is_null(ref.data());
    },

    task("copy-constructor") = [] {
      constexpr core::string_ref ref { "hello!", 6 };

      assert::equal(ref.length(), 6);
      assert::equal(ref.size(), 6);
      assert::is_false(ref.empty());
      assert::is_not_null(ref.data());

      constexpr core::string_ref copy { ref };

      assert::equal(copy.length(), ref.length());
      assert::equal(copy.size(), ref.size());
      assert::equal(copy.empty(), ref.empty());
      assert::equal(copy.data(), ref.data());

      assert::equal(copy, ref);
    },

    task("string-constructor") = [] {
      std::string str { "string-ctor" };
      core::string_ref ref { str };

      assert::is_not_null(ref.data());
      assert::is_false(ref.empty());
      assert::equal(ref.size(), 11);
      assert::is(ref.data(), str.data());
    },

    task("pointer-constructor") = [] {
      auto str = "pointer-constructor";
      core::string_ref ref { str };

      assert::is_not_null(ref.data());
      assert::is_false(ref.empty());

      assert::equal(ref.size(), std::strlen(str));
      assert::is(ref.data(), str);
    },

    task("pointer-len-constructor") = [] {
      constexpr core::string_ref ref { "pointer-len", 11 };

      assert::is_not_null(ref.data());
      assert::is_false(ref.empty());
      assert::equal(ref.size(), 11);
    },

    task("copy-assignment-operator") = [] {
      core::string_ref ref { "copy-assign" };
      core::string_ref copy { };
      copy = ref;

      assert::is_false(copy.empty());
      assert::is_false(ref.empty());
      assert::equal(copy.size(), ref.size());
      assert::is(copy.data(), ref.data());

      assert::equal(copy, ref);
    },

    task("explicit-string-cast") = [] { assert::fail(); },

    task("begin") = [] { assert::fail(); },
    task("end") = [] { assert::fail(); },
    task("cbegin") = [] { assert::fail(); },
    task("cend") = [] { assert::fail(); },
    task("rbegin") = [] { assert::fail(); },
    task("rend") = [] { assert::fail(); },
    task("crbegin") = [] { assert::fail(); },
    task("crend") = [] { assert::fail(); },
    task("max-size") = [] { assert::fail(); },
    task("length") = [] { assert::fail(); },
    task("size") = [] { assert::fail(); },
    task("empty") = [] { assert::fail(); },
    task("subscript-operator") = [] { assert::fail(); },
    task("front") = [] { assert::fail(); },
    task("back") = [] { assert::fail(); },
    task("data") = [] { assert::fail(); },
    task("remove-prefix") = [] { assert::fail(); },
    task("remove-suffix") = [] { assert::fail(); },

    task("clear") = [] {
      core::string_ref ref { "hello", 5 };

      assert::is_false(ref.empty());
      assert::equal(ref.size(), 5);

      ref.clear();

      assert::is_true(ref.empty());
      assert::is_null(ref.data());
    },

    task("substr") = [] {
      using core::string_ref;
      std::string str { "0123456789abcdefghij" };
      string_ref ref { str };

      assert::equal(ref.substr(10), string_ref { "abcdefghij" });
      assert::equal(ref.substr(5, 3), string_ref { "567" });
      assert::equal(ref.substr(12, 100), string_ref { "cdefghij" });
      assert::equal(ref.substr(ref.size() - 3, 50), string_ref { "hij" });
    },

    task("starts-with") = [] { assert::fail(); },
    task("ends-with") = [] { assert::fail(); },
    task("compare") = [] { assert::fail(); },
    task("at") = [] { assert::fail(); },
    task("find-first-not-of") = [] { assert::fail(); },
    task("find-last-not-of") = [] { assert::fail(); },

    task("find-first-of") = [] {
      core::string_ref ref { "find-first-of" };
      auto npos = core::string_ref::npos; /* used to solve linker issue */

      /* char comparisons */
      assert::equal(ref.find_first_of('x'), npos);
      assert::equal(ref.find_first_of('f'), 0);

      /* string-ref comparisons */
      core::string_ref search_pass { "pass" };
      core::string_ref search_fail { "que?" };

      assert::equal(ref.find_first_of(search_fail), npos);
      assert::equal(ref.find_first_of(search_pass), 8);
    },

    task("find-last-of") = [] { assert::fail(); },
    task("rfind") = [] { assert::fail(); },

    task("find") = [] {
      core::string_ref ref { "find" };
      auto npos = core::string_ref::npos;

      assert::equal(ref.find(core::string_ref { "in" }), 1);
      assert::equal(ref.find('d'), 3);

      assert::equal(ref.find(core::string_ref { "string" }), npos);
      assert::equal(ref.find('x'), npos);
    },

    task("swap") = [] { assert::fail(); },
    task("operator-equal") = [] { assert::fail(); },
    task("operator-not-equal") = [] { assert::fail(); },
    task("operator-greater-equal") = [] { assert::fail(); },
    task("operator-less-equal") = [] { assert::fail(); },
    task("operator-greater") = [] { assert::fail(); },
    task("operator-less") = [] { assert::fail(); },
    task("operator-stream-insert") = [] { assert::fail(); },
    task("hash") = [] { assert::fail(); }
  };

  monitor::run();
}