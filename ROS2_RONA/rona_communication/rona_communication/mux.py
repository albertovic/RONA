import rclpy
from rclpy.node import Node
from std_msgs.msg import Float64MultiArray
from rclpy.time import Time

class CommandMultiplexer(Node):
    def __init__(self):
        super().__init__('command_multiplexer')
        self.subscription_nav2 = self.create_subscription(
            Float64MultiArray,
            '/kinematics_controller/commands_from_nav2',
            self.handle_nav2_commands,
            10)
        self.subscription_other = self.create_subscription(
            Float64MultiArray,
            '/kinematics_controller/commands_from_other',
            self.handle_other_commands,
            10)
        self.publisher = self.create_publisher(
            Float64MultiArray,
            '/simple_velocity_controller/commands', 
            10)
        
        # Usar un tiempo de prioridad para determinar cuánto tiempo tiene prioridad un comando
        self.last_nav2_command_time = None
        self.priority_duration = rclpy.duration.Duration(seconds=1)  # 1 segundo de prioridad

    def handle_nav2_commands(self, msg):
        self.last_nav2_command_time = self.get_clock().now()
        self.publisher.publish(msg)
        self.get_logger().info('Published command from Nav2')

    def handle_other_commands(self, msg):
        current_time = self.get_clock().now()
        if self.last_nav2_command_time is None or \
           (current_time - self.last_nav2_command_time) > self.priority_duration:
            self.publisher.publish(msg)
            self.get_logger().info('Published command from other source')

def main(args=None):
    rclpy.init(args=args)
    multiplexer_node = CommandMultiplexer()
    rclpy.spin(multiplexer_node)
    multiplexer_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
