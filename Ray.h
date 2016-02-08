#ifndef RAY_H
#define RAY_H
#include "Vec3.h"
#include <assert.h> 
class Ray {
public:
  Vec3f origin;
  Vec3f direction;
  Ray(Vec3f o,Vec3f direct){
    origin = o;
    direction =normalize(direct);

  }

  bool rect_is_intersect_with(Vec3f* Rect)
  {
    return is_intersect_with(Rect[0], Rect[1], Rect[3])||is_intersect_with(Rect[1],Rect[2],Rect[3]);
  }

  Vec3f rect_intersect_at(Vec3f* Rect, float & b0, float& b1, float& b2, float& b3)
  {
    if(is_intersect_with(Rect[0], Rect[1], Rect[3])) return intersect_at(Rect[0], Rect[1], Rect[3], b0,b1,b3);
    else if(is_intersect_with(Rect[1],Rect[2], Rect[3])) return intersect_at(Rect[1], Rect[2], Rect[3],b1,b2,b3);
    else assert(-1);
  }

  bool is_intersect_with(Vec3f p0, Vec3f p1, Vec3f p2)
  {
  Vec3f e0(p1-p0);
  Vec3f e1(p2-p0);
  Vec3f n(cross(e0,e1)/cross(e0,e1).length());
  Vec3f q(cross(direction,e1));
  double a = dot(e0,q);
  if(dot(n,direction) >= 0 || fabs(a) < 0.00001)
    return false;
  Vec3f s((origin-p0)/a);
  Vec3f r(cross(s,e0));
  double b0(dot(s,q));
  double b1(dot(r,direction));
  double b2(1-b0-b1);
  if(b0 < 0 || b1 < 0 || b2 < 0)
    return false;
  double t(dot(e1,r));
  if(t<0)
    return false;
  return true;

  }
  Vec3f intersect_at(Vec3f p0, Vec3f p1, Vec3f p2, float & b0, float& b1, float& b2)
  {
    Vec3f e0(p1-p0);
    Vec3f e1(p2-p0);
    Vec3f n(cross(e0,e1)/cross(e0,e1).length());
    Vec3f q(cross(direction,e1));
    double a = dot(e0,q);
    if(dot(n,direction) >= 0 || fabs(a) < 0.00001)
      assert(-1);
    Vec3f s((origin-p0)/a);
    Vec3f r(cross(s,e0));
    b0 = (dot(s,q));
    b1 = (dot(r,direction));
    b2 = (1-b0-b1);
    if(b0 < 0 || b1 < 0 || b2 < 0)
      assert(-1);
    double t(dot(e1,r));
    if(t<0)
      assert(-1);
    return Vec3f(b0 * p0+b1*p1+b2*p2);
  }
};
#endif
