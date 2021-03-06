/**
 * @file sam3x_eth.h
 * @brief SAM3X Ethernet MAC controller
 *
 * @section License
 *
 * Copyright (C) 2010-2013 Oryx Embedded. All rights reserved.
 *
 * This file is part of CycloneTCP Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded (www.oryx-embedded.com)
 * @version 1.3.8
 **/

#ifndef _SAM3X_ETH_H
#define _SAM3X_ETH_H

//TX buffers
#define SAM3X_TX_BUFFER_COUNT 3
#define SAM3X_TX_BUFFER_SIZE 1536
//RX buffers
#define SAM3X_RX_BUFFER_COUNT 72
#define SAM3X_RX_BUFFER_SIZE 128

//RMII signals
#define EMAC_RMII_MASK (PIO_PB9A_EMDIO | PIO_PB8A_EMDC | \
   PIO_PB7A_ERXER | PIO_PB6A_ERX1 | PIO_PB5A_ERX0 | PIO_PB4A_ERXDV | \
   PIO_PB3A_ETX1 | PIO_PB2A_ETX0 | PIO_PB1A_ETXEN | PIO_PB0A_ETXCK)

//TX buffer descriptor flags
#define EMAC_TX_USED           0x80000000
#define EMAC_TX_WRAP           0x40000000
#define EMAC_TX_ERROR          0x20000000
#define EMAC_TX_UNDERRUN       0x10000000
#define EMAC_TX_EXHAUSTED      0x08000000
#define EMAC_TX_NO_CRC         0x00010000
#define EMAC_TX_LAST           0x00008000
#define EMAC_TX_LENGTH         0x000007FF

//RX buffer descriptor flags
#define EMAC_RX_ADDRESS        0xFFFFFFFC
#define EMAC_RX_WRAP           0x00000002
#define EMAC_RX_OWNERSHIP      0x00000001
#define EMAC_RX_BROADCAST      0x80000000
#define EMAC_RX_MULTICAST_HASH 0x40000000
#define EMAC_RX_UNICAST_HASH   0x20000000
#define EMAC_RX_EXT_ADDR       0x10000000
#define EMAC_RX_SAR1           0x04000000
#define EMAC_RX_SAR2           0x02000000
#define EMAC_RX_SAR3           0x01000000
#define EMAC_RX_SAR4           0x00800000
#define EMAC_RX_TYPE_ID        0x00400000
#define EMAC_RX_VLAN_TAG       0x00200000
#define EMAC_RX_PRIORITY_TAG   0x00100000
#define EMAC_RX_VLAN_PRIORITY  0x000E0000
#define EMAC_RX_CFI            0x00010000
#define EMAC_RX_EOF            0x00008000
#define EMAC_RX_SOF            0x00004000
#define EMAC_RX_OFFSET         0x00003000
#define EMAC_RX_LENGTH         0x00000FFF


/**
 * @brief Transmit buffer descriptor
 **/

typedef struct
{
   uint32_t address;
   uint32_t status;
} Sam3xTxBufferDesc;


/**
 * @brief Receive buffer descriptor
 **/

typedef struct
{
   uint32_t address;
   uint32_t status;
} Sam3xRxBufferDesc;


//SAM3X Ethernet MAC driver
extern const NicDriver sam3xEthDriver;

//SAM3X Ethernet MAC related functions
error_t sam3xEthInit(NetInterface *interface);
void sam3xEthInitBufferDesc(NetInterface *interface);

void sam3xEthTick(NetInterface *interface);

void sam3xEthEnableIrq(NetInterface *interface);
void sam3xEthDisableIrq(NetInterface *interface);
void sam3xEthRxEventHandler(NetInterface *interface);

error_t sam3xEthSetMacFilter(NetInterface *interface);

error_t sam3xEthSendPacket(NetInterface *interface,
   const ChunkedBuffer *buffer, size_t offset);

uint_t sam3xEthReceivePacket(NetInterface *interface,
   uint8_t *buffer, uint_t size);

void sam3xEthWritePhyReg(uint8_t phyAddr, uint8_t regAddr, uint16_t data);
uint16_t sam3xEthReadPhyReg(uint8_t phyAddr, uint8_t regAddr);

#endif
