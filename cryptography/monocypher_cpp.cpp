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
#include "monocypher_cpp.hpp" 


namespace monocypher_cpp { 

/** 
 * @brief C++ wrapper for the crypto_wipe function. 
 * Original C function declaration: 
 * void crypto_wipe(void *secret, size_t size); 
 * 
 * 
 */ 
void crypto_wipe(std::span<std::uint8_t> secret) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(!secret.empty()); // Ensure non-empty secret 
#endif 
    ::crypto_wipe(secret.data(), 
                  secret.size());  
} 




/** 
 * @brief C++ wrapper for the crypto_blake2b function. 
 * Original C function declaration: 
 * void crypto_blake2b(uint8_t *hash,          size_t hash_size, 
 *                     const uint8_t *message, size_t message_size);    
 * 
 */ 
void crypto_blake2b(std::span<std::uint8_t> hash, 
                    const std::span<const std::uint8_t> message) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(hash.size() >= 1 && hash.size() <= 64); // Blake2b hash size 
    assert(message.size() > 0); // Ensure non-empty message 
#endif  
    ::crypto_blake2b(hash.data(), 
                     hash.size(), 
                     message.data(), 
                     message.size()); 
} 




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
                          const std::span<const std::uint8_t> message) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(hash.size() >= 1 && hash.size() <= 64);  // Blake2b keyed hash size 
    assert(key.size() >= 1 && key.size() <= 64);    // Blake2b keyed key size 
    assert(message.size() > 0); // Ensure non-empty message 
#endif     
    ::crypto_blake2b_keyed(hash.data(), 
                           hash.size(), 
                           key.data(), 
                           key.size(), 
                           message.data(), 
                           message.size()); 
} 




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
                           const std::array<std::uint8_t, 32>& seed) noexcept 
{ 
    ::crypto_eddsa_key_pair(secret_key.data(), 
                            public_key.data(), 
                            seed.data()); 
} 




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
                       const std::span<const std::uint8_t> message) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(message.size() > 0); // Ensure non-empty message 
#endif     
    ::crypto_eddsa_sign(signature.data(), 
                        secret_key.data(), 
                        message.data(), 
                        message.size()); 
} 




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
                       const std::span<const std::uint8_t> message) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(message.size() > 0); // Ensure non-empty message 
#endif    
    return ::crypto_eddsa_check(signature.data(), 
                                public_key.data(), 
                                message.data(), 
                                message.size()); 
} 




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
std::uint32_t crypto_chacha20_ietf(std::span<std::uint8_t> cipher_text, 
                              const std::span<const std::uint8_t> plain_text, 
                              const std::array<std::uint8_t, 32>& key, 
                              const std::array<std::uint8_t, 12>& nonce, 
                              std::uint32_t ctr) noexcept 
{ 
#ifdef MONOCYPHER_CPP_DEBUG_MODE 
    assert(cipher_text.size() == plain_text.size()); 
    assert(cipher_text.size() > 0); // Ensure non-empty input 
#endif  
    return ::crypto_chacha20_ietf(cipher_text.data(), 
                                  plain_text.data(), 
                                  plain_text.size(), 
                                  key.data(), 
                                  nonce.data(), 
                                  ctr); 
} 

} // namespace monocypher_cpp 



