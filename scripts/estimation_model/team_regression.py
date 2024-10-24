import numpy as np
from sklearn.linear_model import LinearRegression

# Given x values
x = np.array([0.5717, 3.216, 4.7406, 6.2652, 7.7898]).reshape(-1, 1)

# y values 
y = np.array([1, 2, 3, 4, 5])

# Create and fit the linear regression model
model = LinearRegression()
model.fit(x, y)

# Print the regression coefficient (slope)
print(f"Regression Coefficient (Slope): {model.coef_[0]}")
