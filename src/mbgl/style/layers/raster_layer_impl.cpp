#include <mbgl/style/layers/raster_layer_impl.hpp>
#include <mbgl/renderer/render_raster_layer.hpp>

namespace mbgl {
namespace style {

std::unique_ptr<RenderLayer> RasterLayer::Impl::createRenderLayer() const {
    return std::make_unique<RenderRasterLayer>(std::make_shared<style::RasterLayer::Impl>(*this));
}

} // namespace style
} // namespace mbgl
