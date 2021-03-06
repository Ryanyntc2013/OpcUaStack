
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
include_directories(
    ../inc
	${Boost_INCLUDE_DIRS}
)
file(GLOB OpcUaStackServer_SRC ./OpcUaStackServer/*/*.cpp)
add_library(OpcUaStackServer SHARED ${OpcUaStackServer_SRC})

target_link_libraries(
    OpcUaStackServer
    OpcUaStackCore
    ${CMAKE_DL_LIBS}
#    ${pthread}
    ${Boost_LIBRARIES}
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
file(GLOB INC_OpcUaStackServer_Server OpcUaStackServer/Server/*.h)
file(GLOB INC_OpcUaStackServer_AddressSpaceModel OpcUaStackServer/AddressSpaceModel/*.h)
file(GLOB INC_OpcUaStackServer_Application OpcUaStackServer/Application/*.h)
file(GLOB INC_OpcUaStackServer_InformationModel OpcUaStackServer/InformationModel/*.h)
file(GLOB INC_OpcUaStackServer_NodeSet OpcUaStackServer/NodeSet/*.h)
file(GLOB INC_OpcUaStackServer_SecureChannel OpcUaStackServer/SecureChannel/*.h)
file(GLOB INC_OpcUaStackServer_ServiceManager OpcUaStackServer/ServiceManager/*.h)
file(GLOB INC_OpcUaStackServer_ServiceSet OpcUaStackServer/ServiceSet/*.h)
file(GLOB INC_OpcUaStackServer_ServiceSetApplication OpcUaStackServer/ServiceSetApplication/*.h)


install(TARGETS OpcUaStackServer DESTINATION ${LIB_DIR}/OpcUaStack)
install(FILES ${INC_OpcUaStackServer_Server} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/Server)
install(FILES ${INC_OpcUaStackServer_AddressSpaceModel} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/AddressSpaceModel)
install(FILES ${INC_OpcUaStackServer_Application} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/Application)
install(FILES ${INC_OpcUaStackServer_InformationModel} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/InformationModel)
install(FILES ${INC_OpcUaStackServer_NodeSet} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/NodeSet)
install(FILES ${INC_OpcUaStackServer_SecureChannel} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/SecureChannel)
install(FILES ${INC_OpcUaStackServer_ServiceManager} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/ServiceManager)
install(FILES ${INC_OpcUaStackServer_ServiceSet} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/ServiceSet)
install(FILES ${INC_OpcUaStackServer_ServiceSetApplication} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaStackServer/ServiceSetApplication)

