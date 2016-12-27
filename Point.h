
#ifndef ASS1_POINT_H
#define ASS1_POINT_H


#include <ostream>
/**
 * a point with x and y axis.
 */
class Point {
private:
    int x;
    int y;

public:
/**
 * @param x_p - x axis.
 * @param y_p - y  axis.
 * @return set the axis of the point.
 */
    Point(int x, int y);
    /**
     *
     * @return
     */
    Point();
    /**
 *
 * @return the x axis.
 */
    int GetX() const;
/**
 *
 * @return the y axis.
 */
    int GetY() const;
/**
*
* @param x - new x.
*/
    void SetX(int x);
/**
 *
 * @param y - new y.
 */
    void SetY(int y);
    /**
 *
 * @param p1 - point which will be comapred.
 * @return true if the points are equals, otherwise false.
 */
    bool operator==(const Point &p1) const;
/**
 *
 * @param p1 - point which will be comapred.
 * @return fase if the points are equals, otherwise true.
 */
    bool operator!=(const Point &p1) const;
/**
 *
 * @param os - the output stream.
 * @param point - that will be printed.
 * @return string which represents the point.
 */
    friend std::ostream &operator<<(std::ostream &os, const Point &point);
    /**
     *
     * @param input
     * @param point
     * @return the input point
     */
    friend std::istream &operator>>(std::istream &input, Point &point);
};


#endif //ASS1_POINT_H
