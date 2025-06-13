import heapq

def dijkstra(tablero, pos, paquete):
    xi = pos[0]
    yi = pos[1]
    xf = paquete[0]
    yf = paquete[1]
    n = tablero.len()
    start = xi * n + yi
    end = xf * n + yf
    distances = [float('inf')] * (n * n)
    distances[start] = 0
    heap = [(0, start)]
    visited = set()
    previous = [None] * (n * n)
    while heap:
        (current_distance, current_vertex) = heapq.heappop(heap)
        if current_vertex == end:
            path = []
            while current_vertex is not None:
                row = current_vertex // n
                col = current_vertex % n
                path.append([row, col])
                current_vertex = previous[current_vertex]
            return path[::-1]
        if current_vertex in visited:
            continue
        visited.add(current_vertex)
        for neighbor in get_neighbors(current_vertex, n, tablero):
            distance = current_distance + neighbor[1]
            if distance < distances[neighbor[0]]:
                distances[neighbor[0]] = distance
                previous[neighbor[0]] = current_vertex
                heapq.heappush(heap, (distance, neighbor[0]))
    return None

def get_neighbors(vertex, n, tablero):
    neighbors = []
    row = vertex // n
    col = vertex % n
    if row > 0:
        neighbor = (row - 1) * n + col
        weight = tablero.getCasillas()[row - 1][col].t
        capacity = tablero.getCasillas()[row - 1][col].f
        if capacity > 0:
            neighbors.append((neighbor, weight))
        if col > 0:
            neighbor = (row - 1) * n + col - 1
            weight = tablero.getCasillas()[row - 1][col - 1].t
            capacity = tablero.getCasillas()[row - 1][col - 1].f
            if capacity > 0:
                neighbors.append((neighbor, weight))
        if col < n - 1:
            neighbor = (row - 1) * n + col + 1
            weight = tablero.getCasillas()[row - 1][col + 1].t
            capacity = tablero.getCasillas()[row - 1][col + 1].f
            if capacity > 0:
                neighbors.append((neighbor, weight))
    if row < n - 1:
        neighbor = (row + 1) * n + col
        weight = tablero.getCasillas()[row + 1][col].t
        capacity = tablero.getCasillas()[row + 1][col].f
        if capacity > 0:
            neighbors.append((neighbor, weight))
        if col > 0:
            neighbor = (row + 1) * n + col - 1
            weight = tablero.getCasillas()[row + 1][col - 1].t
            capacity = tablero.getCasillas()[row + 1][col - 1].f
            if capacity > 0:
                neighbors.append((neighbor, weight))
        if col < n - 1:
            neighbor = (row + 1) * n + col + 1
            weight = tablero.getCasillas()[row + 1][col + 1].t
            capacity = tablero.getCasillas()[row + 1][col + 1].f
            if capacity > 0:
                neighbors.append((neighbor, weight))
    if col > 0:
        neighbor = row * n + col - 1
        weight = tablero.getCasillas()[row][col - 1].t
        capacity = tablero.getCasillas()[row][col - 1].f
        if capacity > 0:
            neighbors.append((neighbor, weight))
    if col < n - 1:
        neighbor = row * n + col + 1
        weight = tablero.getCasillas()[row][col + 1].t
        capacity = tablero.getCasillas()[row][col + 1].f
        if capacity > 0:
            neighbors.append((neighbor, weight))
    return neighbors