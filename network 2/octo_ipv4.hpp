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

/** 
 * 
 * @brief Represents an IPv4 headers memmory layout according to RFC 791. 
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
 * 
 * @par Memory Layout (Offset and Size in Bits) 
 * | Offset | Size | Field                | 
 * |--------|------|----------------------| 
 * | 0      | 4    | Version              | 
 * | 4      | 4    | IPv4 Header Length   | 
 * | 8      | 3    | Precedence           | 
 * | 11     | 1    | Delay                | 
 * | 12     | 1    | Throughput           | 
 * | 13     | 1    | Reliability          | 
 * | 14     | 1    | FAFO* Reserved Bit 0 | 
 * | 15     | 1    | FAFO Reserved Bit 1  |  
 * | 16     | 16   | Total Length         | 
 * | 32     | 16   | Identification       | 
 * | 48     | 1    | TOS** Reserved       |    
 * | 49     | 1    | DF                   | 
 * | 50     | 1    | MF                   | 
 * | 51     | 13   | Fragment Offset      | 
 * | 64     | 8    | Time to Live         | 
 * | 72     | 8    | Protocol             | 
 * | 80     | 16   | Header Checksum      | 
 * | 96     | 32   | Source Address       | 
 * | 128    | 32   | Destination Address  | 
 * Total size: 20 bytes (without options). 
 * 
 * * FAFO (Flags and fragmentation offset) 
 * ** TOS(Type of service) 
 */  

namespace octo_network 
{ 

namespace ipv4 
{ 

namespace container 
{ 

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

} // namespace container 




namespace offset 
{ 

// Bit offsets for each IPv4 header field 
constexpr std::uint8_t VERSION             = 0;  // high nibble 
constexpr std::uint8_t HEADER_LENGTH       = 4;  // low nibble 
constexpr std::uint8_t PRECEDENCE          = 8; 
constexpr std::uint8_t DELAY               = 11; 
constexpr std::uint8_t THROUGHPUT          = 12; 
constexpr std::uint8_t RELIABILITY         = 13; 
constexpr std::uint8_t FAFO_RESERVED0      = 14; 
constexpr std::uint8_t FAFO_RESERVED1      = 15; 
constexpr std::uint8_t TOTAL_LENGTH        = 16; 
constexpr std::uint8_t IDENTIFICATION      = 32; 
constexpr std::uint8_t TOS_RESERVED        = 48; 
constexpr std::uint8_t DF                  = 49; 
constexpr std::uint8_t MF                  = 50; 
constexpr std::uint8_t FRAGMENT_OFFSET     = 51; 
constexpr std::uint8_t TIME_TO_LIVE        = 64; 
constexpr std::uint8_t PROTOCOL            = 72; 
constexpr std::uint8_t HEADER_CHECKSUM     = 80; 
constexpr std::uint8_t SOURCE_ADDRESS      = 96; 
constexpr std::uint8_t DESTINATION_ADDRESS = 128; 

} // namespace offset 




namespace size 
{ 

// Bit sizes for each IPv4 header field 
constexpr std::uint8_t VERSION               = 4;  // high nibble 
constexpr std::uint8_t HEADER_LENGTH         = 4;  // low nibble 
constexpr std::uint8_t PRECEDENCE            = 3; 
constexpr std::uint8_t DELAY                 = 1; 
constexpr std::uint8_t THROUGHPUT            = 1; 
constexpr std::uint8_t RELIABILITY           = 1; 
constexpr std::uint8_t FAFO_RESERVED0        = 1; 
constexpr std::uint8_t FAFO_RESERVED1        = 1; 
constexpr std::uint8_t TOTAL_LENGTH          = 16; 
constexpr std::uint8_t IDENTIFICATION        = 16; 
constexpr std::uint8_t TOS_RESERVED          = 1; 
constexpr std::uint8_t DF                    = 1; 
constexpr std::uint8_t MF                    = 1; 
constexpr std::uint8_t FRAGMENT_OFFSET       = 13; 
constexpr std::uint8_t TIME_TO_LIVE          = 8; 
constexpr std::uint8_t PROTOCOL              = 8; 
constexpr std::uint8_t HEADER_CHECKSUM       = 16; 
constexpr std::uint8_t SOURCE_ADDRESS        = 32; 
constexpr std::uint8_t DESTINATION_ADDRESS   = 32; 

} // namespace size 




namespace bitfields 
{ 

/// Type of service:    
constexpr std::uint8_t PRECEDENCE_NETWORK_CONTROL          = 0b11100000; 
constexpr std::uint8_t PRECEDENCE_INTERNETWORK_CONTROL     = 0b11000000; 
constexpr std::uint8_t PRECEDENCE_CRITIC_ECP               = 0b10100000;  
constexpr std::uint8_t PRECEDENCE_FLASH_OVERRIDE           = 0b10000000; 
constexpr std::uint8_t PRECEDENCE_FLASH                    = 0b01100000; 
constexpr std::uint8_t PRECEDENCE_IMMEDIATE                = 0b01000000; 
constexpr std::uint8_t PRECEDENCE_PRIORITY                 = 0b00100000; 
constexpr std::uint8_t PRECEDENCE_ROUTINE                  = 0b00000000; 
constexpr std::uint8_t DELAY_NORMAL                        = 0b00000000; 
constexpr std::uint8_t DELAY_LOW                           = 0b00010000;  
constexpr std::uint8_t THROUGHPUT_NORMAL                   = 0b00000000; 
constexpr std::uint8_t THROUGHPUT_HIGH                     = 0b00001000; 
constexpr std::uint8_t RELIABILITY_NORMAL                  = 0b00000000;  
constexpr std::uint8_t RELIABILITY_HIGH                    = 0b00000100;  
constexpr std::uint8_t TOS_RESERVED                        = 0b00000000; 

/// Flags and fragment offset:  
constexpr std::array<std::uint8_t, 2> FAFO_RESERVED0       = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> FAFO_RESERVED1       = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> DF_MAY_FRAGMENT      = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> DF_DONT_FRAGMENT     = {0b01000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> MF_MORE_FRAGMENTS    = {0b00000000, 0b00000000}; 
constexpr std::array<std::uint8_t, 2> MF_LAST_FRAGMENT     = {0b00100000, 0b00000000};  

} // namespace bitfields  




namespace utility 
{ 

/**  
 * @brief Extracts the IPv4 flags and fields from the IPv4 header and stores it in the provided data buffer.  
 * 
 * This function extracts the version from the IPv4 header by using GetDataWithBinaryOffsetAndSize and places it into the  
 * provided data buffer in big endian order. The version is extracted from the first 4 bits of the `version_and_header_length` field. 
 * 
 * @param ipv4HeaderByteArray The IPv4 header as a raw byte array to extract the bits from. 
 * @param outputBuffer The output buffer to hold the extracted version, provided as a std::span. 
 */ 
void GetVersion(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetHeaderLengthInWords(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetPrecedence(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetDelay(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetThroughput(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetReliability(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetTosReserved0(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetTosReserved1(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetTotalLength(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetIdentifier(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetFafoReserved(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetDf(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetMf(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetFragmentOffset(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetTimeToLive(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetProtocol(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetHeaderChecksum(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetSourceAddress(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetDestinationAddress(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer);  




/**  
 * @brief Extracts the IPv4 flags and fields from the IPv4 header and stores it in the provided data buffer.  
 * 
 * This function extracts the version from the IPv4 header by using GetDataWithBinaryOffsetAndSize and places it into the  
 * provided data buffer in big endian order. The version is extracted from the first 4 bits of the `version_and_header_length` field. 
 * 
 * @param ipv4HeaderByteArray The IPv4 header as a raw byte array to extract the bits from. 
 * @param outputBuffer The output buffer to hold the extracted version, provided as a std::span. 
 */ 
void changeVersion(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeHeaderLengthInWords(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changePrecedence(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeDelay(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeThroughput(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeReliability(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeTosReserved0(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeTosReserved1(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeTotalLength(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void changeIdentifier(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetFafoReserved(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetDf(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetMf(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetFragmentOffset(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetTimeToLive(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetProtocol(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetHeaderChecksum(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetSourceAddress(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer); 
void GetDestinationAddress(const std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> outputBuffer);  


} // namespace utility 

} // namespace ipv4  

} // namespace octo_network 

#endif // OCTO_HPP 

















