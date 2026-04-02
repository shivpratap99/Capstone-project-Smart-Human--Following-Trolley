# Capstone-project-Smart-Human--Following-Trolley
This project is an autonomous human-following trolley built using an Arduino Uno, ultrasonic sensors, and an L298N motor driver. The system is designed to automatically follow a person while maintaining a safe and consistent distance.

The trolley uses ultrasonic sensors to continuously measure the distance between the user and the robot. Based on this distance data, the Arduino Uno processes the readings and controls the DC motors through the L298N motor driver. The trolley adjusts its movement in real time, allowing it to move forward, turn left, or turn right to stay aligned with the user.

The system maintains an optimal following distance by adjusting the motor speed using PWM control. If the person moves farther away, the trolley increases its speed to follow. If the person gets too close, the trolley slows down while still continuing to track the user smoothly.

This project demonstrates the integration of embedded systems, sensor-based navigation, and motor control to create a simple yet effective autonomous robotic system. Such a system can be useful in applications where hands-free transportation is needed.

Key Features:
  
  
    Automatic human-following behavior
  
    Distance-based speed adjustment
  
    Left and right directional tracking
  
    Smooth motor control using PWM
  
    Simple and efficient Arduino-based design


Technologies Used:

    Arduino Uno
  
     HC-SR04 Ultrasonic Sensors
  
    L298N Motor Driver
  
    DC Motors
  
    C / Arduino Programming

  
Applications:

    Smart shopping trolley
  
    Luggage carrying robot
  
    Warehouse assistance robot
  
    Autonomous service trolley
