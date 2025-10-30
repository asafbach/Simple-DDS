# Define the core DDS library
add_library(dds_core
    DomainParticipant.cpp
    DomainParticipantFactory.cpp
    Publisher.cpp
    Subscriber.cpp  
    Topic.cpp 
    qos/QosProfiles.cpp      
)

# Specify the public include directory for the library
target_include_directories(dds_core PUBLIC "${PROJECT_SOURCE_DIR}/include")
