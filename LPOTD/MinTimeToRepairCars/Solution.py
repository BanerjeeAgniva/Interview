# https://leetcode.com/problems/minimum-time-to-repair-cars/description/?envType=daily-question&envId=2025-03-16

class Solution(object):
    def repairCars(self, ranks, cars):
        def canRepairInTime(time):
            total_cars = 0
            for r in ranks:
                total_cars += int((time // r) ** 0.5)  # Max cars this mechanic can repair
            return total_cars >= cars
        
        left, right = 1, max(ranks) * (cars ** 2)
        while left < right:
            mid = (left + right) // 2
            if canRepairInTime(mid):
                right = mid  # Try for a lower time
            else:
                left = mid + 1  # Increase time
            
        return left
        