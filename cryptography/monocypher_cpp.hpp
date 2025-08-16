// monocypher_cpp.cpp 
/** 
 * @file monocypher_cpp.hpp 
 * @brief C++ wrappers for the Monocypher cryptographic library. 
 * 
 * This header provides a set of thin, type-safe, exception-safe C++ wrappers 
 * over the Monocypher C cryptographic API. The wrappers leverage modern C++  
 * constructs such as `std::array` and `std::span` for safer and more expressive 
 * cryptographic operations. 
 * 
 * Functions in this namespace directly correspond to their Monocypher C equivalents,    
 * providing direct access to its cryptographic primitives without further abstraction.  
 */ 
#ifndef MONOCYPHER_CPP_HPP 
#define MONOCYPHER_CPP_HPP 
#include <cstdint> 
#include <span> 
#include <array> 
extern "C" { 
    #include <monocypher/monocypher.h> 
} 




/** 
 * @def MONOCYPHER_CPP_DEBUG_MODE 
 * @brief Debug mode for Monocypher C++ wrappers.  
 *  
 * Debug mode (`MONOCYPHER_CPP_DEBUG_MODE`) is used to enforce runtime assertions  
 * that ensure certain conditions are met during the execution of cryptographic  
 * operations. These assertions help catch errors in development or testing by  
 * verifying that input values and sizes are within expected bounds before calling  
 * the underlying Monocypher C functions. 
 * 
 * Debug mode assertions are typically disabled in release builds to avoid any  
 * runtime performance overhead. 
 */ 
#define MONOCYPHER_CPP_DEBUG_MODE 1 

#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    #include <cassert> 
#endif 




namespace monocypher_cpp { 

/** 
 * @brief C++ wrapper for the crypto_wipe function. 
 * Original C function declaration: 
 * void crypto_wipe(void *secret, size_t size); 
 * 
 * 
 */ 
void crypto_wipe(std::span<std::uint8_t> secret) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_blake2b function. 
 * Original C function declaration: 
 * void crypto_blake2b(uint8_t *hash,          size_t hash_size, 
 *                     const uint8_t *message, size_t message_size);    
 * 
 */ 
void crypto_blake2b(std::span<std::uint8_t> hash, 
                    const std::span<const std::uint8_t> message) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_blake2b_keyed function. 
 * Original C function declaration: 
 * void crypto_blake2b_keyed(uint8_t *hash,          size_t hash_size, 
 *                           const uint8_t *key,     size_t key_size, 
 *                           const uint8_t *message, size_t message_size);  
 * 
 */ 
void crypto_blake2b_keyed(std::span<std::uint8_t> hash, 
                          const std::span<const std::uint8_t> key, 
                          const std::span<const std::uint8_t> message) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_eddsa_key_pair function. 
 * Original C function declaration: 
 * void crypto_eddsa_key_pair(uint8_t secret_key[64], 
 *                            uint8_t public_key[32], 
 *                            uint8_t seed[32]); 
 * 
 */ 
void crypto_eddsa_key_pair(std::array<std::uint8_t, 64>& secret_key, 
                           std::array<std::uint8_t, 32>& public_key, 
                           const std::array<std::uint8_t, 32>& seed) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_eddsa_sign function. 
 * Original C function declaration: 
 * void crypto_eddsa_sign(uint8_t        signature [64], 
 *                      const uint8_t  secret_key[64], 
 *                      const uint8_t *message, size_t message_size); 
 *  
 */ 
void crypto_eddsa_sign(std::array<std::uint8_t, 64>& signature, 
                       const std::array<std::uint8_t, 64>& secret_key, 
                       const std::span<const std::uint8_t> message) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_eddsa_check function. 
 * Original C function declaration: 
 * int crypto_eddsa_check(const uint8_t  signature [64], 
 *                        const uint8_t  public_key[32], 
 *                        const uint8_t *message, size_t message_size); 
 * 
 */ 
[[nodiscard]] 
int crypto_eddsa_check(const std::array<std::uint8_t, 64>& signature, 
                       const std::array<std::uint8_t, 32>& public_key, 
                       const std::span<const std::uint8_t> message) noexcept; 




/** 
 * @brief C++ wrapper for the crypto_chacha20_ietf function. 
 * Original C function declaration: 
 * uint32_t crypto_chacha20_ietf(uint8_t       *cipher_text, 
 *                               const uint8_t *plain_text, 
 *                               size_t         text_size, 
 *                               const uint8_t  key[32], 
 *                               const uint8_t  nonce[12], 
 *                               uint32_t       ctr);  
 * 
 */ 
uint32_t crypto_chacha20_ietf(std::span<std::uint8_t> cipher_text, 
                              const std::span<const std::uint8_t> plain_text, 
                              const std::array<std::uint8_t, 32>& key, 
                              const std::array<std::uint8_t, 12>& nonce, 
                              std::uint32_t ctr) noexcept; 

} // namespace monocypher_cpp 

#endif // monocypher_cpp.hpp  



