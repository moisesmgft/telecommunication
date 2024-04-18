import pandas as pd
import matplotlib.pyplot as plt

# Load the data from the CSV file
df = pd.read_csv('results.csv')

# Extract data for plotting
p_subset = df['p'].values
no_encoding_subset = df['No encoding'].values
mr_subset = df['MR'].values
hamming_subset = df['Hamming'].values

# Create the plot
fig, ax = plt.subplots(figsize=(10, 6))

# Plotting the data
ax.plot(p_subset, no_encoding_subset, linestyle='-', color='black', label='No Encoding')
ax.plot(p_subset, mr_subset, linestyle='-', color='blue', label='MR')
ax.plot(p_subset, hamming_subset, linestyle='-', color='red', label='Hamming')

# Setting log scale for x and y
ax.set_xscale('log')
ax.set_yscale('log')

# Reversing the x-axis
ax.set_xlim(ax.get_xlim()[::-1])

# Adding labels and title
ax.set_xlabel('Probability (p)')
ax.set_ylabel('Values')
ax.set_title('Probabilidade de erro')

# Adding a legend
ax.legend()

# Show plot
plt.show()
