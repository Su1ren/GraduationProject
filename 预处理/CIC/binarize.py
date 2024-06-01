import pandas as pd
import socket
import struct

def write_ips_and_unix_timestamp_to_binary(csv_file, binary_file):
    # 读取 CSV 文件并提取 IP 地址列
    df = pd.read_csv(csv_file)
    ip_column = df['Source IP']
    timestamp_column = df['Timestamp']
    # 将 IP 地址转换为二进制并写入二进制文件
    with open(binary_file, 'wb') as binfile:
        for ip,t in zip(ip_column,timestamp_column):
            ip_bytes = socket.inet_aton(ip)
            binfile.write(ip_bytes)
            binfile.write(struct.pack('<L',t))

# 示例用法
csv_file = 'timestamp.csv'
binary_file = 'ip_addresses_u32.dat'
write_ips_and_unix_timestamp_to_binary(csv_file, binary_file)