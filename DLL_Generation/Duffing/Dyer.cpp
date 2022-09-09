#include <cmath>
#include "Dyer.h"
#include <boost/multiprecision/cpp_int.hpp>
#include "wide_data.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random.hpp>

#include <string>
#include <iostream>
#include <fstream>

namespace mp = boost::multiprecision;
namespace rng = boost::random;

extern "C"
{

__declspec(dllexport) void duffing(double input, double x_in, double x_dot_in, double x_3_in, double Ts,
                                   double d, double a, double B,
                                   int bit_length, int rho, int rho_, double delta, double arr[]) {

    struct PKey {  // Public Key
        wide_uint_t kappa;
        wide_uint_t p;
    };

    auto read_prime_from_file = [&](int bit_length) {
        std::string FILE_NAME = "D:\\Enc_3\\duffing_new\\Duffing\\primes.txt";
        int NO_PRIME = 0;

        std::ifstream myfile;
        myfile.open(FILE_NAME); // std::ios_base::app ==> append not overwrite
        std::string line;

        wide_uint_t found_prime = NO_PRIME;
        if (myfile.is_open())
        {
            while (std::getline(myfile, line)) {
                std::size_t found_at = line.find(',');

                std::string bit_length_str = line.substr(0, found_at);
                int found_bit_length = std::stoi(bit_length_str);

                if (found_bit_length == bit_length) {
                    std::string prime_str = line.substr(found_at + 1);
                    wide_uint_t prime(prime_str);
                    found_prime = prime;
                    break;
                }
            }
        }
        myfile.close();
        return found_prime;
    };

    auto get_prime = [&](int bit_length) {
        wide_uint_t p = read_prime_from_file(bit_length);
        return p;
    };

    auto keygen = [&](int bit_length, int rho, int rho_) {
        wide_uint_t p = get_prime(bit_length);
        int nu = rho_ - rho;
        wide_uint_t kappa = get_prime(nu);
        PKey key = { kappa, p };
        return key;
    };

    auto pgen = [&](int bit_length, int rho_, wide_uint_t p) {
        int eta = std::floor(std::pow(bit_length, 2) / rho_) - bit_length;
        wide_uint_t q = get_prime(eta);
        wide_uint_t modulus = p * q;
        return modulus;
    };

    auto encode = [&](wide_double_t x, wide_double_t delta) {
        return wide_uint_t(mp::floor(x / delta + .5));
    };


    auto decode = [&](int m, wide_double_t delta) {
        wide_double_t x = m * delta;
        return x;
    };

    auto get_rand = [&](wide_uint_t min, wide_uint_t max) {
        static rng::mt11213b rng(clock());
        rng::uniform_int_distribution<wide_uint_t> distribution(min, max);
        return distribution(rng);
    };

    auto encrypt = [&](wide_uint_t m, PKey key, wide_uint_t modulus) {
        wide_uint_t q(mp::floor(
                (modulus / key.p).convert_to<wide_double_t>()
        ));
        wide_uint_t r = get_rand(0, q - 1);
        wide_uint_t s = get_rand(0, key.kappa - 1);

        return (m + s * key.kappa + r * key.p) % modulus;
    };

    auto min_residue = [&](const wide_int_t& a, const wide_int_t& m) {
        wide_int_t b = a % m;
        wide_int_t c = b - m;
        return b >= abs(c) ? c : b;
    };

    auto decrypt = [&](cipher_text c, PKey key) {  // MIGHT NEED `min_residue"
        //return static_cast<int>(min_residue(min_residue(c, key.p),key.kappa));
        return static_cast<int>(min_residue(c % key.p, key.kappa));
    };


    auto enc = [&](wide_double_t x, PKey key, wide_uint_t modulus, wide_double_t delta) {
        return encrypt(encode(x, delta), key, modulus);
    };

    auto dec = [&](wide_int_t c, PKey key, wide_double_t delta) {
        return decode(decrypt(c, key), delta);
    };

    auto add = [&](cipher_text c1, cipher_text c2, wide_uint_t modulus) {
        return (c1 + c2) % modulus;
    };

    auto mul = [&](cipher_text c1, cipher_text c2, wide_uint_t modulus) {
        return (c1 * c2) % modulus;
    };


    PKey key = keygen(bit_length, rho, rho_);
    auto modulus = pgen(bit_length, rho_, key.p);

#define ENC(m) enc((m), key, modulus, delta)
#define DEC(c, delta) dec((c), key, (delta))
#define ADD(m1, m2) add((m1), (m2), modulus)
#define MUL(m1, m2) mul((m1), (m2), modulus)

    auto _input = ENC(input);
    auto _x_in = ENC(x_in);
    auto _x_dot_in = ENC(x_dot_in);
    auto _x_3_in = ENC(x_3_in);
    auto _ts = ENC(Ts);
    auto _d_neg = ENC(-d);
    auto _a_neg = ENC(-a);
    auto _b_neg = ENC(-B);
    auto _ts_2 = enc(Ts, key, modulus, pow(delta, 2));
    auto _x_dot_in_4 = enc(x_dot_in, key, modulus, pow(delta, 4));
    auto _x_in_2 = enc(x_in, key, modulus, pow(delta, 2));

    auto _xdd_p1 = ADD(MUL(_input, ENC(1)), MUL(_d_neg, _x_dot_in));
    auto _xdd_p2 = ADD(MUL(_a_neg, _x_in), MUL(_b_neg, _x_3_in));
    auto _xdd = ADD(_xdd_p1, _xdd_p2);   //depth 2

    auto _x_dot_out_4 = ADD(MUL(_xdd, _ts_2), _x_dot_in_4);  //depth 4
    auto _x_out_2 = ADD(MUL(_x_dot_in, _ts), _x_in_2);


    auto x_dot_out = DEC(_x_dot_out_4, pow(delta, 4));
    auto x_out = DEC(_x_out_2, pow(delta, 2));

    //double xdd = input - d * x_dot_in - a * x_in - B * x_3_in;
    //double x_dot_out = xdd * Ts + x_dot_in;
    //double x_out = x_dot_in * Ts + x_in;

    arr[0] = (double)x_dot_out;
    arr[1] = (double)x_out;
}
}