############################################################################
# CMakeLists.txt file for building ROOT io/xmlparser package
# @author Pere Mato, CERN
############################################################################

# needed to propagate includes to rootling
include_directories(${LIBXML2_INCLUDE_DIR} ${LIBXML2_INCLUDE_DIRS})

ROOT_STANDARD_LIBRARY_PACKAGE(XMLParser
  HEADERS
     TDOMParser.h
     TSAXParser.h
     TXMLAttr.h
     TXMLDocument.h
     TXMLNode.h
     TXMLParser.h
  SOURCES
     src/TDOMParser.cxx
     src/TSAXParser.cxx
     src/TXMLAttr.cxx
     src/TXMLDocument.cxx
     src/TXMLNode.cxx
     src/TXMLParser.cxx
  DEPENDENCIES
    Core
)

target_link_libraries(XMLParser
  PRIVATE
    ${LIBXML2_LIBRARIES}
    $<$<PLATFORM_ID:Windows>:ws2_32.lib>
)
