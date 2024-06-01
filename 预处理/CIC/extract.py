import pandas as pd

def extract_columns_from_csv(input_file, output_file, columns_to_extract):
    try:
        # 使用pandas读取CSV文件
        df = pd.read_csv(input_file,usecols=columns_to_extract)
         
        # 从DataFrame中选择指定的列
        # selected_columns_df = df[columns_to_extract]
         
        # 将选择的列保存到XLSX文件
        df.to_csv(output_file, index=False)
         
        print(f"成功从 {input_file} 中提取并保存了以下列到 {output_file}: {', '.join(columns_to_extract)}")
     
    except Exception as e:
        print("出现错误:", e)
 
# 输入CSV文件路径
input_csv_file = "ldos.csv"
 
# 输出XLSX文件路径
output_xlsx_file = "output.csv"
 
# 需要提取的列名
columns_to_extract = [1,6,84]
 
# 调用函数进行提取和保存
extract_columns_from_csv(input_csv_file, output_xlsx_file, columns_to_extract)