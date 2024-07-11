import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
file_path = 'data/lab4_results.csv'
data = pd.read_csv(file_path)

# Plotting SNR by the error with only the error axis in log scale
output_path_corrected = 'data/lab4_plot.png'
plt.figure(figsize=(10, 6))
plt.semilogy(data['SNR'], data['Uncoded'], label='Uncoded', marker='o')
plt.semilogy(data['SNR'], data['Hamming'], label='Hamming', marker='o')
plt.semilogy(data['SNR'], data['Bit-Flip'], label='Bit-Flip', marker='o')
plt.semilogy(data['SNR'], data['LLR'], label='LLR', marker='o')
plt.semilogy(data['SNR'], data['MR-LDPC'], label='MR-LDPC', marker='o')

plt.xlabel('SNR')
plt.ylabel('Error Rate')
plt.title('SNR vs Error Rate')
plt.legend()
plt.grid(True, which="both", ls="--")
plt.savefig(output_path_corrected)
plt.show()

