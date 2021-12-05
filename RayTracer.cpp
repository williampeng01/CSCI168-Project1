#include "RayTracer.h"
#include <iostream>

void RayTracer::clear() const {
}

glm::vec3 RayTracer::trace(const Ray &ray,const vector<Object*> o, const glm::vec3 &_cEye, Light l) const {
  //Object ob;
  
  int parameter = -1;
  float minDist = INFINITY;
  for(int i = 0; i < o.size(); i++){
    Collision c = o[i]->collide(ray);
    if(c.m_type == Collision::Type::kHit){
      //std::cout << "Hit" << std::endl;
      float dist = glm::distance(ray.getO(), c.m_x);
      if(dist < minDist){
        parameter = i;
        minDist = dist;
      }
    }
    else { 
      //std::cout << "Miss" << std::endl;
    }
  }
  //std::cout << "Parameter = " << parameter << std::endl;
  if(parameter == -1 || parameter > o.size() - 1) return glm::vec3(0.0f,0.0f,0.0f);
  Collision c = o[parameter]->collide(ray);
  return l.multipleLights((c.m_material), (c.m_x), (c.m_normal), _cEye);
}

void RayTracer::render(const Scene& _scene,int g_height, int g_width, unique_ptr<glm::vec4[]>& g_frame) const {
  float d = 1;
  float t = d*tan(25.5);
  float b = -t;
  float l = (16/9)*b;
  float r = -l;
  g_frame = std::make_unique<glm::vec4[]>(g_width*g_height);
  //std::cout << "g_width = " << g_width << std::endl;
  //std::cout << "g_height = " << g_height << std::endl;
  for(int i=0; i<g_width; i++){
    //std::cout << i << std::endl;
    for(int j=0; j<g_height; j++){
      //std::cout << j << std::endl;
      float tau = l + ((r-l)*(i+0.5))/g_width;
      float sigma = b + ((t-b)*(j+0.5))/g_height;
      glm::vec3 o(0.0f, 0.0f, 0.0f);//eye
      glm::vec3 direction = glm::vec3(tau,sigma,-d);//need to caulculate

      Ray ray(o,direction);
      vector<Object*> v;
      vector<Sphere> sv = _scene.getS();
      vector<Plane>  pv = _scene.getP();
      for(int k = 0; k < sv.size()-1; k++){
        v.emplace_back(new Sphere(sv[k].getRadius(), sv[k].getCenter(), sv[k].getMaterial()));
      }
      Object* testObjectPoint = v[0];
      for(int k = 0; k < pv.size()-1; k++){
        v.emplace_back(new Plane(pv[k].getP(), pv[k].getN(), pv[k].getMaterial()));
      }
      vector<Light> lv = _scene.getL();
      glm::vec3 color = trace(ray, v, o, lv[0]);
      for(auto p : v){
        delete p;
      }
      v.clear();
      double a = j*g_width + i;
      //std::cout << a << std::endl;
      if(color[0] == 0 && color[1] == 0 && color[2] == 0) {
        g_frame[a] = glm::vec4(0.f,0.f,0.f,0.f);
      }
      else {
      g_frame[a] = glm::vec4(color[0],color[1],color[2],1.f);
      }
      
    }
  }
}