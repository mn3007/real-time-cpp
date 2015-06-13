///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstddef>
#include <cstdint>
#include <mcal_led.h>
#include <mcal_reg_access.h>

mcal::led::led_type::led_type() : led_is_on(false)
{
  // Write 1 to the GPIO16 init nibble in the Function Select 1 GPIO
  // peripheral register to enable GPIO16 as an output.
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpfsel1, UINT32_C(18)>::bit_set();

  // Set the GPIO16 output high (turn the OK LED off).
  mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set();
}

void mcal::led::led_type::toggle() const
{
  // Toggle the LED state.
  // Note here that the logic of the led is inverted.

  (led_is_on ? mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpset0, UINT32_C(16)>::bit_set()
             : mcal::reg::access<std::uint32_t, std::uint32_t, mcal::reg::gpio_gpclr0, UINT32_C(16)>::bit_set());

  led_is_on = (!led_is_on);
}

namespace mcal
{
  namespace led
  {
    const led_type led0;
  }
}
