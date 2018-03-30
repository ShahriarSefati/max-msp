cmake_minimum_required (VERSION 3.0)

project (UDP)

set(BOOST_LIBRARYDIR C:/boost/lib)

message(${BOOST_LIBRARYDIR})
find_package(Boost REQUIRED COMPONENTS system)

if(NOT Boost_LIBRARY_DIRS)
  message("Boost libraries not found")
endif()
  
set(OSCPP_INCLUDE_DIRS "" CACHE PATH "Path to oscpp")
if (NOT OSCPP_INCLUDE_DIRS)
  message(FATAL_ERROR "Set the oscpp include directory")
endif()

message("boost lib dir: ${BOOST_LIBRARY_DIRS}")

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OSCPP_INCLUDE_DIRS}
  )
 
link_directories("C:/boost_1_66_0/stage/lib/")
   
add_executable (boost boostTest.cpp udpPacket.cpp tnyosc.hpp udpPacket.h)
target_link_libraries(boost 
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_System_Library}
)  
