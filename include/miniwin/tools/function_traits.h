#pragma once
#include <tuple>

namespace miniwin {
namespace internal {
template<typename Func>
struct FunctionTraits;

template<typename Ret, typename... Args>
struct FunctionTraits<Ret(Args...)> {
    using Return = Ret;
    using Arguments = std::tuple<Args...>;
    using Function = Ret(*)(Args...);

    static constexpr size_t kArgumentCount = sizeof...(Args);
    static constexpr bool kIsMemberFunction = false;
    static constexpr bool kIsPointerToFunction = false;
    static constexpr bool kIsFunctorObject = false;
};


template<typename Ret, typename... Args>
struct FunctionTraits<Ret(*)(Args...)> {
    using Return = Ret;
    using Arguments = std::tuple<Args...>;
    using Function = Ret(*)(Args...);

    static constexpr size_t kArgumentCount = sizeof...(Args);
    static constexpr bool kIsMemberFunction = false;
    static constexpr bool kIsPointerToFunction = true;
    static constexpr bool kIsFunctorObject = false;
};

template<typename Ret, typename Obj, typename... Args>
struct FunctionTraits<Ret(Obj::*)(Args...)> {
    using Return = Ret;
    using Arguments = std::tuple<Args...>;
    using Function = Ret(Obj::*)(Args...);
    using Object = Obj;

    static constexpr size_t kArgumentCount = sizeof...(Args);
    static constexpr bool kIsMemberFunction = true;
    static constexpr bool kIsPointerToFunction = true;
    static constexpr bool kIsFunctorObject = false;
};

template<typename Ret, typename Obj, typename... Args>
struct FunctionTraits<Ret(Obj::*)(Args...) const> {
    using Return = Ret;
    using Arguments = std::tuple<Args...>;
    using Function = Ret(Obj::*)(Args...) const;
    using Object = Obj;

    static constexpr size_t kArgumentCount = sizeof...(Args);
    static constexpr bool kIsMemberFunction = true;
    static constexpr bool kIsPointerToFunction = true;
    static constexpr bool kIsFunctorObject = false;
};

template<typename Func>
struct FunctionTraits {
private:
    using Wrapper = FunctionTraits<decltype(&Func::operator())>;
public:
    using Return = typename Wrapper::Return;
    using Arguments = typename Wrapper::Arguments;
    using Function = typename Wrapper::Function;

    static constexpr size_t kArgumentCount = Wrapper::kArgumentCount;
    static constexpr bool kIsMemberFunction = false;
    static constexpr bool kIsPointerToFunction = false;
    static constexpr bool kIsFunctorObject = true;
};

template<typename Func>
struct FunctionTraits<Func&> : public FunctionTraits<Func> {};

template<typename Func>
struct FunctionTraits<Func&&> : public FunctionTraits<Func> {};

template<typename... ExpectedArgs, typename... ActualArgs>
consteval bool MatchArguments(std::tuple<ExpectedArgs...>, std::tuple<ActualArgs...>) {
    return (... && std::is_convertible_v<ActualArgs, ExpectedArgs>);
}

template<typename ExpectedFunc, typename ActualFunc>
consteval bool MatchFunctionArguments() {
    using ExpectedSignature = FunctionTraits<ExpectedFunc>;
    using ActualSignature = FunctionTraits<ActualFunc>;

    using ExpectedArgs = typename ExpectedSignature::Arguments;
    using ActualArgs = typename ActualSignature::Arguments;

    if constexpr (ExpectedSignature::kArgumentCount == ActualSignature::kArgumentCount) {
        return MatchArguments(ExpectedArgs(), ActualArgs());
    }
    return false;
}

template<typename ExpectedFunc, typename ActualFunc>
// 匹配两个可调用对象的参数
// 也就是ActualFunc的每个参数是否都可以隐式转换为ExpectedFunc对应的参数
constexpr bool kIsArgumentsMatchableFunctions = MatchFunctionArguments<ExpectedFunc, ActualFunc>();

template<typename ExpectedFunc, typename ActualFunc>
// 匹配两个可调用对象的返回值
// 也就是ActualFunc的返回类型是否可以隐式转换为ExpectedFunc的返回类型
constexpr bool kIsReturnTypeMatchableFunctions = std::is_convertible_v<typename FunctionTraits<ExpectedFunc>::Return,
    typename FunctionTraits<ActualFunc>::Return>;

template<typename ExpectedFunc, typename ActualFunc>
// 匹配两个可调用对象
constexpr bool kIsMatchableFunctions = kIsArgumentsMatchableFunctions<ExpectedFunc, ActualFunc>&&
    kIsReturnTypeMatchableFunctions< ExpectedFunc, ActualFunc>;
}
}
