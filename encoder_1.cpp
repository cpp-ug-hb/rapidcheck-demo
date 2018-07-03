#include <rapidcheck.h>
#include <rapidcheck/state.h>

#include <array>
#include <cstdint>
#include <algorithm>


using rgb_uint8 = std::array<std::uint8_t, 3>;
using rgb_double = std::array<double, 3>;


std::uint8_t encode_uint8(double value) {
  return std::uint8_t(value * 255);
}

rgb_uint8 encode_rgb(rgb_double const& rgb_d)
{
  rgb_uint8 result;

  result[0] = encode_uint8(rgb_d[0]);
  result[1] = encode_uint8(rgb_d[1]);
  result[2] = encode_uint8(rgb_d[2]);

  // return result;
}

double decode_uint8(uint8_t value) {
  return double(value) / 256.0;
  // return double(value) / 255.0;
}

rgb_double decode_rgb(rgb_uint8 const& rgb_u8)
{
  rgb_double result;

  result[0] = decode_uint8(rgb_u8[0]);
  result[1] = decode_uint8(rgb_u8[1]);
  result[2] = decode_uint8(rgb_u8[2]);

  return result;
}

////////////////////////


int main()
{

  rc::check(
    "uint8 can be decoded and encoded to the same vaue",
    [] (uint8_t value) {
      auto decoded = decode_uint8(value);
      auto encoded = encode_uint8(decoded);

      RC_ASSERT( value == encoded);
  });


  // demo break
  return 0;


 rc::check(
    "double can be encoded and decoded to the same value",
    [] (double value) {

    auto encoded = encode_uint8(value);
    auto decoded = decode_uint8(encoded);

    RC_LOG() << "value: " << value << std::endl;
    RC_LOG() << "encoded: " << std::uint16_t(encoded) << std::endl;
    RC_LOG() << "decoded: " << decoded << std::endl;

    RC_ASSERT(value == decoded);
  });


  // demo break
  return 0;


  rc::check(
    "double can be encoded and decoded to the same value (2nd try)",
    [] {

    auto value_int = *rc::gen::inRange<uint64_t>(0, 1000000000);
    auto value = value_int / 1000000000.0;

    auto encoded = encode_uint8(value);
    auto decoded = decode_uint8(encoded);
    auto delta = std::abs(value - decoded);
    auto eps = (1.0/256);

    RC_LOG() << "value: " << value << std::endl;
    RC_LOG() << "encoded: " << std::uint16_t(encoded) << std::endl;
    RC_LOG() << "decoded: " << decoded << std::endl;
    RC_LOG() << "delta: " << delta << std::endl;
    RC_LOG() << "eps: " << eps << std::endl;

    RC_ASSERT(value == decoded);
   // RC_ASSERT( delta < eps);

  });


  // demo break
  // rerun the previous test, please
  return 0;



  // demo break
  return 0;


  rc::check(
    "rgb tuple can be decoded and encoded tot he same value",
    [] (rgb_uint8 rgb) {
      auto decoded = decode_rgb(rgb);
      auto encoded = encode_rgb(decoded);

      RC_ASSERT( rgb == encoded);
  });
}
