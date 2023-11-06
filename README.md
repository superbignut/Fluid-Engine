## Fluid Engine Dev - big
---
![Static Badge](https://img.shields.io/badge/language-c%2B%2B-green)
![Static Badge](https://img.shields.io/badge/license-N%2FA-red)
![Static Badge](https://img.shields.io/badge/render-Mitsuba-blue)
![Static Badge](https://img.shields.io/badge/Windows-False-purple)
![Static Badge](https://img.shields.io/badge/Ubuntu-True-brown)

<!-- ### By 👀reading the 😱excellent 📖book "💦Fluid 🤖Engine 💻Development" and learning its 🥰concise 😍code 🤩structure💩,  the "🤪big" 🚀engine is ⏳being 🤠developed 🥱completely 🧐from 🥶scratch.🤓 -->
#### "Fluid Engine Development" is actually a compensation for your exam-oriented education. 
#### By reading the code, you will realize that writing a pyhsics or math formula on paper fluently is still far from truly understanding it, but rather becoming familiar with its appearance. 
#### Everyone who loves physics can't afford to miss this wonderful book. If only I had come across this book earlier.
---
<!-- <div align="center">
	<img src="render/render.jpg" alt="Editor" width="700">
</div> -->
![render](https://github.com/superbignut/Fluid-Engine/blob/master/render/render.jpg)
---
📦 [Contents:](#Contents-)
+ 📌 [Curiously Recurring Template Pattern](#CRTP)
+ 📌 [Compressed Sparse Row](#CSR)
+ 📌 [ASYNC](#ASYNC)
+ 📌 [Conjugate Gradient Method](#CG)
+ 📌 [Ray Axis-Aligned Bounding Box Intersection](#Ray-AABB-Intersection)
+ 📌 [Quaternion and 3-D Rotation Matrix](#Quaternion-and-3-D-Rotation-Matrix)
+ 📌 [Builder Pattern](#Builder-Pattern)

🗓 [To Do:](#ToDO-)

📎 [Reference:](#Reference-)

---
## Contents :
+ ### CRTP
    The results of most operations related to Matrices and Vectors are defined as a new agent type.All these types are [CRTP][1] and derive from Matrix_Expression or Vector_Expression.

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

    By using CRTP, we can delay the calculation until a specific result is needed. The new storage space is also not required.

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
+ ### ASYNC
    A simplified version of [std::async][3] is wrappered by using std::thread and std::future. Later ,the use of 'new' and 'delete' will be changed to morden c++ syntax.
        
        template <typename TASK_T>
        inline void schedule(TASK_T &&fcn)
        {
            std::thread thread(std::forward<TASK_T>(fcn));
            thread.detach(); 
        }
        template <typename TASK_T>
        using operator_return_t = typename std::invoke_result<TASK_T>::type;

        template <typename TASK_T>
        inline auto async(TASK_T &&fcn) -> std::future<operator_return_t<TASK_T>>
        {
            using package_t = std::packaged_task<operator_return_t<TASK_T>()>;
            auto task = new package_t(std::forward<TASK_T>(fcn));
            auto future = task->get_future();
            schedule([task=task]() { // <-- Todo
                (*task)(); 
                delete task;});
            return future;
        }
+ ### CG
    Our interest in the conjugate gradient method is twofold. It is one of the most useful tecnniques for solving large linear systems  of equations, and it can also be adapted to solve nolinear optimization problems[^1].

        BlasType::residual(A, *x, b, r);                           //r = A * x - b
        
        *p = -*r;                                                  //p = -r
        
        typename BlasType::ScalarType rr = BlasType::dot(*r, *r);  //rr = r * r
        
        unsigned int k = 0;
        while (rr > tolerance && k <= maxNumberOfIterations)
        {
            BlasType::mvm(A, *p, q);                               //q = A * p

            typename BlasType::ScalarType alpha = rr / BlasType::dot(*p, *q);

            BlasType::axpy(alpha, *p, *x, x);                      //x = x + alpha * p

            BlasType::axpy(alpha, *q, *r, r);                      //r = r + alpha * q 

            typename BlasType::ScalarType old_rr = rr;

            rr = BlasType::dot(*r, *r);

            typename BlasType::ScalarType beta = rr / old_rr;      //beta = rr / rr

            BlasType::axpy(beta, *p, -*r, p);                      //p = beta * p - r

            ++k;
        }
+ ### Ray-AABB-Intersection
    Kay and Kayjia developed a method based on "slabs" where a slab is the space between two parallel plane[^2]. It is a simple method to ascertain whether a ray intersects with an axis-aligned bounding box(AABB).
    
    Generally, when a line intersects with an AABB, the ray's origin can be categorized into 5 distinct scenarios, as illustrated below:

    ![Raybox](https://github.com/superbignut/Fluid-Engine/blob/master/render/raybox.jpg)
    
    We use : $\vec{r}_0 + t \cdot \vec{r}_d$ to represent a parametric line and $t_i$ to represent the intersection of line and boundary，and we can find that:
    
    1. $$\qquad 0 < t_1 < t_3 < t_2 < t_4 < \infty$$
    2. $$\qquad t_1 < 0 < t_3 < t_2 < t_4 < \infty$$
    3. $$\qquad t_1 < t_3 < 0 < t_2 < t_4 < \infty$$
    4. $$\qquad t_1 < t_3 < t_2 < 0 < t_4 < \infty$$  
    5. $$\qquad t_1 < t_3 < t_2 < t_4 < 0 < \infty$$ 

    We only need to consider the first two cases. The third case is assessed as 'contained within the bounding box', and the last two cases are deemed as non-intersecting. Naturally We can draw a conclusion that: $$Intersect : max(t_1, t_3, 0) < min(t_2, t_4 ,\infty)$$ 

    Alought there are some edge cases need to be considered.

    If we raise the dimension to three-dimensional space, the positional relationship between straight line and cube will become unimaginable.  However, just remember that, the straight line will pass through three planes first, and then the remaining three planes.(As before, we just consider the cases that the straight line does not parallel to any plane.)

    Therefore, the only difference between 2-D and 3-D is that we have 4 parameters $(t_1,t_2,t_3,t_4)$ in 2-D space while 6 paramters $(t_1,t_2,t_3,t_4,t_5,t_6)$ in 3-D space.
+ ### Quaternion and 3-D Rotation Matrix
    In $R^3$, a proper rotation by angle $\theta$ around the axis $\vec{u}$ can be written concisely as :[^3]
    $$\vec{v'} = cos\theta \cdot\vec{v} + (1-cos\theta)(\vec{u}\cdot\vec{v})\vec{u}+sin\theta\cdot(\vec{u}\times\vec{v})$$

    The representations of rotations by quaternions are more compact than the representations by matrices. In addition, unlike Euler angles, they are not susceptible to "gimbal lock".[^4]
    $$v'  = q v q^* = qvq^{-1} \qquad v=（0, \vec{v}） \qquad q=(cos( \frac{1}{2} \theta),sin( \frac{1}{2} \theta) \vec{u})$$

    If you are new to quaternion, this [Quaternion Introduction](https://github.com/Krasjet/quaternion) is all you needed. 


+ ### Builder Pattern
    The builder pattern is a design pattern designed to provide a flexible solution to various object creation problems in object-oriented programming. The intent of the builder design pattern is to separate the construction of a complex object from its representation. [^5]

    Furthermore, it's possible to integrate the Builder Pattern with the Curiously Recurring Template Pattern (CRTP). At first glance，the implementation may appear somewhat complex and puzzeling. However, once finished, it becomes exceedingly straightforward to use.

        template <typename DrivedBuilder>
        class SurfaceBuilderBase3
        {
        public:
            DrivedBuilder &withIsNormalFlipped(...);

            DrivedBuilder &withTranslation(...);

            DrivedBuilder &withOrientation(...);

            DrivedBuilder &withTransform(...);
        protected:
            bool _isNormalFlipped;
            Transform3 _transform;
        };

        class Sphere3::Builder final : public SurfaceBuilderBase3<Sphere3::Builder>
        {
        public:
            Builder &withCenter(...);

            Builder &withRadius(...);

            Sphere3 build() const;

            Sphere3Ptr makeShared() const;
        private:
            Vector<double, 3> _center; 
            double _radius;
        };

## ToDo :

<!-- #### 8. write someting here... -->
#### 10. Complete the animation and physics_animation.
---
#### ~~9. Complete the surface of sphere and plane ,while box and cylinder are not done.~~
---
#### ~~8. Complete the surface.h and its corresponding files.~~

---
#### ~~7. Complete the Field, scalar_field, vector_field and conjugate gradient parts.~~

---
#### ~~6. Complete the matrix.h and its corresponding files.~~
<!-- + ~~matrix.h, matrix_expression.h and fix a bug in matrix inverse().~~
+ ~~matrix2x2.h, matrix3x3.h~~
+ ~~matrix4x4.h and matrix_mxn.h are excluded temporarily for their cubersome and repeated codes.~~
+ ~~matrix_csr.h, matrix_csr-inl.h and parrall.h~~ -->
---
#### ~~5. Complete the vector2.h, vector3.h and vector4.h.~~
<!-- + ~~vector2.h, vector3.h, vector4.h~~
+ ~~Jet::VectorN has a dynamic size. We don't add it now.~~ -->
---
#### ~~4. Complete the vector.h and its corresponding files.~~
<!-- + ~~vector_expression.h and vector_expression-inl.h~~
+ ~~type_helpers.h~~
+ ~~vector.h and vector-inl.h~~ -->
---
#### ~~3. Complete the array3.h and its corresponding files.~~
<!-- + ~~point3.h and point3-inl.h~~
+ ~~size3.h and size3-inl.h~~
+ ~~array_accessor3.h and array_accerssor3-inl.h~~ -->
---
#### ~~2. Complete the  array2.h and its corresponding files.~~
<!-- + ~~point2.h and point2-inl.h~~
+ ~~size2.h and size2-inl.h~~
+ ~~array_accessor2.h and array_accerssor2-inl.h~~ -->
---
#### ~~1. Complete the  array1.h and its corresponding files.~~
<!-- + ~~point.h~~
+ ~~size.h~~ 
+ ~~array_accessor.h~~ -->
---
#### ~~0. Do some preparations about git , cmake and vscode's xxx.json .~~
<!-- + ~~.git~~
+ ~~CMakeLists.txt~~
+ ~~README.md~~ -->
---
## Reference :
---
<!-- github-reference -->
### [https://github.com/doyubkim/fluid-engine-dev](https://github.com/doyubkim/fluid-engine-dev)
### [https://github.com/mitsuba-renderer/mitsuba3](https://github.com/mitsuba-renderer/mitsuba3)
### [https://github.com/Krasjet/quaternion](https://github.com/Krasjet/quaternion)
---
<!-- keyword-link -->
[1]: https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
[2]: https://en.wikipedia.org/wiki/Sparse_matrix
[3]: https://en.cppreference.com/w/cpp/thread/async
[4]: https://github.com/Krasjet/quaternion
<!-- paragraph-footnote -->
[^1]: https://www.math.uci.edu/~qnie/Publications/NumericalOptimization.pdf
[^2]: https://education.siggraph.org/static/HyperGraph/raytrace/rtinter3.htm
[^3]: https://en.wikipedia.org/wiki/Rotation_matrix
[^4]: https://en.wikipedia.org/wiki/Quaternion
[^5]: https://en.wikipedia.org/wiki/Builder_pattern

<!-- 知我者谓我心忧，不知者谓我何求 -->