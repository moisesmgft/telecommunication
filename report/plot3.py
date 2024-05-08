import pandas as pd

# Load the CSV files into DataFrames
rate12_df = pd.read_csv(f"./data/rate37.csv")
hamming_df = pd.read_csv(f"./data/hamming.csv")

# Display the first few rows of each DataFrame to understand their structure
(rate12_df.head(), hamming_df.head())

import matplotlib.pyplot as plt
import numpy as np

# Set up the plot
plt.figure(figsize=(10, 7))
ax = plt.gca()
ax.set_xscale('log')
ax.set_yscale('log')
ax.invert_xaxis()

# Plotting each size's error from rate12.csv
sizes = rate12_df['size'].unique()
for size in sizes:
    subset = rate12_df[rate12_df['size'] == size]
    plt.plot(subset['p'], subset['error'], label=f'Size {size}')

# Plotting y = x line
x_values = np.linspace(min(rate12_df['p']), max(rate12_df['p']), 400)

# Plotting Hamming error from hamming.csv
plt.plot(hamming_df['p'], hamming_df['Hamming'], label='Hamming', color='black')

# Adding legends and labels
plt.legend(title='Error Lines')
plt.xlabel('Probability p (reversed log scale)')
plt.ylabel('Error (log scale)')
plt.title('Error vs. Probability with Different Encoding Sizes and Hamming Error')
plt.grid(True)

# Show plot
plt.show()
