# Urban Logistics for Parcel Delivery

## Project Description

This project focuses on optimizing parcel delivery logistics for a transportation company aiming to enhance productivity and competitiveness. The company handles both standard and express deliveries, where express parcels are delivered directly to customers, while standard parcels are assigned to couriers for delivery. The project considers three optimization scenarios:

1. **Courier Optimization**: Minimize the number of couriers without compromising parcel deliveries.
2. **Profit Optimization**: Maximize the company's profit by prioritizing more profitable parcels and using the most cost-efficient couriers.
3. **Express Delivery Optimization**: Minimize the average delivery time for express parcels.

## Optimization Scenarios

### **Scenario 1: Courier Optimization**
- **Objective**: Maximize the load transported by each courier while minimizing the total number of couriers.
- **Constraints**:
  - The total weight and volume of parcels assigned to a courier must not exceed its maximum capacity.
  - Higher-priority parcels must be assigned first.
- **Algorithm**:
  - Couriers are sorted in descending order of maximum weight capacity (with ties broken by volume capacity).
  - Parcels are sorted in descending order of priority.
  - A **backtracking algorithm** iterates over the parcels and assigns as many as possible to each courier.
  - This ensures the minimum number of couriers is used while maximizing their load.

- **Complexity Analysis**:
  - **Backtracking Assignment (`courierFiller`)**: \( O(n^2) \)
  - **Overall Complexity**: \( O(m \cdot n^2) \), where \( n \) is the number of parcels and \( m \) is the number of couriers.

### **Scenario 2: Profit Optimization**
- **Objective**: Maximize company profit by minimizing courier costs while prioritizing higher-profit deliveries.
- **Constraints**:
  - The total weight and volume assigned to each courier must not exceed its capacity.
- **Algorithm**:
  - Couriers are sorted by cost-efficiency (cost per unit of transported weight).
  - Parcels are sorted by profit and priority.
  - The **backtracking algorithm (`courierFiller`)** is used to fill each courier with the most profitable parcels.

- **Complexity Analysis**:
  - **Overall Complexity**: \( O(m \cdot n^2) \)

### **Scenario 3: Express Delivery Optimization**
- **Objective**: Minimize the average delivery time for express parcels.
- **Constraints**:
  - Each express delivery must be handled individually.
  - Deliveries must occur between 09:00 and 17:00.
- **Algorithm**:
  - Express parcels are sorted in ascending order of delivery time.
  - A **greedy algorithm** assigns deliveries based on the shortest travel time first.
  
- **Complexity Analysis**:
  - **Overall Complexity**: \( O(n \log n) \)

## Handling Undelivered Parcels
The application includes a function `endOfBusiness`, which:
- Removes successfully delivered standard parcels from the system.
- Increases the priority of undelivered parcels.
- Allows new parcels to be added at any time.

