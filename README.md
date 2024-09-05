#ros2_plot

​		A ROS2 package that leverages shared memory to visualize waveforms using [PlotJuggler](https://github.com/facontidavide/PlotJuggler), a state-of-the-art tool for real-time data analysis and visualization. This package allows you to work with high-performance, advanced visualization capabilities without being restricted to simulators or tools that are ROS-centric or lack ROS support.

# 0 Optional

```bash
sudo apt install ros-{ROS-DISTRO}-plotjuggler-ros
```

# 1 Build

```bash
mkdir -p ros2_plot_ws/src && cd ros2_plot_ws/src
git clone https://github.com/HuNingHe/ros2_plot.git
cd ../
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
```

# 2 Usage

```bash
source install/setup.bash
ros2 run ros2_plot ros2_plot
```

​		Run another program, such as the ankle controller [closed_loop_ankle](https://github.com/HuNingHe/closed_loop_ankle). Once the terminal displays “[ros2_plot]: Start publishing data”, it indicates that the data in shared memory has been published and you can proceed to visualize it using PlotJuggler.

​		You can refer to the ankle controller [closed_loop_ankle](https://github.com/HuNingHe/closed_loop_ankle) as a guide to writing your own program.

# 3 Test

​		Tested exclusively on Ubuntu 24.04 and ROS2 Jazzy. Please report any bugs you encounter.
