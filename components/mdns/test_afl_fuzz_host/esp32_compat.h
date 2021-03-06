// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _ESP32_COMPAT_H_
#define _ESP32_COMPAT_H_

#ifdef MDNS_TEST_MODE

// Not to include
#define ESP_MDNS_NETWORKING_H_
#define _TCPIP_ADAPTER_H_


#ifdef USE_BSD_STRING
#include <bsd/string.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define ESP_FAIL                    -1

#define ESP_ERR_NO_MEM              0x101
#define ESP_ERR_INVALID_ARG         0x102
#define ESP_ERR_INVALID_STATE       0x103
#define ESP_ERR_INVALID_SIZE        0x104
#define ESP_ERR_NOT_FOUND           0x105
#define ESP_ERR_NOT_SUPPORTED       0x106
#define ESP_ERR_TIMEOUT             0x107
#define ESP_ERR_INVALID_RESPONSE    0x108
#define ESP_ERR_INVALID_CRC         0x109

#define pdTRUE                      true
#define pdFALSE                     false
#define pdPASS			( pdTRUE )
#define pdFAIL			( pdFALSE )

#define portMAX_DELAY               0xFFFFFFFF
#define portTICK_PERIOD_MS          1
#define ESP_LOGW(a,b)
#define ESP_LOGD(a,b)
#define ESP_LOGE(a,b,c)
#define ESP_LOGV(a,b,c,d)

#define LWIP_HDR_PBUF_H
#define __ESP_SYSTEM_H__
#define INC_TASK_H

#define pdMS_TO_TICKS(a) a
#define portTICK_RATE_MS 10
#define xSemaphoreTake(s,d)
#define xTaskDelete(a)
#define vTaskDelete(a)             free(a)
#define xSemaphoreGive(s)
#define xQueueCreateMutex(s)
#define _mdns_pcb_init(a,b)         true
#define _mdns_pcb_deinit(a,b)       true
#define xSemaphoreCreateMutex()     malloc(1)
#define xSemaphoreCreateBinary()    malloc(1)
#define vSemaphoreDelete(s)         free(s)
#define queueQUEUE_TYPE_MUTEX       ( ( uint8_t ) 1U
#define xTaskCreatePinnedToCore(a,b,c,d,e,f,g)     *(f) = malloc(1)
#define vTaskDelay(m)               usleep((m)*0)
#define pbuf_free(p)                free(p)
#define esp_random()                (rand()%UINT32_MAX)
#define tcpip_adapter_get_ip_info(i,d)          true
#define tcpip_adapter_dhcpc_get_status(a, b)    TCPIP_ADAPTER_DHCP_STARTED
#define tcpip_adapter_get_ip6_linklocal(i,d)    (ESP_OK)
#define tcpip_adapter_get_hostname(i, n)        *(n) = "esp32-0123456789AB"

#define IP4_ADDR(ipaddr, a,b,c,d) \
        (ipaddr)->addr = ((uint32_t)((d) & 0xff) << 24) | \
                         ((uint32_t)((c) & 0xff) << 16) | \
                         ((uint32_t)((b) & 0xff) << 8)  | \
                          (uint32_t)((a) & 0xff)
#define ip_2_ip6(ipaddr)   (&((ipaddr)->u_addr.ip6))
#define ip_2_ip4(ipaddr)   (&((ipaddr)->u_addr.ip4))

#define IP_SET_TYPE_VAL(ipaddr, iptype) do { (ipaddr).type = (iptype); }while(0)
#define IP_ADDR4(ipaddr,a,b,c,d)      do { IP4_ADDR(ip_2_ip4(ipaddr),a,b,c,d); \
                                           IP_SET_TYPE_VAL(*(ipaddr), IPADDR_TYPE_V4); } while(0)
#define IP_ADDR6(ipaddr,i0,i1,i2,i3)  do { IP6_ADDR(ip_2_ip6(ipaddr),i0,i1,i2,i3); \
                                           IP_SET_TYPE_VAL(*(ipaddr), IPADDR_TYPE_V6); } while(0)

#define IPADDR6_INIT(a, b, c, d)      { { { { a, b, c, d } } }, IPADDR_TYPE_V6 }

typedef int32_t esp_err_t;

typedef void * xSemaphoreHandle;
typedef void * SemaphoreHandle_t;
typedef void * xQueueHandle;
typedef void * QueueHandle_t;
typedef void * TaskHandle_t;
typedef uint32_t TickType_t;
typedef uint32_t portTickType;


extern const char * WIFI_EVENT;
extern const char * IP_EVENT;
extern const char * ETH_EVENT;

/* status of DHCP client or DHCP server */
typedef enum {
    TCPIP_ADAPTER_DHCP_INIT = 0,    /**< DHCP client/server in initial state */
    TCPIP_ADAPTER_DHCP_STARTED,     /**< DHCP client/server already been started */
    TCPIP_ADAPTER_DHCP_STOPPED,     /**< DHCP client/server already been stopped */
    TCPIP_ADAPTER_DHCP_STATUS_MAX
} tcpip_adapter_dhcp_status_t;

struct udp_pcb {
    uint8_t dummy;
};

struct ip4_addr {
  uint32_t addr;
};
typedef struct ip4_addr ip4_addr_t;

struct ip6_addr {
  uint32_t addr[4];
};
typedef struct ip6_addr ip6_addr_t;

typedef struct {
    ip4_addr_t ip;
    ip4_addr_t netmask;
    ip4_addr_t gw;
} tcpip_adapter_ip_info_t;

typedef enum {
    TCPIP_ADAPTER_IF_STA = 0,     /**< ESP32 station interface */
    TCPIP_ADAPTER_IF_AP,          /**< ESP32 soft-AP interface */
    TCPIP_ADAPTER_IF_ETH,         /**< ESP32 ethernet interface */
    TCPIP_ADAPTER_IF_MAX
} tcpip_adapter_if_t;

typedef struct {
    ip6_addr_t ip;
} tcpip_adapter_ip6_info_t;

typedef void* system_event_t;

struct pbuf {
  struct pbuf *next;
  void *payload;
  uint16_t tot_len;
  uint16_t  len;
  uint8_t  /*pbuf_type*/ type;
  uint8_t  flags;
  uint16_t  ref;
};

#define IP_GET_TYPE(ipaddr)           ((ipaddr)->type)
#define IP_IS_V6_VAL(ipaddr)          (IP_GET_TYPE(&ipaddr) == IPADDR_TYPE_V6)
#define ip4_addr_copy(dest, src) ((dest).addr = (src).addr)
#define ip6_addr_copy(dest, src) do{(dest).addr[0] = (src).addr[0]; \
                                    (dest).addr[1] = (src).addr[1]; \
                                    (dest).addr[2] = (src).addr[2]; \
                                    (dest).addr[3] = (src).addr[3];}while(0)

#define ip_addr_copy(dest, src)      do{ IP_SET_TYPE_VAL(dest, IP_GET_TYPE(&src)); if(IP_IS_V6_VAL(src)){ \
  ip6_addr_copy(*ip_2_ip6(&(dest)), *ip_2_ip6(&(src))); }else{ \
  ip4_addr_copy(*ip_2_ip4(&(dest)), *ip_2_ip4(&(src))); }}while(0)

#include "esp32_mock.h"

uint32_t xTaskGetTickCount(void);


#endif //MDNS_TEST_MODE

#endif //_ESP32_COMPAT_H_
