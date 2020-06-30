/*
 * UART.hpp
 *
 *  Created on: Apr 15, 2020
 *      Author: Ali AlSaibie
 *      Email:  ali.a@ku.edu.kw
 */

#ifndef DEVICE_UART_HPP_
#define DEVICE_UART_HPP_

#include "stm32f4xx_hal.h"
#include <cstring>
#include <string>
#include <cstdio>

#define BUFFER_SIZE 200

typedef struct {
//  size_t const buffer_size = 200;
  char buf[BUFFER_SIZE];
  size_t len { BUFFER_SIZE };
} StreamBuffer;

inline void clear_stream(StreamBuffer &stream_buf) {
  memset(stream_buf.buf, 0, stream_buf.len);
  stream_buf.len = 0;
}

class UART {
 public:
  UART(UART_HandleTypeDef &handle)
      :
      huart(handle) {
  }

  void start();

  /* Synchronous call to check for new char in dma buffer  */
  void spin_circular();
//  void spin_circular2();

  /* Print Methods */
  ssize_t print(const char *buf, size_t len);

  size_t print(const char *buf);

  ssize_t print(const std::string &s);

  size_t EOL();

  size_t write(uint8_t &c);

  size_t write(const uint8_t *buf, size_t len);

  size_t write(const char *buf, size_t len);

  /* Define what to do when a new line is received */
  virtual void process_line(const uint8_t *buf, size_t len) = 0;

  inline UART_HandleTypeDef get_uart_handle() {
    return huart;
  }

  void clear_rx_dma_buffer();

 protected:

  ssize_t tx_dma_buffer(const uint8_t *buf, size_t len);

  ssize_t rx_dma_buffer(const uint8_t *buf, size_t len);

 private:
  void process(const void *data, size_t len);
  static const uint_least16_t UART_RX_BUFFER_SIZE = 255;
  static const uint_least16_t UART_TX_BUFFER_SIZE = 255;

  uint8_t dma_rx_buffer[UART_RX_BUFFER_SIZE] { 0 };

  uint8_t dma_tx_buffer[UART_TX_BUFFER_SIZE] { 0 };

  uint32_t dma_receive_prev_idx { 0 };

  UART_HandleTypeDef &huart;

};

#endif /* DEVICE_UART_HPP_ */
