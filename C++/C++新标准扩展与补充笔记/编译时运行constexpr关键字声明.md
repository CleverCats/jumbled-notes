C++11��һЩ�����ĸ��ƣ����ָ��Ʊ�֤д���Ĵ���������κ�ʱ���ִ��Ч�ʶ�Ҫ�á����ָ���֮һ�������ɳ������ʽ������������ñ���ʱ�ļ�����������������Ϥģ��Ԫ��̣��㽫����constexprʹ��һ�б�ø��Ӽ򵥡������㲻֪��ģ��Ԫ��̣�Ҳûʲô��constexprʹ���Ǻ����������ϱ���ʱ��̵����ơ�

�������ʽ��Ҫ������һЩ���㷢���ڱ���ʱ���������ڴ��������������е�ʱ�����Ǻܴ���Ż���������Щ��������ڱ���ʱ��������ֻ��һ�Σ�������ÿ�γ�������ʱ����Ҫ����һ������ʱ��֪�ĳ����������ض�ֵ��sine��cosin��ȷʵ�������ʹ�ÿ⺯��sin��cos������������뻨������ʱ�Ŀ�����ʹ��constexpr������Դ���һ������ʱ�ĺ���������Ϊ����������Ҫ����ֵ���û��ĵ��Խ�����Ҫ����Щ������


/*�����㽫һ����Ա�������Ϊconstexpr����˳��Ҳ�������Ϊ��const������㽫һ���������Ϊconstexpr����ͬ������const�ġ����෴����������һ��const�ı���������������constexpr�ġ�*/



constexpr��̽
Ϊ��ʹ������ȡ����ʱ����������������ָ��constexpr�ؼ��ֵ����������

constexpr int multiply (int x, int y)
{
    return x * y;
}

// ���ڱ���ʱ����
const int val = multiply( 10, 10 );
���˱���ʱ����������Ż���constexpr������һ�������ǣ�����������Ӧ������ǰ���ú�����г��ϡ����磬����Ҫһ����������size�ĺ�����size��10�ı������������constexpr������Ҫ����һ�������ʹ��ģ�壬��Ϊ�㲻���ú����ķ���ֵȥ��������Ĵ�С��������constexpr����Ϳ��Ե���һ��constexpr����ȥ����һ�����顣

constexpr int getDefaultArraySize (int multiplier)
{
    return 10 * multiplier;
}

int my_array[ getDefaultArraySize( 3 ) ];
constexpr����������
һ��constexpr��һЩ������ѭ���ϸ�Ҫ��

������ֻ����һ��return��䣨�м���������
ֻ�ܵ�������constexpr����
ֻ��ʹ��ȫ��constexpr����
ע��ݹ鲢�������ơ���ֻ����һ��������䣬�����ʵ�ֵݹ��أ�����ʹ����Ԫ�������?:)�����磬����n�Ľ׳ˣ�

constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}
���������ʹ��factorial(2)�����������ڱ���ʱ�������ֵ�����ַ�ʽ���и�����ļ��㣬��������Ȼ��ͬ�����޷�����һ���ݹ麯����

constexpr����������Щ�ص㣿

һ��constexpr������ֻ�������һ�п�ִ�д��롣���������typedefs�� using declaration && directives����̬���Եȡ�

constexpr������ʱ
һ������Ϊconstexpr�ĺ���ͬ������������ʱ�����ã�����������Ĳ����Ƿǳ����ģ�

int n;
cin >> n;
factorial( n );
����ζ���㲻��Ҫ�ֱ�д����ʱ�ͱ���ʱ�ĺ�����

����ʱʹ�ö���
��������һ��Circle�ࣺ

class Circle
{
    public:
    Circle (int x, int y, int radius) : _x( x ), _y( y ), _radius( radius ) {}
    double getArea () const
    {
        return _radius * _radius * 3.1415926;
    }
    private:
        int _x;
        int _y;
        int _radius;
};
��ϣ���ڱ����ڹ���һ��Circle����������������

constexpr Circle c( 0, 0, 10 );
constexpr double area = c.getArea();
��ʵ֤������Ը�Circle����һЩС���޸����������¡����ȣ�������Ҫ�����캯������Ϊconstexpr������������Ҫ��getarea��������Ϊconstexpr�������캯������Ϊconstexpr�����й��캯���ڱ��������У�ֻҪ������캯���Ĳ���Ϊ�������ҹ��캯������������Ա������constexpr���죨����Ĭ�Ϲ�����Կ���constexpr��ֻҪ��Ա��������constexpr���죩��

class Circle
{
    public:
    constexpr Circle (int x, int y, int radius) : _x( x ), _y( y ), _radius( radius ) {}
    constexpr double getArea ()
    {
        return _radius * _radius * 3.1415926;
    }
    private:
        int _x;
        int _y;
        int _radius;
};
constexpr vs const
�����㽫һ����Ա�������Ϊconstexpr����˳��Ҳ�������Ϊ��const������㽫һ���������Ϊconstexpr����ͬ������const�ġ����෴����������һ��const�ı���������������constexpr�ġ�

constexpr�͸�����
���������ǽ�����constexpr���ܶ�����ͨ��ģ��Ԫ���ʵ�֡���constexpr֧�ֵ�һ�������ǿ��Լ��㸡���͵����ݡ���Ϊdouble��float������Ч��ģ��������㲻�������׵�ͨ��ģ������ڼ��㸡������ֵ����constexpr��������ڼ��㸡�������ݡ�

Ȩ��constexpr
C++��������������޸�һ��ͷ�ļ����������±��뵼�±��뻺�������š���constexpr�����������ӱ���ʱ��ķ��գ���Ҳ��һЩ����ȥ�������ַ��ա����ȣ���Ϊconstexpr������ͬ�Ĳ����������ͬ�Ľ�����������ǿ��Ա�memoized����ʵ��GCC�Ѿ�֧��memoization��

��Ϊ���Զ�constexpr����memoize,������constexpr�����滻ģ�庯���ĵط���(���룩���ܲ����ø����������������������ʵ�ϣ��滻��һ����ģ��ʵ��������������ӿ졣

��󣬱�׼���������ȥ���Ƶݹ麯���ļ�������������������ȵݹ�ı���������ġ�