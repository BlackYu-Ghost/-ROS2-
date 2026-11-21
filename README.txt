ROS 2 System Status Workspace
=============================

Purpose
-------
This directory is a ROS 2 workspace for publishing system resource statistics
and displaying them in a Qt window.

Source packages are in src/:
- status_interfaces: defines the SystemStatus ROS message.
- status_publisher: publishes CPU, memory, hostname, and network statistics
  on the "system_status" topic once per second.
- status_display: contains a Qt greeting program (hello_qt) and a Qt
  subscriber (sys_status_display) that displays SystemStatus messages.

Workspace directories
---------------------
- src/: package source code. Edit files here.
- build/: generated build files. Do not edit by hand.
- install/: built packages and environment setup scripts.
- log/: build and runtime logs.

Required environment
--------------------
- Ubuntu with ROS 2 Humble installed under /opt/ros/humble.
- colcon and ROS 2 build tools.
- Qt 5 Widgets development libraries (qtbase5-dev).
- Python psutil (python3-psutil), used by status_publisher.
- A graphical desktop session for the Qt programs.

Install missing dependencies on Ubuntu (if needed):

  sudo apt update
  sudo apt install python3-colcon-common-extensions python3-rosdep \
      qtbase5-dev python3-psutil

If rosdep has been initialized, package dependencies can also be installed
from the workspace root with:

  source /opt/ros/humble/setup.bash
  rosdep install --from-paths src --ignore-src -r -y

Build
-----
Run these commands from this directory:

  source /opt/ros/humble/setup.bash
  colcon build --symlink-install
  source install/setup.bash

After rebuilding, source install/setup.bash again in each new terminal before
running workspace packages.

Run
---
Open a terminal and source the ROS and workspace environments:

  source /opt/ros/humble/setup.bash
  source install/setup.bash

Start the publisher:

  ros2 run status_publisher sys_status_pub

Start the status display in another sourced terminal:

  ros2 run status_display sys_status_display

The simple Qt greeting window can be run with:

  ros2 run status_display hello_qt

Qt and Snap environment note
----------------------------
When a terminal inherits GTK_PATH from Snap-packaged VS Code (for example,
pointing into /snap/code/...), a Qt program may load incompatible libraries
and fail with a GLIBC_PRIVATE or libpthread symbol error. For that terminal,
run the Qt program with GTK_PATH removed:

  env -u GTK_PATH ros2 run status_display sys_status_display

For the greeting program, replace sys_status_display with hello_qt. This
removes GTK_PATH only for that command; it does not change system files or
permanently alter the shell environment. If the error persists, inspect
GTK_PATH and other library-related environment variables before changing
system libraries.
