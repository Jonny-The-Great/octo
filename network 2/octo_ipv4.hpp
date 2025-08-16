/** 
 * @file octo_ipv4.hpp 
 * @brief Defines structures and constants for IPv4 header manipulation as per RFC 791: https://www.rfc-editor.org/rfc/rfc791#ref-9. 
 * 
 * This header provides: 
 * - A packed struct `Ipv4Header` representing a 20-byte IPv4 header layout. 
 * - Constants for encoding Version, Header Length, Type of Service, and Fragmentation Flags. 
 * - Bit-level layout documentation for key fields. 
 * 
 * The definitions follow the standard IPv4 format and are useful for low-level networking tasks, 
 * such as constructing or parsing raw IPv4 packets. 
 * 
 * @note All structures are packed to ensure strict conformance to byte alignment as defined in RFC 791. 
 *       The usage of raw byte arrays, etc. allows for system-endian independent access. 
 */ 
#ifndef OCTO_HPP 
#define OCTO_HPP 

#include <cstdint> 
#include <array> 
#include <span> 
#include <algorithm>  

namespace octo_network 
{ 


namespace octo_ipv4 
{ 




/** 
 * @brief Represents an IPv4 header according to RFC 791. 
 * 
 * @par Memory Layout (Offset and Size in Bytes) 
 * | Offset | Size | Field                      | 
 * |--------|------|----------------------------| 
 * | 0      | 1    | versionAndHeaderLength     | 
 * | 1      | 1    | typeOfService              | 
 * | 2      | 2    | totalLength                | 
 * | 4      | 2    | identification             | 
 * | 6      | 2    | flagsAndFragmentOffset     | 
 * | 8      | 1    | timeToLive                 | 
 * | 9      | 1    | protocol                   | 
 * | 10     | 2    | headerChecksum             | 
 * | 12     | 4    | sourceAddress              | 
 * | 16     | 4    | destinationAddress         | 
 * Total size: 20 bytes (without options). 
 */ 
#pragma pack(push, 1) // Ensure 1-byte alignment for the structure 
struct Ipv4Header 
{ 
    std::uint8_t                versionAndHeaderLength;            // Combined Version and Internet Header Length 
    std::uint8_t                typeOfService; 
    std::array<std::uint8_t, 2> totalLength; 
    std::array<std::uint8_t, 2> identification; 
    std::array<std::uint8_t, 2> flagsAndFragmentOffset; 
    std::uint8_t                timeToLive; 
    std::uint8_t                protocol; 
    std::array<std::uint8_t, 2> headerChecksum; 
    std::array<std::uint8_t, 4> sourceAddress; 
    std::array<std::uint8_t, 4> destinationAddress; 
    
}; 
#pragma pack(pop) // Restore previous packing alignment 
// Ensure the structure is packed correctly to match the expected size 
static_assert(sizeof(Ipv4Header) == 20, "Ipv4Header must be 20 bytes"); 




/** 
 * @brief bit offsets and sizes for each field in the IPv4 header and flag (RFC 791). 
 * @par Memory Layout (Offset and Size in Bits) 
 * | Offset | Size | Field               | 
 * |--------|------|---------------------| 
 * | 0      | 4    | Version             | 
 * | 4      | 4    | IPv4 Header Length  | 
 * | 8      | 3    | Precedence          | 
 * | 11     | 1    | Delay               | 
 * | 12     | 1    | Throughput          | 
 * | 13     | 1    | Reliability         | 
 * | 14     | 1    | FAFO Reserved Bit 0 | 
 * | 15     | 1    | FAFO Reserved Bit 1 |  
 * | 16     | 16   | Total Length        | 
 * | 32     | 16   | Identification      | 
 * | 48     | 1    | TOS Reserved        | 
 * | 49     | 1    | DF                  | 
 * | 50     | 1    | MF                  | 
 * | 51     | 13   | Fragment Offset     | 
 * | 64     | 8    | Time to Live        | 
 * | 72     | 8    | Protocol            | 
 * | 80     | 16   | Header Checksum     | 
 * | 96     | 32   | Source Address      | 
 * | 128    | 32   | Destination Address | 
 * Total size: 20 bytes (without options). 
 * 
 */ 
// Bit offsets for each IPv4 header field 
constexpr std::uint8_t BIT_OFFSET_IPV4_VERSION             = 0;  // high nibble 
constexpr std::uint8_t BIT_OFFSET_IPV4_HEADER_LENGTH       = 4;  // low nibble 
constexpr std::uint8_t BIT_OFFSET_IPV4_PRECEDENCE          = 8; 
constexpr std::uint8_t BIT_OFFSET_IPV4_DELAY               = 11; 
constexpr std::uint8_t BIT_OFFSET_IPV4_THROUGHPUT          = 12; 
constexpr std::uint8_t BIT_OFFSET_IPV4_RELIABILITY         = 13; 
constexpr std::uint8_t BIT_OFFSET_IPV4_FAFO_RESERVED0      = 14; 
constexpr std::uint8_t BIT_OFFSET_IPV4_FAFO_RESERVED1      = 15; 
constexpr std::uint8_t BIT_OFFSET_IPV4_TOTAL_LENGTH        = 16; 
constexpr std::uint8_t BIT_OFFSET_IPV4_IDENTIFICATION      = 32; 
constexpr std::uint8_t BIT_OFFSET_IPV4_TOS_RESERVED        = 48; 
constexpr std::uint8_t BIT_OFFSET_IPV4_DF                  = 49; 
constexpr std::uint8_t BIT_OFFSET_IPV4_MF                  = 50; 
constexpr std::uint8_t BIT_OFFSET_IPV4_FRAGMENT_OFFSET     = 51; 
constexpr std::uint8_t BIT_OFFSET_IPV4_TIME_TO_LIVE        = 64; 
constexpr std::uint8_t BIT_OFFSET_IPV4_PROTOCOL            = 72; 
constexpr std::uint8_t BIT_OFFSET_IPV4_HEADER_CHECKSUM     = 80; 
constexpr std::uint8_t BIT_OFFSET_IPV4_SOURCE_ADDRESS      = 96; 
constexpr std::uint8_t BIT_OFFSET_IPV4_DESTINATION_ADDRESS = 128; 

// Bit sizes for each IPv4 header field 
constexpr std::uint8_t BIT_SIZE_IPV4_VERSION               = 4;  // high nibble 
constexpr std::uint8_t BIT_SIZE_IPV4_HEADER_LENGTH         = 4;  // low nibble 
constexpr std::uint8_t BIT_SIZE_IPV4_PRECEDENCE            = 3; 
constexpr std::uint8_t BIT_SIZE_IPV4_DELAY                 = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_THROUGHPUT            = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_RELIABILITY           = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_FAFO_RESERVED0        = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_FAFO_RESERVED1        = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_TOTAL_LENGTH          = 16; 
constexpr std::uint8_t BIT_SIZE_IPV4_IDENTIFICATION        = 16; 
constexpr std::uint8_t BIT_SIZE_IPV4_TOS_RESERVED          = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_DF                    = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_MF                    = 1; 
constexpr std::uint8_t BIT_SIZE_IPV4_FRAGMENT_OFFSET       = 13; 
constexpr std::uint8_t BIT_SIZE_IPV4_TIME_TO_LIVE          = 8; 
constexpr std::uint8_t BIT_SIZE_IPV4_PROTOCOL              = 8; 
constexpr std::uint8_t BIT_SIZE_IPV4_HEADER_CHECKSUM       = 16; 
constexpr std::uint8_t BIT_SIZE_IPV4_SOURCE_ADDRESS        = 32; 
constexpr std::uint8_t BIT_SIZE_IPV4_DESTINATION_ADDRESS   = 32; 




/// Version and header length: Version 
constexpr std::uint8_t VERSION                             = 4; // Version 4  

/// Version and header length: Header Length in Words 
constexpr std::uint8_t HEADER_LENGTH                       = 5;  

/// Type of service: Precedense   
constexpr std::uint8_t PRECEDENCE_NETWORK_CONTROL          = 0b11100000; 
constexpr std::uint8_t PRECEDENCE_INTERNETWORK_CONTROL     = 0b11000000; 
constexpr std::uint8_t PRECEDENCE_CRITIC_ECP               = 0b10100000;  
constexpr std::uint8_t PRECEDENCE_FLASH_OVERRIDE           = 0b10000000; 
constexpr std::uint8_t PRECEDENCE_FLASH                    = 0b01100000; 
constexpr std::uint8_t PRECEDENCE_IMMEDIATE                = 0b01000000; 
constexpr std::uint8_t PRECEDENCE_PRIORITY                 = 0b00100000; 
constexpr std::uint8_t PRECEDENCE_ROUTINE                  = 0b00000000; 

/// Type of service: Delay   
constexpr std::uint8_t DELAY_NORMAL                        = 0b00000000; 
constexpr std::uint8_t DELAY_LOW                           = 0b00010000;  

/// Type of service: Throughput 
constexpr std::uint8_t THROUGHPUT_NORMAL                   = 0b00000000; 
constexpr std::uint8_t THROUGHPUT_HIGH                     = 0b00001000; 

/// Type of service: Reliability 
constexpr std::uint8_t RELIABILITY_NORMAL                  = 0b00000000;  
constexpr std::uint8_t RELIABILITY_HIGH                    = 0b00000100;  

/// Type of service: Reserved Bits 
constexpr std::uint8_t TOS_RESERVED                        = 0b00000000; 

/// Flags and fragment offset: Reserved 
constexpr std::array<std::uint8_t, 2> FAFO_RESERVED0       = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> FAFO_RESERVED1       = {0b00000000, 0b00000000}; 

/// Flags and fragment offset: Don't Fragment (DF) 
constexpr std::array<std::uint8_t, 2> MD_MAY_FRAGMENT      = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> MD_DONT_FRAGMENT     = {0b01000000, 0b00000000}; 

/// Flags and fragment offset: More Fragments (MF) 
constexpr std::array<std::uint8_t, 2> MF_MORE_FRAGMENTS    = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> MF_LAST_FRAGMENT     = {0b00100000, 0b00000000};  




/** 
 * @brief Extracts a sequence of bits from an IPv4 header starting at a specified bit offset, 
 *        and copies them into a provided buffer as a contiguous bit sequence. 
 *  
 * This function treats the IPv4 header as a byte array, extracts `binarySize` bits starting 
 * from `binaryOffset` bit position, and packs them into the output buffer (`dataBuffer`), 
 * with the most significant bit of each byte filled first. The output buffer is zeroed out 
 * before packing. 
 * 
 * @param ipv4Header   The IPv4 header to extract bits from. 
 * @param binaryOffset The bit offset within the IPv4 header to start extraction (0-based). 
 * @param binarySize   The number of bits to extract. 
 * @param dataBuffer   The output buffer to hold the extracted bits, provided as a std::span. 
 *                     Must be large enough to hold `binarySize` bits (rounded up to bytes). 
 * 
 */ 
inline void GetDataWithBinaryOffsetAndSize(const Ipv4Header& ipv4Header, 
                                    const std::uint8_t binaryOffset, 
                                    const std::uint8_t binarySize, 
                                    std::span<std::uint8_t> dataBuffer); 
{ 
    // Zero out the output buffer 
    std::fill(dataBuffer.begin(), dataBuffer.end(), 0); 

    // Treat the header as a byte array without copying 
    const std::uint8_t* headerBytes = reinterpret_cast<const std::uint8_t*>(&ipv4Header); 

    // Extract bits 
    for (std::uint16_t bit = 0; bit < binarySize; ++bit) 
    { 
        std::uint16_t srcBitIndex = binaryOffset + bit; 
        std::uint8_t srcByteIndex = srcBitIndex / 8; 
        std::uint8_t srcBitOffset = 7 - (srcBitIndex % 8);  
        std::uint8_t bitValue = (headerBytes[srcByteIndex] >> srcBitOffset) & 0x01; 
        std::uint8_t dstByteIndex = bit / 8; 
        std::uint8_t dstBitOffset = 7 - (bit % 8);  
        dataBuffer[dstByteIndex] |= (bitValue << dstBitOffset); 

    } 

}  




/**  
 * @brief Extracts the IPv4 flags and fields from the IPv4 header and stores it in the provided data buffer.  
 * 
 * This function extracts the version from the IPv4 header by using GetDataWithBinaryOffsetAndSize and places it into the  
 * provided data buffer in big endian order. The version is extracted from the first 4 bits of the `version_and_header_length` field. 
 * 
 * @param ipv4Header The IPv4 header to extract the version from. 
 * @param dataBuffer The output buffer to hold the extracted version, provided as a std::span. 
 */ 
void GetVersion(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetHeaderLengthInWords(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetPrecedence(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetDelay(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetThroughput(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetReliability(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetTosReserved0(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetTosReserved1(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetTotalLength(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetIdentifier(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetFafoReserved(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetDf(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetMf(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetFragmentOffset(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetTimeToLive(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetProtocol(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetHeaderChecksum(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetSourceAddress(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer); 
void GetDestinationAddress(const Ipv4Header& ipv4Header, std::span<std::uint8_t> dataBuffer);  






} // namespace octo_ipv4  

} // namespace octo_network 

#endif // OCTO_HPP 



