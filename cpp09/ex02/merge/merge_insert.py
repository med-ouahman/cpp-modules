def ford_johnson_sort(arr):
    """
    Entry point for the Ford-Johnson (Merge-Insertion) Sort.
    Wraps elements in a tuple (value, original_index) to handle duplicates 
    and guarantee stable, unique identities throughout the algorithm.
    """
    if len(arr) <= 1:
        return arr
        
    # WRAP: Create unique identities for every element
    wrapped_arr = [(val, i) for i, val in enumerate(arr)]
    
    # Run the recursive algorithm on the wrapped identities
    sorted_wrapped = _fj_recursive(wrapped_arr)
    
    # UNWRAP: Return just the sorted values
    return [item[0] for item in sorted_wrapped]


def _fj_recursive(arr):
    """
    The core recursive logic: pairs elements, sorts the winners, 
    and sets up the dispatch phase.
    """
    n = len(arr)
    if n <= 1:
        return arr

    # Step 1: Pair up elements into winners (A) and losers (B)
    pairs = []
    for i in range(0, n - 1, 2):
        # Compare the actual values (index 0 of the tuple)
        if arr[i][0] > arr[i+1][0]:
            pairs.append((arr[i], arr[i+1])) # (A, B)
        else:
            pairs.append((arr[i+1], arr[i])) # (A, B)

    # Catch the odd-element-out if the array length is uneven
    straggler = arr[-1] if n % 2 != 0 else None

    # Step 2: Prepare for recursion
    # Because our elements are unique tuples, we can use a dictionary
    # to perfectly remember which B belongs to which A.
    a_to_b = {pair[0]: pair[1] for pair in pairs}
    a_elements = [pair[0] for pair in pairs]

    # Recursively sort ONLY the 'A' elements (the winners)
    sorted_a = _fj_recursive(a_elements)

    # Step 3: Reconstruct the main chain and pending list
    main_chain = list(sorted_a)
    
    # Create a list of tuples: (pending_B_element, paired_A_element)
    # This guarantees the dispatch loop always knows exactly who to track
    pending_pairs = [(a_to_b[a], a) for a in sorted_a]

    if straggler:
        # The straggler has no paired A, so we map it to None
        pending_pairs.append((straggler, None))

    # Step 4: Execute the Jacobsthal reverse-insertion phase
    return _insert_pending_elements(main_chain, pending_pairs)


def _generate_insertion_order(pending_length):
    """
    Dynamically generates the 0-indexed reverse-group insertion order 
    using the Jacobsthal boundary formula.
    """
    if pending_length == 0:
        return []
    
    # Calculate boundaries (t_k) dynamically: 1, 3, 5, 11, 21, 43, 85...
    # Formula: t_k = (2^(k+1) + (-1)^k) / 3
    boundaries = []
    k = 1
    while True:
        t_k = (2**(k+1) + (1 if k % 2 == 0 else -1)) // 3
        boundaries.append(t_k)
        if t_k >= pending_length:
            break
        k += 1
        
    order = []
    last_boundary = 0
    
    for boundary in boundaries:
        # Cap the boundary if it exceeds our pending list
        current_boundary = min(boundary, pending_length)
        
        # Build the order going strictly backwards within the current group
        for i in range(current_boundary, last_boundary, -1):
            order.append(i) # Subtract 1 for 0-indexed arrays
            
        last_boundary = current_boundary
        
    return order


def _binary_search_insertion(chain, target_value, upper_bound):
    """
    A strict binary search that will not look past the upper_bound.
    """
    left = 0
    right = upper_bound
    
    while left < right:
        mid = (left + right) // 2
        # Compare the actual values (index 0 of the tuple)
        if chain[mid][0] < target_value:
            left = mid + 1
        else:
            right = mid
            
    return left


def _insert_pending_elements(main_chain, pending_pairs):
    """
    Executes the insertion dispatch, solving the moving target problem.
    """
    if not pending_pairs:
        return main_chain
        
    # Insert b1 for free (it is always strictly smaller than a1)
    b1, a1 = pending_pairs[0]
    main_chain.insert(0, b1)
    
    # Get the Jacobsthal insertion order
    order = _generate_insertion_order(len(pending_pairs))
    
    for i in order:
        # Skip index 0 because we already inserted b1
        if i == 0:
            continue
            
        target_b, paired_a = pending_pairs[i]
        
        # The moving target solution:
        if paired_a is not None:
            # We locate exactly where the paired A has shifted to
            upper_bound = main_chain.index(paired_a)
        else:
            # If it is the straggler, it can search the entire chain
            upper_bound = len(main_chain)
            
        # Execute custom binary search
        insert_idx = _binary_search_insertion(main_chain, target_b[0], upper_bound)
        
        # Insert the element, physically shifting the array in memory
        main_chain.insert(insert_idx, target_b)
        
    return main_chain

def main():
    while True:
        print(_generate_insertion_order(int(input("> "))))
main()