/**
 * @file Shapes.h
 * @author Anton Artiukh (artyukhanton@gmail.com)
 * @date Created June 01, 2019
 **/

#ifndef SHAPES_H_19D5A367806A431C96F39D5F50B94D31
#define SHAPES_H_19D5A367806A431C96F39D5F50B94D31

#include "ROperations.h"

namespace SPHSDK
{

/**
 * @brief The Shapes class contanis various shapes equations constructed using the R-functions method.
 */
class Shapes
{
private:
    static constexpr auto dis = ROperations::disjunction<FLOAT>;
    static constexpr auto con = ROperations::conjunction<FLOAT>;

public:
    /**
     * @brief Represents a pawn in 3D.
     * @param x    The x-coordinate.
     * @param y    The y-coordinate.
     * @param z    The z-coordinate.
     * @return a value that > 0 inside the object, = 0 on the border and < 0 outside.
     */
    static FLOAT Pawn(FLOAT x, FLOAT y, FLOAT z)
    {
        const FLOAT x_sqr = (x - 1.5f) * (x - 1.5f);
        const FLOAT y_sqr = (y - 1.5f) * (y - 1.5f);
        const FLOAT z1_sqr = (z - 0.75f) * (z - 0.75f);
        const FLOAT z2_sqr = (1.f - z) * (1.f - z);
        const FLOAT z3_sqr = (1.25f - z) * (1.25f - z);

        return dis(con(con(0.25f - x_sqr - y_sqr, -20.f * (x_sqr + y_sqr) + 1.f + 10.f * z1_sqr), z * (1.f - z)),
                   dis(0.125f - x_sqr - y_sqr - 20.f * z2_sqr, 0.05f - x_sqr - y_sqr - z3_sqr));
    }

    /**
     * @brief Represents a bishop in 3D.
     * @param x    The x-coordinate.
     * @param y    The y-coordinate.
     * @param z    The z-coordinate.
     * @return a value that > 0 inside the object, = 0 on the border and < 0 outside.
     */
    static FLOAT Bishop(FLOAT x, FLOAT y, FLOAT z)
    {
        const FLOAT x_sqr = (x - 1.5f) * (x - 1.5f);
        const FLOAT y_sqr = (y - 1.5f) * (y - 1.5f);
        const FLOAT z1_sqr = (z - 0.85f) * (z - 0.85f);
        const FLOAT z2_sqr = (1.25f - z) * (1.25f - z);
        const FLOAT z3_sqr = (1.4f - z) * (1.4f - z);

        return dis(con(con(0.25f - x_sqr - y_sqr, -20.f * (x_sqr + y_sqr) + 1.f + 10.f * z1_sqr), z * (1.25f - z)),
                   dis(0.2f - x_sqr - y_sqr - 20.f * z2_sqr, 0.2f - 5.f * x_sqr - 4.f * y_sqr - z3_sqr));
    }
};

} // namespace SPHSDK

#endif // SHAPES_H_19D5A367806A431C96F39D5F50B94D31
