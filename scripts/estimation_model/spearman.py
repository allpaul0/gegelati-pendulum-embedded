class Spearman:
    def rank_with_percentage_tolerance(self, data, percentage):
        """
        Assigns ranks to each element in the data list. If two values differ by less
        than the specified percentage of their value, they are given the same rank.
        """
        ranks = [0] * len(data)
        # Sort data by value and keep track of original indices
        sorted_data = sorted((value, index) for index, value in enumerate(data))
        
        i = 0
        while i < len(sorted_data):
            value, original_index = sorted_data[i]
            # Calculate tolerance as a percentage of the value
            tolerance = (percentage / 100) * value
            j = i
            
            # Find all items within the calculated tolerance
            while j < len(sorted_data) and abs(sorted_data[j][0] - value) <= tolerance:
                j += 1
            
            # Assign the average rank for this group of close values
            average_rank = (i + j + 1) / 2
            for k in range(i, j):
                ranks[sorted_data[k][1]] = average_rank
            
            # Move to the next group
            i = j
        
        return ranks

    def spearman_rank_correlation_with_percentage_tolerance(self, observed, predicted, tolerance_percentage):
        """
        Computes Spearman's rank correlation coefficient between two lists,
        with an option to handle minor variations in observed values using
        tolerance defined as a percentage of the observed values.
        """
        n = len(observed)
        if n != len(predicted):
            raise ValueError("Observed and predicted lists must have the same length.")
        
        # Rank both lists with percentage tolerance applied to the observed values
        observed_ranks = self.rank_with_percentage_tolerance(observed, tolerance_percentage)
        # print(observed_ranks)
        predicted_ranks = self.rank_with_percentage_tolerance(predicted, 0)  # No need for tolerance in predicted values
        # print(predicted_ranks)
        
        # Calculate the sum of squared rank differences
        d_squared_sum = sum((observed_ranks[i] - predicted_ranks[i]) ** 2 for i in range(n))
        
        # Apply Spearman's formula
        spearman_rho = 1 - (6 * d_squared_sum) / (n * (n**2 - 1))
        
        return spearman_rho

    def rank(self, data, tolerance=0.0):
        """
        Assigns ranks to each element in the data list. If two values differ by less than
        the specified tolerance, they are given the same rank.
        """
        # Sort data by value and keep track of original indices
        sorted_data = sorted((value, index) for index, value in enumerate(data))
        ranks = [0] * len(data)
        
        i = 0
        while i < len(sorted_data):
            # Start of the group of close values
            value, original_index = sorted_data[i]
            j = i
            
            # Find all items within tolerance
            while j < len(sorted_data) and abs(sorted_data[j][0] - value) <= tolerance:
                j += 1
            
            # Assign the average rank for this group of close values
            average_rank = (i + j + 1) / 2
            for k in range(i, j):
                ranks[sorted_data[k][1]] = average_rank
            
            # Move to the next group
            i = j
        
        return ranks

    def spearman_rank_correlation(self, observed, predicted, tolerance=0.0):
        """
        Computes Spearman's rank correlation coefficient between two lists,
        with an option to handle minor variations in observed values using a tolerance.
        """
        n = len(observed)
        if n != len(predicted):
            raise ValueError("Observed and predicted lists must have the same length.")
        
        # Rank both lists with tolerance applied to the observed values
        observed_ranks = self.rank(observed, tolerance)
        predicted_ranks = self.rank(predicted)
        
        # Calculate the sum of squared rank differences
        d_squared_sum = sum((observed_ranks[i] - predicted_ranks[i]) ** 2 for i in range(n))
        
        # Apply Spearman's formula
        spearman_rho = 1 - (6 * d_squared_sum) / (n * (n**2 - 1))
        
        return spearman_rho

# # Example usage:
# observed = [1.10, 2.01, 2.11, 3.20, 4.01]
# predicted = [1, 2, 2, 3, 4]

# sp = Spearman()

# # Specify the tolerance percentage (e.g., 10% of each observed value)
# spearman_rho = sp.spearman_rank_correlation_with_percentage_tolerance(observed, predicted, tolerance_percentage=4.98) # 4.97 is 1.0
# print("Spearman's rank correlation with percentage tolerance:", spearman_rho)