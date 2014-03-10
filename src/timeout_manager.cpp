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

#include "timeout_manager.hpp"

namespace kademlia {
namespace detail {

timeout_manager::timeout_manager
    ( boost::asio::io_service & io_service )
    : timer_{ io_service }
    , timeouts_{}
{}

void
timeout_manager::schedule_next_tick
    ( time_point const& expiration_time )
{
    // This will cancel any pending task.
    timer_.expires_at( expiration_time );

    auto fire = [ this ]( boost::system::error_code const& failure ) 
    { 
        // The current timeout has been canceled
        // hence stop right there.
        if ( failure )
            return;

        // The current expired timeout is the lowest in the map.
        auto expired_timeout = timeouts_.begin();
        // Call the user callback.
        expired_timeout->second();
        // And remove the timeout.
        timeouts_.erase( expired_timeout );

        // If there is a remaining timeout, schedule it.
        if ( ! timeouts_.empty() ) 
            schedule_next_tick( timeouts_.begin()->first );
    };

    timer_.async_wait( fire );
}

} // namespace detail
} // namespace kademlia

