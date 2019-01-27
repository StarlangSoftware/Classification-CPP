cmake_minimum_required(VERSION 3.12)
project(Classification)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(Classification Attribute/AttributeType.h Attribute/Attribute.h Attribute/BinaryAttribute.cpp Attribute/BinaryAttribute.h Attribute/DiscreteAttribute.cpp Attribute/DiscreteAttribute.h Attribute/DiscreteIndexedAttribute.cpp Attribute/DiscreteIndexedAttribute.h Attribute/ContinuousAttribute.cpp Attribute/ContinuousAttribute.h Instance/Instance.cpp Instance/Instance.h Instance/CompositeInstance.cpp Instance/CompositeInstance.h InstanceList/Partition.cpp InstanceList/Partition.h InstanceList/InstanceList.cpp InstanceList/InstanceList.h DataSet/DataDefinition.cpp DataSet/DataDefinition.h)
target_link_libraries(Classification Math)
add_executable(TestClassification Attribute/AttributeType.h Attribute/Attribute.h Attribute/BinaryAttribute.cpp Attribute/BinaryAttribute.h Attribute/DiscreteAttribute.cpp Attribute/DiscreteAttribute.h Attribute/DiscreteIndexedAttribute.cpp Attribute/DiscreteIndexedAttribute.h Attribute/ContinuousAttribute.cpp Attribute/ContinuousAttribute.h Instance/Instance.cpp Instance/Instance.h TestClassification.cpp InstanceList/Partition.cpp InstanceList/Partition.h InstanceList/InstanceList.cpp InstanceList/InstanceList.h DataSet/DataDefinition.cpp DataSet/DataDefinition.h)
target_link_libraries(TestClassification Math)
