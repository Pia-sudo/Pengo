#Especificar donde se encuentran los ficheros cpp a compilar
target_sources(libModulos PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/entidades/pengo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/entidades/bloque.cpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/entidades/snowBee.cpp"      
    "${CMAKE_CURRENT_SOURCE_DIR}/estados/status.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/estados/juegoStatus.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fachada/motorGrafico.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/fachada/sprite.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mundo/mapa.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mundo/mundo.cpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml/tinyxml.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml/tinystr.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml/tinyxmlerror.cpp"    
    "${CMAKE_CURRENT_SOURCE_DIR}/tinyxml/tinyxmlparser.cpp"    
)

#Y donde se encuentran los .h
target_include_directories(libModulos PUBLIC 
"${CMAKE_CURRENT_SOURCE_DIR/../include}"
)

