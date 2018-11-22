#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAKE_COOR(x, y, z)		(((x) << 24) | ((y) << 16) | (z))
#define X(coor)					((coor) >> 24)
#define Y(coor)					(((coor) >> 16) & 0xFF)
#define Z(coor)					((coor) & 0xFF)

typedef struct BFS_NODE {
	int x, y, z;
	int time;
} BFS_NODE;

BFS_NODE _queue[60000];
int _queue_front, _queue_back;

void init_queue() {
	_queue_front = 0;
	_queue_back = 0;
}

void enqueue(const BFS_NODE* node) {
	_queue[_queue_back++] = *node;
}

BFS_NODE dequeue() {
	return _queue[_queue_front++];
}

int empty_queue() {
	return _queue_front == _queue_back;
}

int h, r, c;
int a, b;
int start, end;
int centers[100000];
char map[35][35][35];
char vis[35][35][35];

int abs(int x) {
	return x < 0 ? -x : x;
}

int check(int coor, int time) {
	// 0 1 2 3 2 1 0 1 2 3 2 1 0 1 2 3 2 1 ...
	int mapped = 0;
	if (a > 1) {
		int count = time / (a - 1);
		if (count & 1)
			mapped = (a - 1) - time % (a - 1);
		else
			mapped = time % (a - 1);
	}

	int my_x = X(coor), my_y = Y(coor), my_z = Z(coor);
	int op_x = X(centers[mapped]), op_y = Y(centers[mapped]), op_z = Z(centers[mapped]);

	int diff = INT_MAX;
	if (my_x == op_x && my_y == op_y)
		diff = abs(my_z - op_z);
	else if (my_x == op_x && my_z == op_z)
		diff = abs(my_y - op_y);
	else if (my_y == op_y && my_z == op_z)
		diff = abs(my_x - op_x);

	return diff > b;
}

int bfs() {
	static int dx[6] = { 1, -1, 0, 0, 0, 0 };
	static int dy[6] = { 0, 0, 1, -1, 0, 0 };
	static int dz[6] = { 0, 0, 0, 0, 1, -1 };

	memset(vis, 0, sizeof(vis));
	init_queue();

	BFS_NODE current = { X(start), Y(start), Z(start), 0 };
	if (!check(start, 0))
		return -1;
	else {
		vis[X(start)][Y(start)][Z(start)] = 1;
		enqueue(&current);
	}

	while (!empty_queue()) {
		current = dequeue();

		for (int i = 0; i < 6; ++i) {
			BFS_NODE next = { current.x + dx[i], current.y + dy[i], current.z + dz[i], current.time + 1 };
			if (next.x >= r || next.x < 0 || next.y >= c || next.y < 0 || next.z >= h || next.z < 0)
				continue;
			if (map[next.x][next.y][next.z] == '#')
				continue;
			if (vis[next.x][next.y][next.z])
				continue;
			if (!check(MAKE_COOR(next.x, next.y, next.z), next.time))
				continue;
			if (next.x == X(end) && next.y == Y(end) && next.z == Z(end))
				return next.time;

			vis[next.x][next.y][next.z] = 1;
			enqueue(&next);
		}
	}

	return -1;
}

int main(int argc, char* argv[]) {
	while (1) {
		scanf("%d%d%d", &h, &r, &c);
		if (h == 0 && r == 0 && c == 0)
			break;

		for (int i = 0; i < h; ++i) {
			for (int j = 0; j < r; ++j) {
				for (int k = 0; k < c; ++k) {
					scanf(" %c", &map[j][k][i]);
					if (map[j][k][i] == 'S')
						start = MAKE_COOR(j, k, i);
					else if (map[j][k][i] == 'E')
						end = MAKE_COOR(j, k, i);
				}
			}
		}

		scanf("%d%d", &a, &b);
		for (int i = 0; i < a; ++i) {
			int x, y, z;
			scanf("%d%d%d", &z, &x, &y);
			centers[i] = MAKE_COOR(x, y, z);
		    }

		int ans = bfs();
		if (ans == -1)
			printf("-1\n");
		else 
			printf("Escaped in %d minute(s).\n", ans);
	}

	return 0;
}
