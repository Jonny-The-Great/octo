/** 
 * @file octo_ipv4.hpp 
 * @brief Defines structures and constants and functions for IPv4 header manipulation as per RFC 791: https://www.rfc-editor.org/rfc/rfc791#ref-9. 
 * 
 * 
 * Represents an IPv4 headers memory layout according to RFC 791: 
 * 
 * @par Memory Layout (Offset and Size in Bytes) 
 * | Offset | Size | Field                     | 
 * |--------|------|---------------------------| 
 * | 0      | 1    | Version and header length | 
 * | 1      | 1    | Type of service           | 
 * | 2      | 2    | Total length              | 
 * | 4      | 2    | Identification            | 
 * | 6      | 2    | Flags and fragment offset | 
 * | 8      | 1    | Time to live              | 
 * | 9      | 1    | Protocol                  | 
 * | 10     | 2    | Header checksum           | 
 * | 12     | 4    | Source address            | 
 * | 16     | 4    | Destination address       | 
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
 * | 14     | 1    | FAFO* Reserved       | 
 * | 15     | 16   | Total Length         | 
 * | 31     | 16   | Identification       | 
 * | 47     | 1    | TOS** Reserved bit 0 |    
 * | 48     | 1    | TOS** Reserved bit 1 |    
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
 * ** TOS(Type of service).  
 * 
 * @note All structures are packed to ensure strict conformance to byte alignment as defined in RFC 791. 
 *       The usage of raw byte arrays, etc. allows for system-endian independent access. 
 */ 
#ifndef OCTO_IPV4_HPP 
#define OCTO_IPV4_HPP 

#include <cstdint> 
#include <array> 
#include <span> 
#include <algorithm>  
#include "octo_netcommons.hpp" 

namespace octo_network 
{ 

namespace ipv4 
{ 




namespace container 
{ 

#pragma pack(push, 1) // Ensure 1-byte alignment for the structure 
struct Ipv4Header 
{ 
    std::array<std::uint8_t, 20> ipv4Header;  
    
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
constexpr std::uint8_t TOTAL_LENGTH        = 16; 
constexpr std::uint8_t IDENTIFICATION      = 32; 
constexpr std::uint8_t TOS_RESERVED0       = 48; 
constexpr std::uint8_t TOS_RESERVED1       = 15; 
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
constexpr std::uint8_t DELAY_LOW                           = 0b10000000;  
constexpr std::uint8_t THROUGHPUT_NORMAL                   = 0b00000000; 
constexpr std::uint8_t THROUGHPUT_HIGH                     = 0b10000000; 
constexpr std::uint8_t RELIABILITY_NORMAL                  = 0b00000000;  
constexpr std::uint8_t RELIABILITY_HIGH                    = 0b10000000;  
constexpr std::uint8_t TOS_RESERVED0                        = 0b00000000; 
constexpr std::uint8_t TOS_RESERVED1       = 0b00000000; 

/// Flags and fragment offset:  
constexpr std::uint8_t FAFO_RESERVED       = 0b00000000; 
constexpr std::uint8_t DF_MAY_FRAGMENT      = 0b00000000; 
constexpr std::uint8_t DF_DONT_FRAGMENT     = 0b10000000; 
constexpr std::uint8_t MF_MORE_FRAGMENTS    = 0b00000000; 
constexpr std::uint8_t MF_LAST_FRAGMENT     = 0b10000000;  

} // namespace bitfields  




namespace utility 
{ 

/**  
 * @brief Extracts the IPv4 flags and fields from the IPv4 header and stores it in the provided data buffer.  
 * 
 * This function extracts the flags and fields from the IPv4 header by using GetDataWithBinaryOffsetAndSize and places it into the  
 * provided data buffer.  
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
 * @brief Changes flags and fields from the IPv4 header.  
 * 
 * This function changes the IPv4 header by using ChangeDataWithBinaryOffsetAndSize    
 * 
 * @param ipv4HeaderByteArray The IPv4 header as a raw byte array to extract the bits from. 
 * @param bitfield the bitfield to apply, provided as a std::span. 
 */ 
void ChangeVersion(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeHeaderLengthInWords(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangePrecedence(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeDelay(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeThroughput(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeReliability(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeTosReserved0(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeTosReserved1(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeTotalLength(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeIdentifier(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeFafoReserved(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeDf(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeMf(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeFragmentOffset(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeTimeToLive(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeProtocol(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeHeaderChecksum(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeSourceAddress(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield); 
void ChangeDestinationAddress(std::array<std::uint8_t>& ipv4HeaderByteArray, std::span<std::uint8_t> bitfield);  


} // namespace utility 




} // namespace ipv4  

} // namespace octo_network 

#endif // OCTO_IPV4_HPP 


























