/**
* @file ROperations.h
* @author Anton Artiukh (artyukhanton@gmail.com)
* @date Created May 05, 2019
**/

#ifndef R_OPERATIONS_H_43C34465A6ED4DB9B9F2F4C3937BF5DD
#define R_OPERATIONS_H_43C34465A6ED4DB9B9F2F4C3937BF5DD


namespace SPHAlgorithms
{

/**
* @brief ROperations class defines R-operations.
*/
class ROperations
{
public:

    /**
     * @brief Returns conjunction of x and y
     * @param x    The x Cartesian coordinate
     * @param y    The y Cartesian coordinate
     * @return the result of conjuction R-operation in R0 system
     */
    static double conjunction(double x, double y);

    /**
     * @brief Returns disjunction of x and y
     * @param x    The x Cartesian coordinate
     * @param y    The y Cartesian coordinate
     * @return the result of disjunction R-operation in R0 system
     */
    static double disjunction(double x, double y);
};


} //SPHAlgorithms

#endif // R_OPERATIONS_H_43C34465A6ED4DB9B9F2F4C3937BF5DD
