/* Convert from Hex to Float - IEEE754 Format */
exports.hex2float = function(n){
  var sign = (n >> 31) * 2 + 1; // +1 or -1.
  var exp = (n >>> 23) & 0xff;
  var mantissa = n & 0x007fffff;
  if (exp === 0xff) {
    // NaN or Infinity
    return mantissa ? NaN : sign * Infinity;
  }
  else if (exp) {
    // Normalized value
    exp -= 127;

    // Add implicit bit in normal mode.
    mantissa |= 0x00800000;
  }
  else {
    // Subnormal number
    exp = -126;
  }
  return sign * mantissa * Math.pow(2, exp - 23);
}

