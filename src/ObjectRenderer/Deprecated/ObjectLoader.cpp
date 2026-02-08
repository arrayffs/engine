#include "ObjectLoader.h"
#include "Triangulation.h"
#include "../Util/Defines.h"

#include <print>
#include <fstream>
#include <glm/glm.hpp>

struct face_t {
  std::string _mat;
  int _smoothing;
  std::vector<vertex_t> _faces; // v, vn, vt
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
      wavefront._material_file = line.substr(7);
    }
    else if (line.starts_with("o ")) {
      wavefront._object_name = line.substr(2);
    }
    else if (line.starts_with("v ")) {
      line = line.substr(2);

      std::string c_buffer;
      glm::vec3 vertex = glm::vec3(0);
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = std::stof(c_buffer.c_str());
            break;
          case 1:
            vertex.y = std::stof(c_buffer.c_str());
            break;
          }
          c_buffer = "";
          ++v_idx;
        }
      }

      vertex.z = std::stof(c_buffer.c_str());
      wavefront._vertex.push_back(vertex);
    }
    else if (line.starts_with("vn ")) {
      line = line.substr(3);

      std::string c_buffer;
      glm::vec3 vertex = glm::vec3(0);
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = std::stof(c_buffer.c_str());
            break;
          case 1:
            vertex.y = std::stof(c_buffer.c_str());
            break;
          }
          c_buffer = "";
          ++v_idx;
        }
      }

      vertex.z = std::stof(c_buffer.c_str());
      wavefront._vertex_normal.push_back(vertex);
    }
    else if (line.starts_with("vt ")) {
      line = line.substr(3);

      std::string c_buffer;
      glm::vec3 vertex = glm::vec3(0);
      int v_idx{ 0 };
      for (char c : line) {
        if (c != ' ' && c != '\n')
          c_buffer.push_back(c);
        else {
          switch (v_idx) {
          case 0:
            vertex.x = std::stof(c_buffer.c_str());
            break;
          case 1:
            vertex.y = std::stof(c_buffer.c_str());
            break;
          }
          c_buffer = "";
          ++v_idx;
        }
      }

      vertex.z = std::stof(c_buffer.c_str());
      wavefront._texture_vertex.push_back(vertex);
    }
    else if (line.starts_with("s ")) {
      wavefront._faces.push_back(face_t{ ._smoothing = std::stoi(line.substr(2))});
    }
    else if (line.starts_with("usemtl")) {
      wavefront._faces[wavefront._faces.size() - 1]._mat = line.substr(7);
    }
    else if (line.starts_with("f ")) {
      line = line.substr(2);
     
      int it{ 0 };
      vertex_t face;
      std::string nbuf{};
      for (char& c : line) {
        if (c == '/') {
          int cit = atoi(nbuf.c_str()) - 1;
          switch (it)
          {
          case 0:
            if (cit >= wavefront._vertex.size()) __debugbreak();
            face._world_pos = wavefront._vertex[cit];
            break;
          case 1:
            if (cit >= wavefront._texture_vertex.size()) __debugbreak();
            face._tex_pos = wavefront._texture_vertex[cit];
            break;
          }
          
          nbuf = "";
          it++;
        } else if (c == ' ') {
          it = 0;
          wavefront._faces[wavefront._faces.size() - 1]._faces.push_back(face);
          face = {};
          nbuf = "";
        }
        else {
          nbuf.push_back(c);
        }
      }


      wavefront._faces[wavefront._faces.size() - 1]._faces.push_back(face);
    }
  }

  std::vector<unsigned int> indices;
  std::vector<vertex_t> vb;
  unsigned int it = 0;
  for (auto& faces : wavefront._faces)
    vb.insert(vb.end(), faces._faces.begin(), faces._faces.end());

  triangulation::delaunay(vb);

  return {
    vb,
    indices,
    "res/Shaders/monocolor_basic.vert", "res/Shaders/monocolor_basic.frag"
  };
}