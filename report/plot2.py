import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# Create the plot with log scale for both axes and reverse the x-axis
data_path = './updated_new_results.csv'
data = pd.read_csv(data_path)
data.head()
sizes = data['size'].unique()
colors = plt.cm.viridis(np.linspace(0, 1, len(sizes)))
ps = data['p'].unique()
plt.figure(figsize=(10, 8))

# Plotting each size's error vs. p
for size, color in zip(sizes, colors):
    subset = data[data['size'] == size]
    plt.plot(subset['p'], subset['error'], label=f'Size {size}', color=color)


# Plotting Hamming
plt.plot(data['p'], data['Hamming'], label='Hamming', linestyle='-.', color='red')

# Setting log scale and reversing the x-axis
plt.xscale('log')
plt.yscale('log')
plt.gca().invert_xaxis()

# Adding labels, legend, and title
plt.xlabel('p)')
plt.ylabel('Error')
plt.title('Log-Log Scale of Error vs. p for different sizes and Hamming')
plt.legend()

# Show the plot
plt.grid(True)
plt.show()

