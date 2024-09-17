import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

# Create synthetic overlay of latency distributions for the Poster

# Change the default font size to 24
plt.rcParams['font.size'] = 20

# Generate two sets of latency data with the specified means and standard deviations
data1 = np.random.normal(loc=20.5, scale=5, size=1000)
data2 = np.random.normal(loc=22, scale=5, size=1000)

# Clip data to range 0-40 us
data1 = np.clip(data1, 0, 40)
data2 = np.clip(data2, 0, 40)

# Define histogram bins from 0 to 40 with interval of 5
bins = np.arange(0, 45, 5)

# Create a plot to overlay both distributions
fig, ax = plt.subplots(figsize=(10, 7))

# Set the figure background color
fig.patch.set_facecolor('#5585BF')

# Set the background color of the plot area
ax.set_facecolor('#5585BF')

# Brighter colors for better visibility on the blue background
bright_color1 = '#FFB3E5'  # Brighter shade of the original #E491DE
bright_color2 = '#FFD8A8'  # Brighter shade of the original #EEBB8C

# Histogram and density curve for the first dataset
sns.histplot(data1, kde=True, bins=bins, color=bright_color1, edgecolor=bright_color1, stat='count', label='On-board measurements', alpha=0.5, ax=ax)

# Histogram and density curve for the second dataset
sns.histplot(data2, kde=True, bins=bins, color=bright_color2, edgecolor=bright_color2, stat='count', label='Estimation of the model', alpha=0.5, ax=ax)

# Add titles and labels with white color
plt.title('Overlay of Latency Distributions', color='white')
plt.xlabel('Latency (us)', color='white')
plt.ylabel('Number of Samples', color='white')
plt.xlim(0, 40)

# Customize tick parameters for white color
plt.tick_params(colors='white')
plt.xticks(color='white')
plt.yticks(color='white')

# Add a legend with white text and white background
legend = plt.legend(facecolor='white', edgecolor='white', fontsize=16)
plt.setp(legend.get_texts(), color='black')

# Customize the spines for white color and make top and right spines invisible
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['bottom'].set_color('white')
ax.spines['left'].set_color('white')

# Display the plot
plt.show()
