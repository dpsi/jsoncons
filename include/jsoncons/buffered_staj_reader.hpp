// Copyright 2018 Daniel Parker
// Distributed under the Boost license, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// See https://github.com/danielaparker/jsoncons for latest version

#ifndef JSONCONS_BUFFERED_STAJ_READER_HPP
#define JSONCONS_BUFFERED_STAJ_READER_HPP

#include <memory> // std::allocator
#include <string>
#include <stdexcept>
#include <system_error>
#include <ios>
#include <type_traits> // std::enable_if
#include <vector> 
#include <jsoncons/json_exception.hpp>
#include <jsoncons/json_content_handler.hpp>
#include <jsoncons/bignum.hpp>
#include <jsoncons/parse_error_handler.hpp>
#include <jsoncons/ser_context.hpp>
#include <jsoncons/result.hpp>
#include <jsoncons/json.hpp> // basic_json
#include <jsoncons/staj_reader.hpp>
#include <jsoncons/detail/print_number.hpp>

namespace jsoncons {

template<class CharT>
class basic_buffered_staj_reader : public basic_staj_reader<CharT>
{
    typedef basic_json<CharT> json_type;
    typedef std::basic_string<CharT> string_type;

    struct stack_item
    {
        template <class... Args>
        stack_item(std::true_type, Args&& ... args)
            : name_(std::forward<Args>(args)...)
        {
        }
        template <class... Args>
        stack_item(std::false_type, Args&& ... args)
            : value_(std::forward<Args>(args)...)
        {
        }

        stack_item() = default;
        stack_item(const stack_item&) = default;
        stack_item(stack_item&&) = default;
        stack_item& operator=(const stack_item&) = default;
        stack_item& operator=(stack_item&&) = default;

        string_type name_;
        json_type value_;
    };

    enum class structure_type {root_t, array_t, object_t};

    basic_staj_reader<CharT>* reader_;
    std::vector<stack_item> item_stack_;
    std::vector<structure_type> structure_stack_;
public:
    basic_buffered_staj_reader(basic_staj_reader<CharT>& reader)
        : reader_(std::addressof(reader))
    {
        item_stack_.reserve(1000);
        structure_stack_.reserve(100);
        structure_stack_.push_back(structure_type::root_t);
    }

    bool done() const override
    {
        return reader_->done();
    }

    const basic_staj_event<CharT>& current() const override
    {
        return reader_->current();
    }

    void accept(basic_json_content_handler<CharT>& handler) override
    {
        reader_->accept(handler);
    }

    void accept(basic_json_content_handler<CharT>& handler,
                std::error_code& ec) override
    {
        reader_->accept(handler, ec);
    }

    void next() override
    {
        reader_->next();
    }

    void next(std::error_code& ec) override
    {
        reader_->next(ec);
    }

    const ser_context& context() const override
    {
        return reader_->context();
    }
};

typedef basic_buffered_staj_reader<char> buffered_staj_reader;
typedef basic_buffered_staj_reader<wchar_t> wbuffered_staj_reader;
}

#endif

