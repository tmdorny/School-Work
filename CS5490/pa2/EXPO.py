#PA2 CS5490 Tim Dorny u0829896

def expo(m, d, n):
    # variable used to check the low bit of an integer
    bit = 1
    # number of bits in the exponent
    bits = d.bit_length()

    value = m**2
    value = value % n
    for i in range(0, (bits - 1)):
        shifted_exponent = d >> (bits - (2 + i))
        # If bit is high, square value and then multiply by m(only multiply by m if last bit)
        # If bit is low, only square the value
        if shifted_exponent & bit:
            value = (value * m) % n
            if i != (bits - 3):
                value = (value**2) % n
        else:
            value = (value**2) % n
    return value
