/**
 * @file octo_in.cpp
 * @brief Implements field extraction utilities for the IPv4 header defined in octo_in.hpp
 */
#include "octo_ipv4.hpp" 

namespace octo_network 
{ 

namespace octo_ipv4 
{ 




/**  
 * @brief Extracts the IPv4 flags and fields from the IPv4 header and stores it in the provided data buffer.  
 * 
 * This function extracts the version from the IPv4 header by using GetDataWithBinaryOffsetAndSize and places it into the  
 * provided data buffer in big endian order. The version is extracted from the first 4 bits of the `version_and_header_length` field. 
 * 
 * @param ipv4Header The IPv4 header to extract the version from. 
 * @param dataBuffer The output buffer to hold the extracted version, provided as a std::span. 
 */ 
#define DEFINE_GETTER(FUNC_NAME, OFFSET, SIZE)                               \
    void FUNC_NAME(const Ipv4Header& ipv4Header, std::span<std::uint8_t> buffer) \
    {                                                                        \
        GetDataWithBinaryOffsetAndSize(ipv4Header, OFFSET, SIZE, buffer);   \
    } 

DEFINE_GETTER(GetVersion, BIT_OFFSET_IPV4_VERSION, BIT_SIZE_IPV4_VERSION) 
DEFINE_GETTER(GetHeaderLength, BIT_OFFSET_IPV4_HEADER_LENGTH, BIT_SIZE_IPV4_HEADER_LENGTH) 
DEFINE_GETTER(GetTosPrecedence, BIT_OFFSET_IPV4_TOS_PRECEDENCE, BIT_SIZE_IPV4_TOS_PRECEDENCE) 
DEFINE_GETTER(GetTosDelay, BIT_OFFSET_IPV4_TOS_DELAY, BIT_SIZE_IPV4_TOS_DELAY) 
DEFINE_GETTER(GetTosThroughput, BIT_OFFSET_IPV4_TOS_THROUGHPUT, BIT_SIZE_IPV4_TOS_THROUGHPUT) 
DEFINE_GETTER(GetTosReliability, BIT_OFFSET_IPV4_TOS_RELIABILITY, BIT_SIZE_IPV4_TOS_RELIABILITY) 
DEFINE_GETTER(GetTosReservedBit0, BIT_OFFSET_IPV4_TOS_RESERVED, 1)  
DEFINE_GETTER(GetTosReservedBit1, BIT_OFFSET_IPV4_TOS_RESERVED + 1, 1)  
DEFINE_GETTER(GetTotalLength, BIT_OFFSET_IPV4_TOTAL_LENGTH, BIT_SIZE_IPV4_TOTAL_LENGTH) 
DEFINE_GETTER(GetIdentification, BIT_OFFSET_IPV4_IDENTIFICATION, BIT_SIZE_IPV4_IDENTIFICATION) 
DEFINE_GETTER(GetFafoReserved, BIT_OFFSET_IPV4_FAFO_RESERVED0, 1)   
DEFINE_GETTER(GetDF, BIT_OFFSET_IPV4_DF, 1)  
DEFINE_GETTER(GetMF, BIT_OFFSET_IPV4_MF, 1)  
DEFINE_GETTER(GetFragmentOffset, BIT_OFFSET_IPV4_FRAGMENT_OFFSET, BIT_SIZE_IPV4_FRAGMENT_OFFSET) 
DEFINE_GETTER(GetTimeToLive, BIT_OFFSET_IPV4_TIME_TO_LIVE, BIT_SIZE_IPV4_TIME_TO_LIVE) 
DEFINE_GETTER(GetProtocol, BIT_OFFSET_IPV4_PROTOCOL, BIT_SIZE_IPV4_PROTOCOL) 
DEFINE_GETTER(GetHeaderChecksum, BIT_OFFSET_IPV4_HEADER_CHECKSUM, BIT_SIZE_IPV4_HEADER_CHECKSUM) 
DEFINE_GETTER(GetSourceAddress, BIT_OFFSET_IPV4_SOURCE_ADDRESS, BIT_SIZE_IPV4_SOURCE_ADDRESS) 
DEFINE_GETTER(GetDestinationAddress, BIT_OFFSET_IPV4_DESTINATION_ADDRESS, BIT_SIZE_IPV4_DESTINATION_ADDRESS) 

#undef DEFINE_GETTER 




} // namespace octo_ipv4 

} // namespace octo_network 



