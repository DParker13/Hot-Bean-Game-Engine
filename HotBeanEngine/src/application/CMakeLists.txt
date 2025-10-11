add_library(HotBeanEngine_Application STATIC
    application.cpp
)

add_subdirectory(managers)

target_link_libraries(HotBeanEngine_Application PUBLIC
    HotBeanEngine_Managers
)