import pandas as pd
from datetime import datetime

def convert_datetime_to_unix(datetime_str, datetime_format):
    # 将日期时间字符串解析为 datetime 对象
    dt = datetime.strptime(datetime_str, datetime_format)

    # 将 datetime 对象转换为 Unix 时间戳
    unix_timestamp = int(dt.timestamp())

    return unix_timestamp

def convert_csv_datetime_to_unix(csv_file, output_file,datetime_column, datetime_format):
    # 使用 pandas 读取 CSV 文件
    df = pd.read_csv(csv_file)

    # 将指定列的日期时间数据转换为 Unix 时间戳
    df[datetime_column] = df[datetime_column].apply(lambda x: convert_datetime_to_unix(x, datetime_format))

    # 将修改后的数据保存回 CSV 文件
    df.to_csv(output_file, index=False)

# 示例用法
csv_file = 'output.csv'
out_file = 'timestamp.csv'
datetime_column = ' Timestamp'
datetime_format = '%m/%d/%Y %H:%M'
convert_csv_datetime_to_unix(csv_file,out_file, datetime_column, datetime_format)