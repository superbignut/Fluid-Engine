## Fluid Engine Dev - big
---
![Static Badge](https://img.shields.io/badge/language-c%2B%2B-green)
![Static Badge](https://img.shields.io/badge/license-N%2FA-red)


### By 👀reading the 😱excellent 📖book "💦Fluid 🤖Engine 💻Development" and learning its 🥰concise 😍code 🤩structure💩,  the "🤪big" 🚀engine is ⏳being 🤠developed 🥱completely 🧐from 🥶scratch.🤓
---
![sphere](https://github.com/superbignut/Fluid-Engine/blob/master/render/render.jpg)
---
## Features:
+ ### CRTP 
    The results of most operations related to Matrices and Vectors are defined as a new agent type.All these types use [CRTP][1] and derive fron Matrix_Expression or Vector_Expression.

        // CRTP base
        template <typename T, typename E>
        class MatrixExpression
        {
            ...
            const E &operator()() const{
                return static_cast<const E &>(*this);
            }
        };
        
        template <...>
        class Matrix final : public MatrixExpression<T, Matrix<...>>

    By using CRTP, we can simplify calculation and storage until a specific value is needed.

        template <...>
        class MatrixBinaryOp : public MatrixExpression<T, MatrixBinaryOp<...>>
        {
            ...
            T operator()(std::size_t i, std::size_t j) const{
                return _op(_u(i, j), _v(i, j));} //  <-- calculate
            ...
            const E1 &_u; 
            const E2 &_v;
            Op _op;
        };
+ ### CSR
    The compressed sparse row ([CSR][2]) represents a matrix M by three (one-dimensional) arrays, that respectively contain nonzero values, the extents of rows, and column indices. 

        template <typename T>
        class MatrixCsr final : public MatrixExpression<T, MatrixCsr<T>>
        {
            ...
            NonZeroContainterType _nonZeros;
            IndexContainterType _colIndex;
            IndexContainterType _rowPtr;
        }
## To Do:

### 7. write someting here...
+ xxx
+ xxx
+ xxx
---
### 6. Complete the matrix.h and its corresponding include files.
+ ~~matrix.h, matrix_expression.h and fix a bug in matrix inverse().~~
+ ~~matrix2x2.h, matrix3x3.h~~
+ ~~matrix4x4.h and matrix_mxn.h are excluded temporarily for their cubersome and repeated codes.~~
+ matrix_csr.h, matrix_csr-inl.h and parrall.h
---
### ~~5. Complete the vector2.h, vector3.h and vector4.h.~~
+ ~~vector2.h, vector3.h, vector4.h~~
+ ~~Jet::VectorN has a dynamic size. We don't add it now.~~
### ~~4. Complete the vector.h and its corresponding include files.~~
+ ~~vector_expression.h and vector_expression-inl.h~~
+ ~~type_helpers.h~~
+ ~~vector.h and vector-inl.h~~
---
### ~~3. Complete the array3.h and its corresponding include files.~~
+ ~~point3.h and point3-inl.h~~
+ ~~size3.h and size3-inl.h~~
+ ~~array_accessor3.h and array_accerssor3-inl.h~~
---
### ~~2. Complete the  array2.h and its corresponding include files.~~
+ ~~point2.h and point2-inl.h~~
+ ~~size2.h and size2-inl.h~~
+ ~~array_accessor2.h and array_accerssor2-inl.h~~
---
### ~~1. Complete the  array1.h and its corresponding include files.~~
+ ~~point.h~~
+ ~~size.h~~ 
+ ~~array_accessor.h~~
---
### ~~0. Do some preparations about git , cmake and vscode's xxx.json .~~
+ ~~.git~~
+ ~~CMakeLists.txt~~
+ ~~README.md~~
---
## Reference :
---
### [https://github.com/doyubkim/fluid-engine-dev](https://github.com/doyubkim/fluid-engine-dev)
---
<!-- 知我者谓我心忧，不知者谓我何求 -->
[1]: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
[2]: https://en.wikipedia.org/wiki/Sparse_matrix
