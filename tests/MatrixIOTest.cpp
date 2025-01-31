#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "matrixIO.hpp"

#define BOOST_TEST_DYN_LINK
using namespace Eigen;

struct MatrixIOFixture {
  MatrixIOFixture()
  {
    filePath        = "example_matrix.csv";
    dimension       = 4;
    referenceMatrix = MatrixXd(4, 4);
    referenceMatrix << 1.8923, 8.2983, 8.1238, 7.2432 - 2.3239, 1.2923, -1.2390, 7.3413 1.2324, 1.2323, 6.2342, 7.2341 5.5464, 1.1233, 1.2312, 3.2123;
  }

  std::string filePath;
  int         dimension;
  MatrixXd    referenceMatrix;
};

BOOST_FIXTURE_TEST_SUITE(MatrixIOTests, MatrixIOFixture, *boost::unit_test::tolerance(1e-4))

BOOST_AUTO_TEST_CASE(SaveMatrixName)
{
  std::string outputFileName = "testmatrix.csv";
  matrixIO::saveData(outputFileName, referenceMatrix);
  std::ifstream outputFile(outputFileName);
  BOOST_TEST(outputFile.is_open());
}

BOOST_AUTO_TEST_CASE(OpenMatrix)
{
  MatrixXd loadedMatrix = matrixIO::openData(filePath, dimension);
  BOOST_TEST(loadedMatrix.isApprox(referenceMatrix));
}

BOOST_AUTO_TEST_SUITE_END()
