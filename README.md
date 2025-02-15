# Ticket Inventory Manager  

This C++ program helps manage ticket inventory for a ticket office with two main functions:  

1. **Manage Air Tickets**  
   - View, add, modify, and delete ticket information  
   - Search for tickets by date or location  

2. **Manage Ticket Sale Records**  
   - Add ticket sale records  
   - Calculate commissions over a period of time  

## Features  
- Efficient ticket management with search functionality  
- Record-keeping for ticket sales and commission calculations  


## How to Run  
The program was tested on CodeBlocks (GNU GCC Compiler) and Visual Studio 2022 (C++ 14 – Local Window Debugger). CodeBlocks uses <string.h> while Visual Studio 2022  uses <string>.  You also have to include Shlwapi.lib for Visual Studio 2022  by these follwing statements:
You also have to include `Shlwapi.lib` for Visual Studio 2022 using the following statements:  

```cpp
#ifdef _MSC_VER
#pragma comment (lib, "Shlwapi.lib")
#endif
```
Make sure you have 3 text files (.txt) named domesticket, interticket and salerecord in the same directory as the program, if not, created and name them.
