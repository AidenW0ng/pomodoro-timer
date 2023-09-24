cmake_minimum_required(VERSION 3.12)  # You can adjust the required version

project(PomodoroProject)

# Add your source files here
add_executable(window
   src/main.cpp  # Add all your source files here
)
# Specify the include directories
target_include_directories(window PRIVATE
   /opt/homebrew/opt/sfml/include #absolute path
)

# Specify the SFML library directory
link_directories(/opt/homebrew/Cellar/sfml/2.6.0/lib)

# Add any dependencies here (e.g., SFML)
target_link_libraries(window PRIVATE
"/opt/homebrew/opt/sfml/lib/libsfml-graphics.dylib"
   "/opt/homebrew/opt/sfml/lib/libsfml-window.dylib"
   "/opt/homebrew/opt/sfml/lib/libsfml-system.dylib")
