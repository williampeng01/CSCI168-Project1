#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Scene.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief Abstract base for a renderer
////////////////////////////////////////////////////////////////////////////////
class Renderer {
  public:
    // Constructors and destructors
    Renderer() = default;
    virtual ~Renderer() = default;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Clear the frame
    virtual void clear() const = 0;

    ////////////////////////////////////////////////////////////////////////////
    /// @brief Render a scene
    /// @param _scene Scene
    virtual void render(const Scene& _scene,int g_height, int g_width, std::unique_ptr<glm::vec4[]> g_frame) const = 0;
};

#endif