def generate_netprotocol_code( 
    protocol_name: str, 
    header_description: str, 
    size_code: str, 
    offset_code: str, 
    container_code: str, 
    utility_code: str 
) -> str: 
    uppercase_protocol = protocol_name.upper() 
    lowercase_protocol = protocol_name.lower() 

template = f'''\  
{HeaderDescription} 
#ifndef NET_{uppercaseProtocolName}_HPP 
#define NET_{uppercaseProtocolName}_HPP 

#include <cstdint> 
#include <array> 
#incluse <span> 
#include "netcommons.hpp" 


///////////////// 
//NETSTACK/////// 
//{uppercaseProtocolName} 
////////////////// 
namespace netstack 
{  
namespace {lowercaseProtocolName}  
{  









///////////////// 
//SIZE/////////// 
namespace size 
{  


{sizeCode} 


} 
//SIZE/////////// 
///////////////// 




///////////////// 
//OFFSET///////// 
namespace offset 
{  


{offsetCode} 


} 
//OFFSET///////// 
///////////////// 




///////////////// 
//CONTAINER////// 
namespace offset 
{ 


{containerCode} 


} 
//CONTAINER/////// 
////////////////// 




///////////////// 
//UTILITY//////// 
namespace utility 
{ 


{utilityCode} 


} 
//UTILITY///////// 
////////////////// 











} 
} 
////////////////// 
//NETSTACK//////// 
//{upperCaseProtocolName} 
////////////////// 

#endif // NET_{uppercaseProtocolName}_HPP 




''' return template  
