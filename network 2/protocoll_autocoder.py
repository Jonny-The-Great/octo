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


{paramSizes} 


} 
//SIZE/////////// 
///////////////// 




///////////////// 
//OFFSET///////// 
namespace offset 
{  


{paramOffset} 


} 
//OFFSET///////// 
///////////////// 




///////////////// 
//CONTAINER////// 
namespace offset 
{ 


{paramContainer} 


} 
//CONTAINER/////// 
////////////////// 







""")  
