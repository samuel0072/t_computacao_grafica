#define MAX_VERTICES 200000

typedef struct Vec2 Vec2;

typedef struct Vec3 Vec3;

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

int VERTEX_COUNT;
Vec3 *VERTICES;
Vec3 *NORMALS;
Vec2 *TEX_COORDS;


int load_obj(const char* path);

void init_vecs();

