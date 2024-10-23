
namespace miniwin {
template<class T>
T Or(T a, T b) {
    return static_cast<T>(static_cast<size_t>(a) | static_cast<size_t>(b));
}
template<class T>
T And(T a, T b) {
    return static_cast<T>(static_cast<size_t>(a) & static_cast<size_t>(b));
}
}