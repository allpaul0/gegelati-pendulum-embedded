import itertools
from scipy.stats import spearmanr, kendalltau

def rank(data):
    """
    Assigns ranks to each element in the data list. In the case of ties,
    it assigns the average rank for tied values.
    """
    # Sort the data and assign ranks, nb ranks = nb data elements
    sorted_data = sorted((value, index) for index, value in enumerate(data))
    print(sorted_data)
    ranks = [0] * len(data)
    
    # Assign ranks with handling for ties
    i = 0
    while i < len(sorted_data):
        value, original_index = sorted_data[i]
        print(value, original_index)
        j = i
        # Find all items with the same value (ties)
        while j < len(sorted_data) and sorted_data[j][0] == value:
            j += 1
        # Calculate the average rank for ties
        average_rank = (i + j + 1) / 2
        print(average_rank)
        for k in range(i, j):
            ranks[sorted_data[k][1]] = average_rank
        i = j
    
    return ranks

def spearman_rank_correlation(observed, predicted):
    """
    Computes Spearman's rank correlation coefficient between two lists.
    """
    n = len(observed)
    if n != len(predicted):
        raise ValueError("Observed and predicted lists must have the same length.")
    
    # Step 1: Rank both lists
    observed_ranks = rank(observed)
    print(observed_ranks)
    predicted_ranks = rank(predicted)
    print(predicted_ranks)
    
    # Step 2: Calculate the sum of squared rank differences
    # d_squared_sum = sum((observed_ranks[i] - predicted_ranks[i]) ** 2 for i in range(n))
    d_squared_sum = 0
    for i in range(n):
        print(observed_ranks[i], predicted_ranks[i])
        d_squared_sum += ((observed_ranks[i] - predicted_ranks[i]) ** 2)
    
    # Step 3: Apply Spearman's formula
    spearman_rho = 1 - (6 * d_squared_sum) / (n * (n**2 - 1))
    
    return spearman_rho

def compute_fidelity(observed, predicted):
    # Number of consistent pairs
    consistent_pairs = 0
    # Total number of pairs
    total_pairs = 0
    
    # Generate all pairs (i, j) with i < j
    for i, j in itertools.combinations(range(len(observed)), 2):

        print(i, j)

        # Increase total pairs counter
        total_pairs += 1
        
        # Check if the ordering is consistent
        if (observed[i] < observed[j] and predicted[i] < predicted[j]) or \
           (observed[i] == observed[j] and predicted[i] == predicted[j]) or \
           (observed[i] > observed[j] and predicted[i] > predicted[j]):
            print("consistent pair found")
            consistent_pairs += 1
        else:
            print(observed[i], observed[j], predicted[i], predicted[j])
            
    # Calculate fidelity as the ratio of consistent pairs to total pairs
    fidelity = consistent_pairs / total_pairs if total_pairs > 0 else 0
    return fidelity


observed = [1.1, 2.0, 2.1, 3.2, 4.0, 5.0, 5.1]
predicted = [1, 2, 2, 3, 4, 5, 5]  # Perfectly ordered predicted values

# fidelity_score = compute_fidelity(observed, predicted)
# print("Fidelity score:", fidelity_score)


# # Calculate Spearman's rank correlation
# spearman_corr, _ = spearmanr(observed, predicted)
# print("Spearman's rank correlation:", spearman_corr)

# # Calculate Kendall's Tau
# kendall_corr, _ = kendalltau(observed, predicted)
# print("Kendall's Tau:", kendall_corr)

# spearman_rho = spearman_rank_correlation(observed, predicted)
# print("Spearman's rank correlation:", spearman_rho)

observed2 = [1.1, 4.0, 2.1, 3.2, 2.0, 5.0, 5.1]
predicted2 = [1, 4, 2, 3, 2, 5, 5]

spearman_rho2 = spearman_rank_correlation(observed2, predicted2)
print("Spearman's rank correlation:", spearman_rho2)
