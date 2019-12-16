#pragma once


#include <array>


namespace SPHAlgorithms {

    template<typename _T, size_t _Dim, typename = std::make_index_sequence<_Dim>>
    class Point;

    template<typename _T, size_t _Dim, std::size_t ... _Idx>
    class Point<_T, _Dim, std::index_sequence<_Idx ...>> : public std::array<_T, _Dim>
    {
        public:
            bool within(const Point<_T, _Dim> & _other, const _T & _range) const
            {
                _T accumulated = ( std::pow(_other[_Idx] - (*this)[_Idx], 2) + ... );
                if ( accumulated > _range * _range )
                    return false;
                return true;
            }

            bool operator ==(const Point<_T, _Dim,
                             std::index_sequence<_Idx ...>> & _other) const
            {
                bool res = (true & ... & ((*this)[_Idx] == _other[_Idx]) );
                return res;
            }
            _T norm() const
            {
                return ( std::pow( (*this)[_Idx], 2) + ... );
            }

            Point<_T, _Dim> operator-(const Point<_T, _Dim, std::index_sequence<_Idx ...>> & _other) const
            {
                Point<_T, _Dim> p/*{ { ( ((*this)[_Idx] - _other[_Idx]) , ... ) } }*/;
                ( (p[_Idx] = (*this)[_Idx] - _other[_Idx]) , ... );
                return p;
            }

            Point<_T, _Dim> operator-() const
            {
                Point<_T, _Dim> p/*{ { ( ((*this)[_Idx] - _other[_Idx]) , ... ) } }*/;
                ( (p[_Idx] = -(*this)[_Idx]) , ... );
                return p;
            }

            Point<_T, _Dim> & operator-=(_T _value)
            {
                ( ((*this)[_Idx] -= _value) , ... );
                return *this;
            }

            Point<_T, _Dim> operator+(const Point<_T, _Dim, std::index_sequence<_Idx ...>> & _other) const
            {
                Point<_T, _Dim> p/*{ { ( ((*this)[_Idx] + _other[_Idx]) , ... ) } }*/;
                ( (p[_Idx] = (*this)[_Idx] + _other[_Idx]) , ... );
                return p;
            }

            Point<_T, _Dim> & operator+=(const Point<_T, _Dim, std::index_sequence<_Idx ...>> & _other)
            {
                ( ((*this)[_Idx] += _other[_Idx]) , ... );
                return *this;
            }

            Point<_T, _Dim> operator*(_T _value) const
            {
                Point<_T, _Dim> p;
                ( (p[_Idx] = (*this)[_Idx] * _value) , ... );
                return p;
            }

            Point<_T, _Dim> & operator*=(_T _value)
            {
                ( ((*this)[_Idx] *= _value) , ... );
                return *this;
            }

            Point<_T, _Dim> operator/(_T _value) const
            {
                Point<_T, _Dim> p;
                ( (p[_Idx] = (*this)[_Idx] / _value) , ... );
                return p;
            }

            Point<_T, _Dim> & operator/=(_T _value)
            {
                ( ((*this)[_Idx] /= _value) , ... );
                return *this;
            }

            Point<_T, _Dim> operator/(const Point<_T, _Dim, std::index_sequence<_Idx ...>> & _other) const
            {
                Point<_T, _Dim> p;
                ( (p[_Idx] = (*this)[_Idx] / _other[_Idx]) , ... );
                return p;
            }

            Point<_T, _Dim> & operator/=(const Point<_T, _Dim, std::index_sequence<_Idx ...>> & _other)
            {
                ( ((*this)[_Idx] /= _other[_Idx]) , ... );
                return *this;
            }
    };

    using Point2D = Point<double, 2>;
    using Point2F = Point<float, 2>;
    using Point2I = Point<int, 2>;

    using Point3D = Point<double, 3>;
    using Point3F = Point<float, 3>;

}




