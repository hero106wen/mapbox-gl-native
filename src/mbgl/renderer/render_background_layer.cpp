#include <mbgl/renderer/render_background_layer.hpp>
#include <mbgl/style/layers/background_layer_impl.hpp>
#include <mbgl/renderer/bucket.hpp>

namespace mbgl {

RenderBackgroundLayer::RenderBackgroundLayer(std::shared_ptr<style::BackgroundLayer::Impl> impl)
        : RenderLayer(style::LayerType::Background, std::move(impl)),
          impl(static_cast<style::BackgroundLayer::Impl *>(baseImpl.get())) {
}

std::unique_ptr<RenderLayer> RenderBackgroundLayer::clone() const {
    return std::make_unique<RenderBackgroundLayer>(*this);
}

std::unique_ptr<Bucket> RenderBackgroundLayer::createBucket(const BucketParameters &,
                                                            const std::vector<const RenderLayer *> &) const {
    assert(false);
    return nullptr;
}

void RenderBackgroundLayer::cascade(const style::CascadeParameters &parameters) {
    unevaluated = impl->cascading.cascade(parameters, std::move(unevaluated));
}

bool RenderBackgroundLayer::evaluate(const style::PropertyEvaluationParameters &parameters) {
    evaluated = unevaluated.evaluate(parameters);

    passes = evaluated.get<style::BackgroundOpacity>() > 0 ? RenderPass::Translucent
                                                           : RenderPass::None;

    return unevaluated.hasTransition();
}

}
