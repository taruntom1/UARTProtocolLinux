/*
 * @file LinuxUARTProtocol.h
 * @brief Header file for the LinuxUARTProtocol class, providing UART communication utilities on Linux.
 */

 #ifndef LINUX_UART_PROTOCOL_H
 #define LINUX_UART_PROTOCOL_H
 
 #include <stdint.h>
 #include <termios.h>
 #include <string>
 
 /**
  * @struct protocol_config
  * @brief Configuration structure for LinuxUARTProtocol.
  *
  * This structure holds the configuration parameters required to initialize
  * the LinuxUARTProtocol class, such as baud rate, device file, and buffer size.
  */
 struct protocol_config
 {
     std::string device = "/dev/ttyUSB0"; /**< UART device file. */
     int baudRate = 115200;                /**< Baud rate for UART communication. */
     uint16_t bufferSize = 1024;           /**< Size of the UART buffer. */
     uint8_t header = 0xAA;                /**< Header byte for the protocol. */
     uint8_t maxPacketSize = 100;          /**< Maximum size of a data packet. */
 };
 
 /**
  * @class LinuxUARTProtocol
  * @brief Provides a protocol layer for UART communication on Linux.
  *
  * The LinuxUARTProtocol class encapsulates UART communication functionality,
  * including sending and receiving commands and data, with header validation.
  */
 class LinuxUARTProtocol
 {
 private:
     protocol_config config; /**< Configuration settings for the protocol. */
     int serial_fd;          /**< File descriptor for the serial port. */
     struct termios tty;     /**< Terminal settings structure. */
 
     /**
      * @brief Configures the serial port.
      * @return True if configuration is successful, false otherwise.
      */
     bool configureSerialPort();
 
 public:
     /**
      * @brief Constructs a LinuxUARTProtocol object.
      * @param config Configuration settings for the protocol.
      */
     LinuxUARTProtocol(protocol_config config);
 
     /**
      * @brief Initializes the UART protocol with the specified configuration.
      * @return True if initialization is successful, false otherwise.
      */
     bool begin();
 
     /**
      * @brief Sends a command over UART.
      * @param commandType The type of command to send.
      */
     void SendCommand(const uint8_t &commandType);
 
     /**
      * @brief Sends data over UART.
      * @param data Pointer to the data array to send.
      * @param length Length of the data array.
      */
     void SendData(const uint8_t *data, const uint8_t length);
 
     /**
      * @brief Reads a command from UART.
      * @param commandType Reference to store the received command type.
      * @return True if a command was successfully read, false otherwise.
      */
     bool ReadCommand(uint8_t &commandType);
 
     /**
      * @brief Reads a command from UART with a timeout.
      * @param commandType Reference to store the received command type.
      * @param timeout Timeout duration in milliseconds.
      * @return True if a command was successfully read, false otherwise.
      */
     bool ReadCommand(uint8_t &commandType, uint32_t timeout);
 
     /**
      * @brief Reads data from UART with a timeout.
      * @param data Pointer to store the received data.
      * @param length Length of the data to read.
      * @param timeout Timeout duration in milliseconds.
      * @return True if data was successfully read, false otherwise.
      */
     bool ReadData(uint8_t *data, uint8_t length, uint32_t timeout);
 
     /**
      * @brief Reads data from UART.
      * @param data Pointer to store the received data.
      * @param length Length of the data to read.
      * @return True if data was successfully read, false otherwise.
      */
     bool ReadData(uint8_t *data, uint8_t length);
 
     /**
      * @brief Closes the UART connection.
      */
     void closeConnection();
 };
 
 #endif // LINUX_UART_PROTOCOL_H
 