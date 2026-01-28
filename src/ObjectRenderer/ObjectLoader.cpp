#include "ObjectLoader.h"

#include "../Util/Defines.h"

#include <fstream>
#include <glm/glm.hpp>

struct face_t {
  std::string _mat;
  bool _shaded;
  std::vector<glm::uvec3> _faces;
};

struct wavefront_t {
  std::string _material_file;
  std::string _object_name;
  std::vector<glm::vec3> _vertex;
  std::vector<glm::vec3> _vertex_normal;
  std::vector<glm::vec2> _texture_vertex;
  std::vector<face_t> _faces;
};

ObjectRenderer object_loader::load_object(const std::string& path)
{
  std::ifstream file(path);
  assert(file.is_open() == true);

  std::string buffer;
  wavefront_t wavefront;

  for (std::string line; std::getline(file, line);) {
    if (line.starts_with("mtllib ")) {
      wavefront._material_file = line.substr(8);
    }
    else if (line.starts_with("o ")) {
      wavefront._object_name = line.substr(3);
    }
    else if (line.starts_with("v ")) {
      line = line.substr(3);

      std::string c_buffer;
      glm::vec3 vertex;
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = atoi(c_buffer.c_str());
            break;
          case 1:
            vertex.y = atoi(c_buffer.c_str());
            break;
          case 2:
            vertex.z = atoi(c_buffer.c_str());
            break;
          }
          ++v_idx;
        }
      }

      wavefront._vertex.push_back(vertex);
    }
    else if (line.starts_with("vn ")) {
      line = line.substr(4);

      std::string c_buffer;
      glm::vec3 vertex;
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = atoi(c_buffer.c_str());
            break;
          case 1:
            vertex.y = atoi(c_buffer.c_str());
            break;
          case 2:
            vertex.z = atoi(c_buffer.c_str());
            break;
          }
          ++v_idx;
        }
      }

      wavefront._vertex_normal.push_back(vertex);
    }
    else if (line.starts_with("vt ")) {
      line = line.substr(4);

      std::string c_buffer;
      glm::vec2 vertex;
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = atoi(c_buffer.c_str());
            break;
          case 1:
            vertex.y = atoi(c_buffer.c_str());
            break;
          }
          ++v_idx;
        }
      }

      wavefront._texture_vertex.push_back(vertex);
    }
    else if (line.starts_with("s ")) {
      wavefront._faces.push_back(face_t{ ._shaded = (bool)line[line.size() - 1] });
    }
    else if (line.starts_with("usemtl")) {
      wavefront._faces[wavefront._faces.size() - 1]._mat = line.substr(8);
    }
    else if (line.starts_with("f ")) {
      line = line.substr(3);
      std::vector<glm::uvec3> faces(1, {});
      size_t i{ 0 };
      size_t j{ 0 };

      for (char c : line) {
        if (c == '/')
          j++;
        else if (c == ' ' || c == '\n') {
          faces.push_back({});
          i++;
        }
        else {
          switch (j) {
          case 0:
            faces[i].x = atoi(std::to_string(c).c_str());
            break;
          case 1:
            faces[i].y = atoi(std::to_string(c).c_str());
            break;
          case 2:
            faces[i].z = atoi(std::to_string(c).c_str());
            break;
          }
        }
      }

      auto& _faces = wavefront._faces[wavefront._faces.size() - 1]._faces;
      _faces.insert(_faces.end(), faces.begin(), faces.end());
    }
  }

  std::vector<unsigned int> indices;
  for (auto& faces : wavefront._faces) {
    for (auto& face : faces._faces) {
      indices.push_back(face.x);
      indices.push_back(face.y);
      indices.push_back(face.z);
    }
  }

  /*ObjectRenderer objr(
    wavefront._vertex,
    indices,
    "res/Shaders/monocolor_basic.vert", "res/Shaders/monocolor_basic.frag"
  );*/

  return {};
}