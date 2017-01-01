#ifndef ASS1_POINT_H
#define ASS1_POINT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/list.hpp>

//#include <ostream>
using namespace boost::archive;
using namespace std;



//#include "includes.h"
/**
 * a point with x and y axis.
 */
class Point {
private:
    int x;
    int y;

    friend class boost::serialization::access;

public:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }

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
