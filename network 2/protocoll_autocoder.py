print(r""" 
#ifndef {protocolName} 
#define {protocolName} 

///////////////// 
//NETSTACK/////// 
namespace netstack 
{  




///////////////// 
//SIZE/////////// 
namespace size 
{  


{sizesCode} 


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
//NETSTACK//////// 
////////////////// 




""")  
