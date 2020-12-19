#pragma once

#include <string>

namespace ast::assets
{
    enum class Pipeline
    {
        Default
    };

    enum class Texture
    {
        Crate,
		RedCrossHatch
    };

    std::string resolvePipelinePath(const ast::assets::Pipeline& pipeline);

    std::string resolveTexturePath(const ast::assets::Texture& texture);

} // namespace ast::assets
