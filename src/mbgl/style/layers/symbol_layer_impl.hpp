#pragma once

#include <mbgl/text/glyph.hpp>
#include <mbgl/util/variant.hpp>
#include <mbgl/sprite/sprite_atlas.hpp>
#include <mbgl/style/layer_impl.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/symbol_layer_properties.hpp>

namespace mbgl {

class BucketParameters;
class SymbolLayout;
class GeometryTileLayer;

namespace style {


class SymbolLayer::Impl : public Layer::Impl, public std::enable_shared_from_this<SymbolLayer::Impl> {
public:
    std::unique_ptr<Layer> clone() const override;
    std::unique_ptr<Layer> cloneRef(const std::string& id) const override;
    void stringifyLayout(rapidjson::Writer<rapidjson::StringBuffer>&) const override;

    std::unique_ptr<RenderLayer> createRenderLayer() const override;

    // TODO move to RenderSymbolLayer?
    std::unique_ptr<SymbolLayout> createLayout(const BucketParameters&, const std::vector<const RenderLayer*>&,
                                               const GeometryTileLayer&, GlyphDependencies&, IconDependencyMap&) const;

    SymbolLayoutProperties layout;
    SymbolPaintProperties::Cascading cascading;

    SpriteAtlas* spriteAtlas = nullptr;
};

} // namespace style
} // namespace mbgl
