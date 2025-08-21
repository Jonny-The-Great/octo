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
//NETSTACK//////// 
////////////////// 




""")  
