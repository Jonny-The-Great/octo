print(r""" 
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




""")  
