#ifndef IRENDERABLE_HPP_
#define IRENDERABLE_HPP_

/**
 * @brief: Abstract base class for game objects that are renderable
 */

class IRenderable {
    public:
        virtual ~IRenderable() {}
        virtual void render() const = 0;
};
#endif