#ifndef _SPHERE_H_
#define _SPHERE_H_

// GL
#include "GLInclude.h"

// Engine
#include "Collision.h"
#include "Material.h"
#include "Object.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Sphere
////////////////////////////////////////////////////////////////////////////////
/*class Sphere : public Object {
  public:
    Sphere(const glm::vec3 _c,
           float _r) :
      m_center{_c}, m_radius{_r} {}

    Collision collide(const Ray& _ray) const override;
    
  private:
    glm::vec3  m_center; ///< Center
    float      m_radius; ///< Radius
    Material m_material; ///< Material
};*/

class Sphere : public Object{
  public:
    Sphere(const float& r,const glm::vec3& c, const Material* m):
    radius(r), center(c), m_material(m) {};
    const float getRadius() const { return radius; }
    const glm::vec3 getCenter() const { return center; }
    const Material* getMaterial() const { return m_material;}

    Collision collide(const Ray& _ray) const override; // should have override at the end, but produces error if it is there:
                                              // only virtual member functions can be marked 'override'
  private:
    float radius;
    glm::vec3 center;
    const Material* m_material;
};
#endif
