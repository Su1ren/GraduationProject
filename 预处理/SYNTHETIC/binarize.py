import pandas as pd
import socket
import struct

def ip_to_bytes(src,dst):
    return (socket.inet_pton(socket.AF_INET,src),socket.inet_pton(socket.AF_INET,dst))

def write_ips_and_unix_timestamp_to_binary(csv_file, binary_file):
    # 读取 CSV 文件并提取 IP 地址列
    df = pd.read_csv(csv_file)
    src_column = df['src']
    dst_column = df['dst']
    timestamp_column = df['id']
    sum = 0
    # 将 IP 地址转换为二进制并写入二进制文件
    with open(binary_file, 'wb') as binfile:
        for src,dst,t in zip(src_column,dst_column,timestamp_column):
            src_byte,dst_byte = socket.inet_aton(src),socket.inet_aton(dst)
            if (src,dst) in ldos:
                sum += 1
                for _ in range(20):
                    binfile.write(src_byte)
                    binfile.write(dst_byte)
                    binfile.write(struct.pack('<L',t))
            else:
                binfile.write(src_byte)
                binfile.write(dst_byte)
                binfile.write(struct.pack('<L',t))
    print(sum)

# 示例用法
csv_file = 'synthetic1.csv'
binary_file = 'SYN20.dat'
'''
ldos = {ip_to_bytes('56.3.4.29','205.180.84.107'),ip_to_bytes('41.144.6.215','237.42.73.102'),ip_to_bytes('97.133.87.114','231.225.123.73'),
        ip_to_bytes('122.24.159.76','205.236.95.24'),ip_to_bytes('148.83.149.19','193.65.85.90'),ip_to_bytes('13.217.225.167','244.31.10.8'),
        ip_to_bytes('206.48.207.188','215.13.72.176'),ip_to_bytes('69.112.85.189','139.61.80.170'),ip_to_bytes('218.192.201.32','199.221.119.53'),
        ip_to_bytes('195.251.50.59','73.165.34.23')}
'''
ldos = {('56.3.4.29','205.180.84.107'),('41.144.6.215','237.42.73.102'),('97.133.87.114','231.225.123.73'),
        ('122.24.159.76','205.236.95.24'),('148.83.149.19','193.65.85.90'),('13.217.225.167','244.31.10.8'),
        ('206.48.207.188','215.13.72.176'),('69.112.85.189','139.61.80.170'),('218.192.201.32','199.221.119.53'),
        ('195.251.50.59','73.165.34.23')}

write_ips_and_unix_timestamp_to_binary(csv_file, binary_file)
#print(sum)