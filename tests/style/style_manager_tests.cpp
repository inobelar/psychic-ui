#include <memory>
#include "catch.hpp"
#include <psychicui/style/StyleManager.hpp>
#include <psychicui/style/Style.hpp>
#include <psychicui/Component.hpp>

using namespace psychicui;

TEST_CASE("basic style getter", "[style]") {
    auto styleManager = std::make_shared<StyleManager>();

    SECTION("returns dummy style if selector is garbage") {
        auto style = styleManager->style("");
        REQUIRE(style == Style::dummyStyle.get());
    }

    SECTION("returns the same style with same name") {
        auto style = styleManager->style("component");
        REQUIRE(style == styleManager->style("component"));
    }

    SECTION("in a case insensitive manner") {
        auto style = styleManager->style("component");
        REQUIRE(style == styleManager->style("Component"));
        REQUIRE(style == styleManager->style("cOmPoNeNt"));
    }
}

SCENARIO("styles can be declared and computed") {
    auto styleManager = std::make_shared<StyleManager>();

    GIVEN("a single component") {
        auto component = std::make_shared<Component>();
        component->setStyleManager(styleManager);

        WHEN("component has no class names") {

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                component->updateStyle();
                auto s = styleManager->computeStyle(component.get());
                REQUIRE(*style == *s);
            }

            THEN("it should not retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }
        }

        WHEN("component has class name") {
            component->setClassNames({"class"});

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \".other\" selector") {
                auto style = styleManager->style(".other");
                style->set(fontFamily, ".other"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \".class.other\" selector") {
                auto style = styleManager->style(".class.other");
                style->set(fontFamily, ".class.other"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }
        }

        WHEN("component has multiple class names") {
            component->setClassNames({"class", "other"});

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \"component.class.other\" selector") {
                auto style = styleManager->style("component.class.other");
                style->set(fontFamily, "component.class.other"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \"component.other.class\" selector") {
                auto style = styleManager->style("component.other.class");
                style->set(fontFamily, "component.other.class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \".other\" selector") {
                auto style = styleManager->style(".other");
                style->set(fontFamily, ".other"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \".class.other\" selector") {
                auto style = styleManager->style(".class.other");
                style->set(fontFamily, ".class.other"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }

            THEN("it should retrieve a \".other.class\" selector") {
                auto style = styleManager->style(".other.class");
                style->set(fontFamily, ".other.class"); // Just easier to check like this
                component->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(component.get()));
            }
        }

    }

    GIVEN("a parent/child component relationship") {
        auto parent = std::make_shared<Component>();
        parent->setStyleManager(styleManager);
        auto child = std::make_shared<Component>();
        parent->add(child);

        WHEN("neither have class names") {

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component component\" selector") {
                auto style = styleManager->style("component component");
                style->set(fontFamily, "component component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component.class component\" selector") {
                auto style = styleManager->style("component.class component");
                style->set(fontFamily, "component.class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component component.class\" selector") {
                auto style = styleManager->style("component component.class");
                style->set(fontFamily, "component component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }
        }

        WHEN("parent has a class names") {
            parent->setClassNames({"class"});

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component component\" selector") {
                auto style = styleManager->style("component component");
                style->set(fontFamily, "component component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component.class component\" selector") {
                auto style = styleManager->style("component.class component");
                style->set(fontFamily, "component.class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component component.class\" selector") {
                auto style = styleManager->style("component component.class");
                style->set(fontFamily, "component component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class component\" selector") {
                auto style = styleManager->style(".class component");
                style->set(fontFamily, ".class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \".class .other\" selector") {
                auto style = styleManager->style(".class .other");
                style->set(fontFamily, ".class .other"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }
        }

        WHEN("child has a class names") {
            child->setClassNames({"class"});

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component component\" selector") {
                auto style = styleManager->style("component component");
                style->set(fontFamily, "component component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component.class component\" selector") {
                auto style = styleManager->style("component.class component");
                style->set(fontFamily, "component.class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component component.class\" selector") {
                auto style = styleManager->style("component component.class");
                style->set(fontFamily, "component component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \".class component\" selector") {
                auto style = styleManager->style(".class component");
                style->set(fontFamily, ".class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \".class .other\" selector") {
                auto style = styleManager->style(".class .other");
                style->set(fontFamily, ".class .other"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }
        }

        WHEN("both have a class names") {
            parent->setClassNames({"class"});
            child->setClassNames({"other"});

            THEN("it should retrieve a \"component\" selector") {
                auto style = styleManager->style("component");
                style->set(fontFamily, "component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component component\" selector") {
                auto style = styleManager->style("component component");
                style->set(fontFamily, "component component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component.class\" selector") {
                auto style = styleManager->style("component.class");
                style->set(fontFamily, "component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \"component.class component\" selector") {
                auto style = styleManager->style("component.class component");
                style->set(fontFamily, "component.class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component .class\" selector") {
                auto style = styleManager->style("component .class");
                style->set(fontFamily, "component .class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should not retrieve a \"component component.class\" selector") {
                auto style = styleManager->style("component component.class");
                style->set(fontFamily, "component component.class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style != *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class component\" selector") {
                auto style = styleManager->style(".class component");
                style->set(fontFamily, ".class component"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class\" selector") {
                auto style = styleManager->style(".class");
                style->set(fontFamily, ".class"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class .other\" selector") {
                auto style = styleManager->style(".class .other");
                style->set(fontFamily, ".class .other"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }

            THEN("it should retrieve a \".class component.other\" selector") {
                auto style = styleManager->style(".class component.other");
                style->set(fontFamily, ".class component.other"); // Just easier to check like this
                parent->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(child.get()));
            }
        }

    }

    GIVEN("three component") {
        auto a = std::make_shared<Component>();
        a->setStyleManager(styleManager);
        auto b = std::make_shared<Component>();
        a->add(b);
        auto c = std::make_shared<Component>();
        b->add(c);

        WHEN("skipping a node") {
            a->setClassNames({"first"});
            c->setClassNames({"last"});

            THEN("it should retrieve a \".first\" selector") {
                auto style = styleManager->style(".first");
                style->set(fontFamily, ".first"); // Just easier to check like this
                a->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(c.get()));
            }

            THEN("it should retrieve a \".first .last\" selector") {
                auto style = styleManager->style(".first .last");
                style->set(fontFamily, ".first .last"); // Just easier to check like this
                a->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(c.get()));
            }

            THEN("it should retrieve a \".first component .last\" selector") {
                auto style = styleManager->style(".first component .last");
                style->set(fontFamily, ".first component .last"); // Just easier to check like this
                a->updateStyle();
                REQUIRE(*style == *styleManager->computeStyle(c.get()));
            }

        }

    }

}

TEST_CASE("Regressions") {
    auto styleManager = std::make_shared<StyleManager>();

    SECTION("Hovered button should transfer color to label") {
        // We're not testing buttons here, so we're emulating with only components

        auto windowStyle = styleManager->style(".window");
        windowStyle->set(color, 0xFF00FF00);

        auto style = styleManager->style(".button");
        style->set(color, 0xFFFF0000);

        auto styleHover = styleManager->style(".button:hover");
        styleHover->set(color, 0xFF0000FF);

        auto window = std::make_shared<Component>();
        window->setStyleManager(styleManager);
        window->setClassNames({"window"});

        auto button = std::make_shared<Component>();
        button->setClassNames({"button"});
        window->add(button);

        auto label = std::make_shared<Component>();
        button->add(label);

        std::unique_ptr<Style> buttonComputed = std::move(styleManager->computeStyle(button.get()));
        std::unique_ptr<Style> labelComputed  = std::move(styleManager->computeStyle(label.get()));
        REQUIRE(buttonComputed->get(color) == 0xFFFF0000);
        REQUIRE(labelComputed->get(color) == 0xFFFF0000);

        button->setMouseOver(true);
        buttonComputed = std::move(styleManager->computeStyle(button.get()));
        labelComputed  = std::move(styleManager->computeStyle(label.get()));
        REQUIRE(buttonComputed->get(color) == 0xFF0000FF);
        REQUIRE(labelComputed->get(color) == 0xFF0000FF);

    }

    SECTION("Pseudos should be prioritized") {
        // We're not testing buttons here, so we're emulating with only components

        styleManager->style(".test")
                    ->set(color, 0xFFFF0000);

        styleManager->style(".test:hover")
                    ->set(color, 0xFF0000FF);

        styleManager->style(".test:active")
                    ->set(color, 0xFF00FF00);

        auto component = std::make_shared<Component>();
        component->setStyleManager(styleManager);
        component->setClassNames({"test"});

        REQUIRE(styleManager->computeStyle(component.get())->get(color) == 0xFFFF0000);

        component->setMouseOver(true);
        REQUIRE(styleManager->computeStyle(component.get())->get(color) == 0xFF0000FF);

        component->setMouseDown(true);
        REQUIRE(styleManager->computeStyle(component.get())->get(color) == 0xFF00FF00);

    }

}