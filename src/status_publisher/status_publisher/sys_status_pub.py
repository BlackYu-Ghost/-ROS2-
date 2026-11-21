import rclpy
from rclpy.node import Node
from status_interfaces.msg import SystemStatus
import platform
import psutil

class SysStatusPublisher(Node):
    def __init__(self):
        super().__init__('sys_status_publisher')
        self.publisher_ = self.create_publisher(SystemStatus, 'system_status', 10)
        timer_period = 1.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)


        #self.status_msg = SystemStatus()
        #self.status_msg.cpu_usage = 0.0
        #self.status_msg.memory_usage = 0.0

    def timer_callback(self):
        # Here you would add code to update the status message with real data
        cpu_percent = psutil.cpu_percent()
        memory_info = psutil.virtual_memory()
        net_io_counters = psutil.net_io_counters()

        msg = SystemStatus()
        msg.stamp = self.get_clock().now().to_msg()
        msg.host_name = platform.node()
        msg.cpu_percent = cpu_percent
        msg.memory_percent = memory_info.percent
        msg.memory_total = memory_info.total / 1024 / 1024  # Convert to MB
        msg.memory_available = memory_info.available / 1024 / 1024  # Convert to MB
        msg.net_sent = net_io_counters.bytes_sent / 1024 / 1024
        msg.net_recv = net_io_counters.bytes_recv / 1024 / 1024
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: CPU Usage: {str(msg)}')

def main():
    rclpy.init()
    node = SysStatusPublisher()
    rclpy.spin(node)
    rclpy.shutdown()