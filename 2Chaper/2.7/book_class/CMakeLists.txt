cmake_minimum_required(VERSION 2.8.3)
project(book_class)

find_package(catkin REQUIRED COMPONENTS
  message_generation roscpp rospy std_msgs dynamic_reconfigure)

add_service_files(FILES
  PassWord.srv
)

generate_messages(DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
  message_runtime
)

include_directories(
  include ${catkin_INCLUDE_DIRS}
# include
# ${catkin_INCLUDE_DIRS}
)

add_executable(book_class
  src/book_class.cpp
)
add_dependencies(book_class ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(book_class
  ${catkin_LIBRARIES}
)