import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Given y values (now treated as the independent variable)
y = np.array([0.5717, 3.216, 4.7406, 6.2652, 7.7898]).reshape(-1, 1)

# Given x values (now treated as the dependent variable)
x = np.array([1, 2, 3, 4, 5])

# Create and fit the linear regression model
model = LinearRegression()
model.fit(y, x)

# Predicted x values based on the model (for plotting the regression line)
x_pred = model.predict(y)

# Plotting the data points and the regression line
plt.scatter(y, x, color='blue', label='Data Points')  # actual data points
plt.plot(y, x_pred, color='red', label='Regression Line')  # regression line

# Labels and title
plt.xlabel('number of programs')
plt.ylabel('time in us')
plt.title('Linear Regression Plot (Inverted x and y)')

# Display legend
plt.legend()

# Show the plot
plt.show()
