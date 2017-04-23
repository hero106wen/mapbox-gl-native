#pragma once

#include <mbgl/renderer/render_layer.hpp>
#include <mbgl/style/layers/symbol_layer.hpp>
#include <mbgl/style/layers/symbol_layer_properties.hpp>

namespace mbgl {

namespace style {

// {icon,text}-specific paint-property packs for use in the symbol Programs.
// Since each program deals either with icons or text, using a smaller property set
// lets us avoid unnecessarily binding attributes for properties the program wouldn't use.
class IconPaintProperties : public PaintProperties<
        IconOpacity,
        IconColor,
        IconHaloColor,
        IconHaloWidth,
        IconHaloBlur,
        IconTranslate,
        IconTranslateAnchor
> {};

class TextPaintProperties : public PaintProperties<
        TextOpacity,
        TextColor,
        TextHaloColor,
        TextHaloWidth,
        TextHaloBlur,
        TextTranslate,
        TextTranslateAnchor
> {};

// Repackaging evaluated values from SymbolLayoutProperties + SymbolPaintProperties
// for genericity over icons vs. text.
class SymbolPropertyValues {
public:
    // Layout
    AlignmentType pitchAlignment;
    AlignmentType rotationAlignment;
    PossiblyEvaluatedPropertyValue<float> layoutSize;

    // Paint
    std::array<float, 2> translate;
    TranslateAnchorType translateAnchor;
    float paintSize;

    float sdfScale;   // Constant (1.0 or 24.0)

    bool hasHalo;
    bool hasFill;
};

} // namespace style

class RenderSymbolLayer: public RenderLayer {
public:
    RenderSymbolLayer(std::shared_ptr<const style::SymbolLayer::Impl>);
    ~RenderSymbolLayer() final = default;

    std::unique_ptr<RenderLayer> clone() const override;

    void cascade(const style::CascadeParameters&) override;
    bool evaluate(const style::PropertyEvaluationParameters&) override;

    style::IconPaintProperties::Evaluated iconPaintProperties() const;
    style::TextPaintProperties::Evaluated textPaintProperties() const;

    style::SymbolPropertyValues iconPropertyValues(const style::SymbolLayoutProperties::PossiblyEvaluated&) const;
    style::SymbolPropertyValues textPropertyValues(const style::SymbolLayoutProperties::PossiblyEvaluated&) const;

    std::unique_ptr<Bucket> createBucket(const BucketParameters&, const std::vector<const RenderLayer*>&) const override;

    // Paint properties
    style::SymbolPaintProperties::Unevaluated unevaluated;
    style::SymbolPaintProperties::Evaluated evaluated;

    float iconSize = 1.0f;
    float textSize = 16.0f;

    const style::SymbolLayer::Impl* const impl;
};

template <>
inline bool RenderLayer::is<RenderSymbolLayer>() const {
    return type == style::LayerType::Symbol;
}

}
