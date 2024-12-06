import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

# # Provided y and x values
# y_values_double1 = np.array([0.5717, 3.216, 4.7406, 6.2652, 7.7898]).reshape(-1, 1)
# y_values_double2 = np.array([0.5718, 3.2756, 4.8597, 6.4795, 8.0043]).reshape(-1, 1)
# y_values_int2 = np.array([0.5241, 1.3102, 1.7033, 2.0964, 2.418]).reshape(-1, 1)
# x = np.array([1, 2, 3, 4, 5]).reshape(-1, 1)

y_values_double1 = np.array([3.216, 4.7406, 6.2652, 7.7898]).reshape(-1, 1)
y_values_double2 = np.array([3.2756, 4.8597, 6.4795, 8.0043]).reshape(-1, 1)
y_values_int2 = np.array([1.3102, 1.7033, 2.0964, 2.418]).reshape(-1, 1)
x = np.array([2, 3, 4, 5]).reshape(-1, 1)


# Initialize linear regression models
lin_reg_double1 = LinearRegression()
lin_reg_double2 = LinearRegression()
lin_reg_int2 = LinearRegression()

# Fit the models
lin_reg_double1.fit(x, y_values_double1)
lin_reg_double2.fit(x, y_values_double2)
lin_reg_int2.fit(x, y_values_int2)

# Predict values using the fitted models
y_pred_double1 = lin_reg_double1.predict(x)
y_pred_double2 = lin_reg_double2.predict(x)
y_pred_int2 = lin_reg_int2.predict(x)

print(y_pred_double2)

# Plotting
plt.figure(figsize=(10, 6))
plt.scatter(x, y_values_double1, color="blue", label="Double 1 (data)")
plt.plot(x, y_pred_double1, color="blue", linestyle="--", label="Double 1 (fit)")

plt.scatter(x, y_values_double2, color="green", label="Double 2 (data)")
plt.plot(x, y_pred_double2, color="green", linestyle="--", label="Double 2 (fit)")

plt.scatter(x, y_values_int2, color="red", label="Int 2 (data)")
plt.plot(x, y_pred_int2, color="red", linestyle="--", label="Int 2 (fit)")

# Adding labels and legend
plt.xlabel("Number of Programs per Team")
plt.ylabel("Time in µs")
plt.title("Linear Regression of Time vs Number of Programs per Team")
plt.legend()
plt.grid(True)
plt.show()

