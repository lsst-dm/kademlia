// Copyright (c) 2013-2014, David Keller
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the University of California, Berkeley nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DAVID KELLER AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <kademlia/error.hpp>
#include <kademlia/detail/cxx11_macros.hpp>

#include <string>

namespace kademlia {

namespace {

/**
 *
 */
struct kademlia_error_category : std::error_category
{
    char const* 
    name
        ( void ) 
        const CXX11_NOEXCEPT override
    {
        return "kademlia";
    }

    std::string 
    message
        ( int condition ) 
        const CXX11_NOEXCEPT override 
    {
        switch ( condition )
        {
            case RUN_ABORTED:
                return "run aborted";
            case INITIAL_PEER_FAILED_TO_RESPOND:
                return "initial peer failed to respond";
            case UNIMPLEMENTED:
                return "unimplemented";
            case INVALID_ID:
                return "invalid id";
            case TRUNCATED_ID:
                return "truncated id";
            case TRUNCATED_ENDPOINT:
                return "truncated endpoint";
            case TRUNCATED_ADDRESS:
                return "truncated address";
            case TRUNCATED_HEADER:
                return "truncated header";
            case CORRUPTED_HEADER:
                return "corrupted header";
            case UNKNOWN_PROTOCOL_VERSION:
                return "unknown protocol version";
            default:
                return "unknown error";
        }
    }
};

} // namespace

std::error_category const&
error_category
    ( void )
{
    static const kademlia_error_category category_{};
    return category_;
}

std::error_condition
make_error_condition
    ( error_type code )
{
    return std::error_condition{ static_cast<int>(code), error_category() };
}

std::error_code
make_error_code
    ( error_type code )
{
    return std::error_code{ static_cast<int>(code), error_category() };
}

} // namespace kademlia

