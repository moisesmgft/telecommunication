import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file
file_path = 'data/lab3_results.csv'  # Update with the actual path
data = pd.read_csv(file_path)

# Creating the plot
plt.figure(figsize=(10, 6))
plt.plot(data["SNR"], data["No decoding"], label="No decoding", marker='o')
plt.plot(data["SNR"], data["Demodulated"], label="BPSK", marker='x')

# Setting the x-axis to linear scale
plt.xscale('linear')

# Setting the y-axis to log scale
plt.yscale('log')

# Adding labels and title
plt.xlabel("SNR")
plt.ylabel("Error Rate")
plt.title("Error Rate vs SNR")
plt.legend()
plt.grid(True)

# Displaying the plot
plt.show()
