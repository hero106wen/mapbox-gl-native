#pragma once

#include <mbgl/style/layer_impl.hpp>
#include <mbgl/style/layers/fill_extrusion_layer.hpp>
#include <mbgl/style/layers/fill_extrusion_layer_properties.hpp>

namespace mbgl {
namespace style {

class FillExtrusionLayer::Impl : public Layer::Impl, public std::enable_shared_from_this<FillExtrusionLayer::Impl> {
public:
    std::unique_ptr<Layer> clone() const override;
    std::unique_ptr<Layer> cloneRef(const std::string& id) const override;
    void stringifyLayout(rapidjson::Writer<rapidjson::StringBuffer>&) const override;

    std::unique_ptr<RenderLayer> createRenderLayer() const override;

    FillExtrusionPaintProperties::Cascading cascading;

    //style::FillExtrusionLayer::Impl* const impl;
};

} // namespace style
} // namespace mbgl
