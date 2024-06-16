import asyncio
from bleak import BleakClient
from pylsl import StreamInfo, StreamOutlet
import struct

# BLE address of your ESP32 device
address = "DC:54:75:61:72:1E" # Replace with your ESP32 BLE Address You Can Check Your ESP32 address using nRF Connect App
SERVICE_UUID = "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"

# LSL stream information
info = StreamInfo('ESP32_BLE_Stream', 'EEG', 1, 100, 'float32', 'myuid34234')
outlet = StreamOutlet(info)

def notification_handler(sender, data):
    """Notification handler which converts the received data to float and stores it."""
    unpacked_data = struct.unpack('<f', data)
    float_data = unpacked_data[0]
    print(f"Received data: {float_data}")
    outlet.push_sample([float_data])

async def ble_task():
    async with BleakClient(address) as client:
        x = await client.is_connected()
        print("Connected: ", x)

        await client.start_notify(CHARACTERISTIC_UUID, notification_handler)
        print("Notification started. Receiving data...")

        await asyncio.Future()

async def main():
    await ble_task()

asyncio.run(main())
