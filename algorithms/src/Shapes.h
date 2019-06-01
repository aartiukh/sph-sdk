/**
 * @file Shapes.h
 * @author Anton Artiukh (artyukhanton@gmail.com)
 * @date Created June 01, 2019
 **/

#ifndef SHAPES_H_19D5A367806A431C96F39D5F50B94D31
#define SHAPES_H_19D5A367806A431C96F39D5F50B94D31

namespace SPHAlgorithms
{

class Shapes
{
public:
    static float Pawn(float x, float y, float z)
    {
        using namespace SPHAlgorithms;

        const auto dis = ROperations::disjunction<float>;
        const auto con = ROperations::conjunction<float>;

        const float x_sqr = (x - 1.5f) * (x - 1.5f);
        const float y_sqr = (y - 1.5f) * (y - 1.5f);
        const float z1_sqr = (z - 0.75f) * (z - 0.75f);
        const float z2_sqr = (1.f - z) * (1.f - z);
        const float z3_sqr = (1.25f - z) * (1.25f - z);

        return dis(con(con(0.25f - x_sqr - y_sqr, -20.f * (x_sqr + y_sqr) + 1.f + 10.f * z1_sqr), z * (1.f - z)),
                   dis(0.125f - x_sqr - y_sqr - 20.f * z2_sqr, 0.05f - x_sqr - y_sqr - z3_sqr));
    }

    static float Bishop(float x, float y, float z)
    {
        using namespace SPHAlgorithms;

        const auto dis = ROperations::disjunction<float>;
        const auto con = ROperations::conjunction<float>;

        const float x_sqr = (x - 1.5f) * (x - 1.5f);
        const float y_sqr = (y - 1.5f) * (y - 1.5f);
        const float z1_sqr = (z - 0.85f) * (z - 0.85f);
        const float z2_sqr = (1.25f - z) * (1.25f - z);
        const float z3_sqr = (1.4f - z) * (1.4f - z);

        return dis(con(con(0.25f - x_sqr - y_sqr, -20.f * (x_sqr + y_sqr) + 1.f + 10.f * z1_sqr), z * (1.25f - z)),
                   dis(0.2f - x_sqr - y_sqr - 20.f * z2_sqr, 0.2f - 5.f * x_sqr - 4.f * y_sqr - z3_sqr));
    }
};

} // namespace SPHAlgorithms

#endif // SHAPES_H_19D5A367806A431C96F39D5F50B94D31
