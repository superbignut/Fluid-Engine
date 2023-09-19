#ifndef INCLUDE_BIG_VECTOR_EXPRESSION_H_
#define INCLUDE_BIG_VECTOR_EXPRESSION_H_
#include <stddef.h>
#include <functors.h>
namespace big
{
    ////////////////////////////////////////////
    //// Curiously Recurring Template Pattern///
    ////////////////////////////////////////////
    //！
    //! \brief base class for vector expression.
    //! \param T Real number type.
    //! \param E Subclass type.
    template <typename T, typename E>
    class VectorExpression
    {
    public:
        std::size_t size();
        const E &operator()() const;
    };

    //! \brief expression for unary operations.
    //! \param T Real number type.
    //! \param E Input expression type.
    //! \param Op Unary operation.
    template <typename T, typename E, typename Op>
    class VectorUnaryOp : public VectorExpression<T, VectorUnaryOp<T, E, Op>>
    {
    public:
        VectorUnaryOp(const E &other);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E &_u;
        Op _op;
    };

    //! \brief Matrix expression for type casting.
    template <typename T, typename E, typename U>
    using VectorTypeCast = VectorUnaryOp<T, E, TypeCast<T, U>>;

    //! \brief Vector expression for binary operations.
    //! \param T Real number type.
    //! \param E1 First input expression type.
    //! \param E2 Second input expression type.
    //! \param Op Binary operation.
    //! 有两个类型的容器，分别是E1和E2，他们中间的元素类型是T，现在想要对他们进行运算。
    //! E1 E2 也都要是VectorExpression的子类
    template <typename T, typename E1, typename E2, typename Op>
    class VectorBinaryOp : public VectorExpression<T, VectorBinaryOp<T, E1, E2, Op>>
    {
    public:
        VectorBinaryOp(const E1 &u, const E2 &v);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E1 &_u;
        const E2 &_v;
        Op _op;
    };

    //! \brief vector expression for matrix -scalar binary operations.
    //! \param T Real number type.
    //! \param E Input expression type.
    //! \param Op Binary operation.
    template <typename T, typename E, typename Op>
    class VectorScalarBinaryOp : public VectorExpression<T, VectorScalarBinaryOp<T, E, Op>>
    {
    public:
        VectorScalarBinaryOp(const E &u, const T &v);

        std::size_t size() const;

        T operator[](std::size_t i) const;

    private:
        const E &_u;
        T _v;
        Op _op;
    };
    //! 
    /*
    只要一个类型XXX是VectorExpression的子类， 那么下面的这些定义都可以直接被使用：
    比如在XXX类中的函数定义：

        VectorScalarAdd<T, XXX> add(constT& s)const
        {
            当我们调用这个函数时,直接返回一个构造函数：
            return VectorScalarAdd<T, XXX>(*this, s);
            这个构造函数的格式与   
                VectorScalarBinaryOp(const E &u, const T &v) : _u(u), _v(v), _op(){};   
            相对应；
            而这个构造函数的函数体是空的，只进行了初始化列表，在这里这个所谓的add操作并没有进行：
            而是在我们要取出具体的元素的时候进行的：
            比如一个：
                VectorScalarAdd<T, XXX> aaa = add(……)
            当我们想要取出 aaa[i]的时候，则会发现，[]()的函数为
                return _op(_u[i], _v);
            因此也就是在这里，这个加法被作用了上其。
        }
        
    
    因此一句话就是，下面这几个using的类，我主要想使用他们的构造函数，返回一个新的op u v都定义好的类VectorScalarBinaryOp
    进而在取出这个新类的原属时 ，使用[]的时候，才是运算真正发生的时候。
    
    */
    template <typename T, typename E1, typename E2>
    using VectorAdd = VectorBinaryOp<T, E1, E2, std::plus<T>>;

    template <typename T, typename E>
    using VectorScalarAdd = VectorScalarBinaryOp<T, E, std::plus<T>>;

    template <typename T, typename E1, typename E2>
    using VectorSub = VectorBinaryOp<T, E1, E2, std::minus<T>>;

    template <typename T, typename E>
    using VectorScalarSub = VectorScalarBinaryOp<T, E, std::minus<T>>;

    template <typename T, typename E>
    using VectorScalarRSub = VectorScalarBinaryOp<T, E, RMinus<T>>;

    template <typename T, typename E1, typename E2>
    using VectorMul = VectorBinaryOp<T, E1, E2, std::multiplies<T>>;

    template <typename T, typename E>
    using VectorScalarMul = VectorScalarBinaryOp<T, E, std::multiplies<T>>;

    template <typename T, typename E1, typename E2>
    using VectorDiv = VectorBinaryOp<T, E1, E2, std::divides<T>>;

    template <typename T, typename E>
    using VectorScalarDiv = VectorScalarBinaryOp<T, E, std::divides<T>>;

    template <typename T, typename E>
    using VectorScalarRDiv = VectorScalarBinaryOp<T, E, RDivides<T>>;

// in order to use static Polymorphism,  all the params use VectorExpression<>. 
/*

还是以 VectorAdd<T, E1, E2> operator+ 为例：
任何两个 VectorExpression 的子类的参数相加时, 比如：
xxx + yyy
调用operator+()    只有一行函数体 ： return VectorAdd(a(), b());//operator()
其中a()b()又调用了 函数调用运算符operator()() 并且进入的是VectorExpression 的函数调用运算符：
也只有一行  ：  return static_cast<const E &>(*this);
将基类this转为了子类this
这时候 两个子类的对象才会输入给VectorAdd 的构造函数：
   VectorAdd(const E &u, const T &v) : _u(u), _v(v), _op(std::plus<T>) {}
所以这些才是静态多态的精华：
函数的参数类型 本来 是父类的引用：

子类调用这个函数后，先变为父类，再强制转换为子类，


因此一句话就是，这些函数的参数都是父类的引用，我们就是从这里突破进取，再加上一个强制转换，从而实现了 静态多态。
总结 ： 子类通过一个父类的接口进去变成了父类的对象，再通过强制转换为子类，从而使用子类的一些性质。
*/
    template <typename T, typename E1, typename E2>
    VectorAdd<T, E1, E2> operator+(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarAdd<T, E> operator+(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorSub<T, E1, E2> operator-(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarSub<T, E> operator-(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarRSub<T, E> operator-(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorMul<T, E1, E2> operator*(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarMul<T, E> operator*(const T &a, const VectorExpression<T, E> &b);

    template <typename T, typename E1, typename E2>
    VectorDiv<T, E1, E2> operator/(const VectorExpression<T, E1> &a, const VectorExpression<T, E2> &b);

    template <typename T, typename E>
    VectorScalarDiv<T, E> operator/(const VectorExpression<T, E> &a, const T &b);

    template <typename T, typename E>
    VectorScalarRDiv<T, E> operator/(const T &a, const VectorExpression<T, E> &b);

} // namespace big
#include <detail/vector_expression-inl.h>
#endif