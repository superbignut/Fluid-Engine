// MatrixMXN use Array2<T> as its element type, while Array2<T> is a wrapper of std::vector.
// So, the size of MatrixMXN can always be changed, which is same as VectorN, whose containertype is also std::vector.
// On the contrary, Matrix<T, M, N>'s containertype is std::array.