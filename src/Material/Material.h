#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <string>

typedef unsigned long UNIQUE_MAT_ID;
constexpr UNIQUE_MAT_ID generate_unique_mat_id(const char* mat_name)
{
  unsigned long mat_id;
  for (char c : mat_name)
    mat_id += c;

  return mat_id;
}

class Material
{
  UNIQUE_MAT_ID _id{ };

  Material() = default;
  Material(const char* mat_name)
  {
    _id = generate_unique_mat_id(mat_name);
  }
};

#endif // !_MATERIAL_H_