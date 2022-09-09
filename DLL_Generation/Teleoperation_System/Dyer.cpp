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
//__declspec(dllexport) int add(int x, int y) {
//    auto mul = [](int a, int b) {
//        return (a * b);
//    };
//    double i = 1;
//    wide_uint_t p = (wide_uint_t) i;
//    return mul(1,2);

//}
//struct point_group1 {
//    double x[2];
//};

__declspec(dllexport) void control(double xm, double dxm, double ddxm, double xs, double dxs,
                                   double ddxs, double mms, double kms, double bms, double um, double us, double mm, double ms,
                                   int bit_length, int rho, int rho_, double delta, double arr[]) {

    struct PKey {  // Public Key
        wide_uint_t kappa;
        wide_uint_t p;
    };

    auto read_prime_from_file = [&](int bit_length) {
        std::string FILE_NAME = "D:\\Enc_3\\Git\\Tele\\primes.txt";
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

    // region model gains encryption
    auto _kms = ENC(kms);
    auto _neg_kms = ENC(-kms);
    auto _bms = ENC(bms);
    auto _neg_bms = ENC(-bms);
    auto _neg_mms = ENC(-mms);
    // endregion

    // region local (m) variable encryption
    auto _xm = ENC(xm);
    auto _neg_xm = ENC(-xm);
    auto _dxm = ENC(dxm);
    auto _neg_dxm = ENC(-dxm);
    auto _ddxm = ENC(ddxm);
    auto _mm = ENC(mm);
    auto _um_prime = ENC(0.9 * um);

    wide_int_t _sign_dxm;
    if (dxm > 0) { _sign_dxm = ENC(1); }
    else if (dxm < 0) { _sign_dxm = ENC(-1); }
    else { _sign_dxm = ENC(0); }
    // endregion

    // region local (s) variable encryption
    auto _xs = ENC(xs);
    auto _neg_xs = ENC(-xs);
    auto _dxs = ENC(dxs);
    auto _neg_dxs = ENC(-dxs);
    auto _ddxs = ENC(ddxs);
    auto _ms = ENC(ms);
    auto _us_prime = ENC(0.9 * us);

    wide_int_t _sign_dxs;
    if (dxm > 0) { _sign_dxs = ENC(1); }
    else if (dxm < 0) { _sign_dxs = ENC(-1); }
    else { _sign_dxs = ENC(0); }
    // endregion
    // xm,dxm, ddxm, xs,dxs,ddxs, mms, kms, bms, um, us, mm, ms

    // helper variables to hold intermediate values
    wide_int_t _sum1;
    wide_int_t _sum2;

    // region encrypted calculation of tau_m
    auto _mass_diff_m = ADD(_mm, _neg_mms);
    auto _pos_diff_m = ADD(_xs, _neg_xm);
    auto _vel_diff_m = ADD(_dxs, _neg_dxm);

    auto _mass_term_m = MUL(_mass_diff_m, _ddxm);
    auto _pos_term_m = MUL(_pos_diff_m, _kms);
    auto _vel_term_m = MUL(_vel_diff_m, _bms);
    auto _sign_term_m = MUL(_um_prime, _sign_dxm);

    _sum1 = ADD(_mass_term_m, _pos_term_m);
    _sum2 = ADD(_vel_term_m, _sign_term_m);
    auto _tau_m = ADD(_sum1, _sum2);
    // endregion

    // region encrypted calculation of tau_s
    auto _mass_diff_s = ADD(_ms, _neg_mms);
    auto _pos_diff_s = ADD(_xm, _neg_xs);
    auto _vel_diff_s = ADD(_dxm, _neg_dxs);

    auto _mass_term_s = MUL(_mass_diff_s, _ddxs);
    auto _pos_term_s = MUL(_pos_diff_s, _kms);
    auto _vel_term_s = MUL(_vel_diff_s, _bms);
    auto _sign_term_s = MUL(_us_prime, _sign_dxs);

    _sum1 = ADD(_mass_term_s, _pos_term_s);
    _sum2 = ADD(_vel_term_s, _sign_term_s);
    auto _tau_s = ADD(_sum1, _sum2);
    // endregion

    auto tau_m = DEC(_tau_m, std::pow(delta, 2));
    auto tau_s = DEC(_tau_s, std::pow(delta, 2));

    arr[0] = (double)tau_m;
    arr[1] = (double)tau_s;
    //double tau_s_double = (double)tau_s;

    //temp.x[0] = tau_m_double;
    //temp.x[1] = tau_s_double;
    //return tau_m_double;
}
}
