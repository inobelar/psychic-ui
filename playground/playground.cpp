#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <array>

class A{
public:
    std::string a{"prout"};
};

int main() {
    std::array<A,2> as;
    A a;
    a.a = "coucou";
    as[0] = a;
    a.a = "prout";
    as[1] = a;

    std::cout << as[0].a << " " << as[1].a << std::endl;
}
//#include <iostream>
//#include <Signal.hpp>
//#include <Observer.hpp>
//
//using namespace psychic_ui;
//
//class A: public Observer {
//public:
//    using Observer::subscribeTo;
//    using Observer::slots;
//};
//
//int main() {
//    std::cout << "Playground" << std::endl;
//
//    Signal<> s1{};
//    auto s1s = s1.subscribe([](){
//        std::cout << "No args" << std::endl;
//    });
//    s1.emit();
//    s1.unsubscribe(s1s);
//    s1.emit();
//
//    Signal<> s2{};
//    {
//        auto s2s = s2.subscribe(
//            []() {
//                std::cout << "No args, should die" << std::endl;
//            }
//        );
//        s2.emit();
//    }
//    s2.emit();
//
//    Signal<> s2b{};
//    {
//        s2b.subscribe(
//            []() {
//                std::cout << "No args, not saved, should die" << std::endl;
//            }
//        );
//        s2b.emit();
//    }
//    s2b.emit();
//
//    Signal<> s3{};
//    {
//        A a{};
//        a.subscribeTo(
//            s3, []() {
//                std::cout << "In observer, should die" << std::endl;
//            }
//        );
//        s3.emit();
//    }
//    s3.emit();
//
//    {
//        Signal<>* s4 = new Signal<>();
//        A a{};
//        a.subscribeTo(
//            *s4, []() {
//                std::cout << "In observer, should die" << std::endl;
//            }
//        );
//        s4->emit();
//        delete s4;
//        std::cout << a.slots.size() << std::endl;
//    }
//}
