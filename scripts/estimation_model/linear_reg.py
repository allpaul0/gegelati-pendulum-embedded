import numpy as np
from sklearn.linear_model import LinearRegression

def perform_linear_regression(x_values, y_values, new_x):
    # Reshape x values to be a 2D array (required by sklearn)
    x = np.array(x_values).reshape(-1, 1)
    y = np.array(y_values)
    
    # Create and fit the linear regression model
    model = LinearRegression()
    model.fit(x, y)
    
    # Calculate the regression coefficient (slope)
    slope = model.coef_[0]
    intercept = model.intercept_
    
    # Predict the corresponding y value for new_x
    predicted_y = model.predict(np.array([[new_x]]))[0]
    
    print(f"Regression Coefficient (Slope): {slope}")
    print(f"Intercept: {intercept}")
    print(f"Predicted y for x = {new_x}: {predicted_y}")
    
    return predicted_y

# Example usage:
x_values = [1, 2, 3, 4, 5]
y_values = [0.5717, 3.216, 4.7406, 6.2652, 7.7898]
new_x = 5.0
predicted_y = perform_linear_regression(x_values, y_values, new_x)
perform_linear_regression(x_values, y_values, 3.5)
