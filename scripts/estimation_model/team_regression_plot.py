import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# Given x values
x = np.array([0.5717, 3.216, 4.7406, 6.2652, 7.7898]).reshape(-1, 1)

# Arbitrary y values
y = np.array([1, 2, 3, 4 , 5])

# Create and fit the linear regression model
model = LinearRegression()
model.fit(x, y)

# Predicted y values based on the model (for plotting the regression line)
y_pred = model.predict(x)

# Plotting the data points and the regression line
plt.scatter(x, y, color='blue', label='Data Points')  # actual data points
plt.plot(x, y_pred, color='red', label='Regression Line')  # regression line

# Labels and title
plt.xlabel('time in us')
plt.ylabel('number of programs')
plt.title('Linear Regression Plot')

# Display legend
plt.legend()

# Show the plot
plt.show()
