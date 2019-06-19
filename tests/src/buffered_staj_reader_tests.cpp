// Copyright 2018 Daniel Parker
// Distributed under Boost license

#if defined(_MSC_VER)
#include "windows.h" // test no inadvertant macro expansions
#endif
#include <jsoncons/json.hpp>
#include <jsoncons/json_encoder.hpp>
#include <jsoncons/json_cursor.hpp>
#include <jsoncons/buffered_staj_reader.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>

using namespace jsoncons;

TEST_CASE("buffered_staj_reader test")
{
    std::string s = R"(
    [
        {
            "enrollmentNo" : 100,
            "firstName" : "Tom",
            "lastName" : "Cochrane",
            "mark" : 55              
        },
        {
            "enrollmentNo" : 101,
            "firstName" : "Catherine",
            "lastName" : "Smith",
            "mark" : 95},
        {
            "enrollmentNo" : 102,
            "firstName" : "William",
            "lastName" : "Skeleton",
            "mark" : 60              
        }
    ]
    )";

    json_cursor cursor(s);
    buffered_staj_reader reader(cursor);

    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::begin_array);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::begin_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::end_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::begin_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::end_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::begin_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::string_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::name);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::uint64_value);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::end_object);
    reader.next();
    REQUIRE_FALSE(reader.done());
    CHECK(reader.current().event_type() == staj_event_type::end_array);
    reader.next();
    CHECK(reader.done());
}



