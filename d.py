import math

def normalize_earring(earring):
    # Calculate centroid
    centroid_x = sum(x for x, y in earring) / len(earring)
    centroid_y = sum(y for x, y in earring) / len(earring)

    # Translate to origin
    earring = [(x - centroid_x, y - centroid_y) for x, y in earring]

    # Sort by polar angle
    earring = sorted(earring, key=lambda p: math.atan2(p[1], p[0]))

    # Find minimal lexicographical rotation of the sorted earring
    min_rotation = earring
    for i in range(1, len(earring)):
        rotated = earring[i:] + earring[:i]
        if rotated < min_rotation:
            min_rotation = rotated
    
    return min_rotation

def is_cyclic_permutation(list1, list2):
    """Check if list1 is a cyclic permutation of list2."""
    if len(list1) != len(list2):
        return False
    # Check for all cyclic permutations
    for i in range(len(list1)):
        if list1 == list2[i:] + list2[:i]:
            return True
    return False

def find_pair(earrings):
    # Normalize each earring
    normalized_earrings = [normalize_earring(earring) for earring in earrings]

    # Compare each pair of earrings
    for i in range(len(normalized_earrings)):
        for j in range(i + 1, len(normalized_earrings)):
            if normalized_earrings[i] == normalized_earrings[j]:
                return (i + 1, j + 1)

    return None

def main():
    n = int(input("Enter the number of earrings: "))

    earrings = []
    for i in range(n):
        k = int(input(f"Enter the number of vertices for earring {i+1}: "))
        earring = []
        for j in range(k):
            x, y = map(int, input(f"Enter vertex {j+1} (x y): ").split())
            earring.append((x, y))
        earrings.append(earring)

    pair = find_pair(earrings)
    if pair:
        print("Pair found:", pair)
    else:
        print("No pair found")

if __name__ == "__main__":
    main()
