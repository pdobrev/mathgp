//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

class nrvo_test
{
public:
    static size_t copies;

    nrvo_test(int d) 
        : dummy(d)
    {}

    nrvo_test(const nrvo_test& b)
        : dummy(b.dummy)
    {
        ++copies;
    }

    int dummy;

    static nrvo_test seven()
    {
        return nrvo_test(7);
    }
};

size_t nrvo_test::copies;

void nrvo()
{
    nrvo_test t = nrvo_test::seven();
    
    BOOST_WARN_EQUAL(nrvo_test::copies, 0);
}

test_suite* prerequisites()
{
    unit_test_log.set_threshold_level(log_test_units);

    test_suite* suite = BOOST_TEST_SUITE( "prerequisites" );

    suite->add(BOOST_TEST_CASE(nrvo));

    return suite;
}