void build_rotmatrix(float m[4][4], float q[4]);
//static void normalize_quat(float q[4]);
void add_quats(float q1[4], float q2[4], float dest[4]);
void negate_quat(float q[4], float nq[4]);
//static float tb_project_to_sphere(float r, float x, float y);
void trackball(float q[4], float p1x, float p1y, float p2x, float p2y);
void axis_to_quat(float a[3], float phi, float q[4]);
void vzero(float *v);
void vset(float *v, float x, float y, float z);
void vsub(const float *src1, const float *src2, float *dst);
void vcopy(const float *v1, float *v2);
void vcross(const float *v1, const float *v2, float *cross);
float vlength(const float *v);
void vscale(float *v, float div);
void vnormal(float *v);
float vdot(const float *v1, const float *v2);
void vadd(const float *src1, const float *src2, float *dst);