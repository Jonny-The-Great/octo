#ifndef OCTO_NETCOMMONS_HPP 
#define OCTO_NETCOMMONS_HPP 

#include <cstdint> 
#include <array> 
#include <span> 
#include <algorithm> 

namespace octo_network { 

namespace octo_netcommons { 




/** 
 * @brief Extracts a sequence of bits from an raw byte array starting at a specified bit offset, 
 *        and copies them into a provided buffer as a contiguous bit sequence. 
 *  
 * This function extracts `binarySize` bits starting 
 * from `binaryOffset` bit position, and packs them into the output buffer `outputBuffer`, 
 * with the most significant bit of each byte filled first. The output buffer is zeroed out 
 * before packing. 
 * 
 * @param inputData    The input data to extract bits from. 
 * @param binaryOffset The bit offset within the data to start extraction (0-based). 
 * @param binarySize   The number of bits to extract. 
 * @param outputBuffer The output buffer to hold the extracted bits, provided as a std::span. 
 *                     Must be large enough to hold `binarySize` bits (rounded up to bytes). 
 * 
 */ 
inline void GetDataWithBinaryOffsetAndSize(const span<const std::uint8_t> inputData, 
                                           const std::uint8_t binaryOffset, 
                                           const std::uint8_t binarySize, 
                                           std::span<std::uint8_t> outputBuffer) 
{ 
    // Zero out the output buffer 
    std::fill(outputBuffer.begin(), outputBuffer.end(), 0); 

    // Treat the header as a byte array without copying 
    const std::uint8_t* bytes = inputData.data(); 

    // Extract bits 
    for (std::uint16_t bit = 0; bit < binarySize; ++bit) 
    { 
        std::uint16_t srcBitIndex = binaryOffset + bit; 
        std::uint8_t srcByteIndex = srcBitIndex / 8; 
        std::uint8_t srcBitOffset = 7 - (srcBitIndex % 8);  
        std::uint8_t bitValue = (bytes[srcByteIndex] >> srcBitOffset) & 0x01; 
        std::uint8_t dstByteIndex = bit / 8; 
        std::uint8_t dstBitOffset = 7 - (bit % 8);  
        outputBuffer[dstByteIndex] |= (bitValue << dstBitOffset); 

    } 

}  




} // namespace octo_netcommons 

} // namespace octo_network 

#endif // OCTO_NETCOMMONS_HPP 
