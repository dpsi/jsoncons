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
#include <jsoncons/staj_reader.hpp>
#include <jsoncons/detail/print_number.hpp>

namespace jsoncons {

template<class CharT>
class basic_staj_event_holder
{
    std::vector<unsigned char> memory_;
    basic_staj_event<CharT> event_;

public: 
    basic_staj_event_holder(const basic_staj_event<CharT>& event)
    {
        switch (event.event_type())
        {
            case staj_event_type::string_value:
            {
                auto v = event.as<basic_string_view<CharT>();
                memory_.resize(v.length()*sizeof(CharT)+sizeof(CharT));
                event_ = basic_staj_event<CharT>(new (&memory_[0])CharT[v.size()],
                                                 v.size(),
                                                 event.event_type(),
                                                 event.get_semantic_tag());
                break;
            }
            case staj_event_type::byte_string_value:
                break;
            default:
                event_ = event;
                break;
        }
    }

};

template<class CharT>
class basic_buffered_staj_reader : public basic_staj_reader<CharT>
{
    basic_staj_reader<CharT>* reader_;
public:
    basic_buffered_staj_reader(basic_staj_reader<CharT>& reader)
        : reader_(std::addressof(reader))
    {
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

