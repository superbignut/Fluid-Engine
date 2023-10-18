template <typename T>
class A
{
public:
    void size() const
    {
        //std::cout << "father\n";
        static_cast<const T &>(*this).size();   //it will call B's copy-constructor without the & in< >
        //std::cout << static_cast<const T &>(*this).con << "\n"; //B's member var is still 
    }
};

class B : public A<B>
{
public:
    void size() const
    {
        //std::cout << "son\n";
    }
    int con = 10;
};

template <typename U>
void inter(const A<U> &other)
{
    other.size();
}
int main(int argc, char **argv)
{
    B bbb;
    inter(bbb);

    return 0;
}