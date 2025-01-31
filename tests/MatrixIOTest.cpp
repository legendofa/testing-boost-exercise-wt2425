#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include <iostream>
#include <matrixIO.hpp>
#include <sstream>
#include <vector>

#define BOOST_TEST_DYN_LINK

struct MatrixIOFixture {
  MatrixIOFixture()
  {
    filePath        = "example_matrix.csv";
    dimension       = 4;
    referenceMatrix = Eigen::MatrixXd(4, 4);
    referenceMatrix << 1.8923, 8.2983, 8.1238, 7.2432,
        -2.3239, 1.2923, -1.2390, 7.3413,
        1.2324, 1.2323, 6.2342, 7.2341,
        5.5464, 1.1233, 1.2312, 3.2123;
  }

  std::string     filePath;
  int             dimension;
  Eigen::MatrixXd referenceMatrix;
};

BOOST_FIXTURE_TEST_SUITE(MatrixIOTests, MatrixIOFixture, *boost::unit_test::tolerance(1e-4))

// Test saving data on opening a file.
BOOST_AUTO_TEST_CASE(SaveMatrixNameCheck)
{
  std::string outputFileName = "testmatrix.csv";
  matrixIO::saveData(outputFileName, referenceMatrix);
  std::ifstream outputFile(outputFileName);
  BOOST_TEST(outputFile.is_open());
}

// Test if the content of the saved matrix is the same as the reference matrix.
BOOST_AUTO_TEST_CASE(SaveMatrixContentCheck)
{
  std::string outputFileName = "testmatrix.csv";
  matrixIO::saveData(outputFileName, referenceMatrix);

  std::ifstream outputFile(outputFileName);
  BOOST_TEST(outputFile.is_open());

  Eigen::MatrixXd loadedMatrix(dimension, dimension);
  for (int i = 0; i < dimension; ++i) {
    for (int j = 0; j < dimension; ++j) {
      if (!(outputFile >> loadedMatrix(i, j))) {
        BOOST_FAIL("Error reading matrix element from file.");
      }
    }
  }
  BOOST_TEST(loadedMatrix.isApprox(referenceMatrix));
}

// Test if the loaded matrix is the same as the reference matrix.
BOOST_AUTO_TEST_CASE(LoadMatrixFromFile)
{
  Eigen::MatrixXd loadedMatrix;
  try {
    loadedMatrix = matrixIO::openData(filePath, dimension);
    BOOST_TEST(loadedMatrix.isApprox(referenceMatrix));
  } catch (const std::exception &e) {
    BOOST_FAIL("Exception caught: " << e.what());
  }
}

BOOST_AUTO_TEST_SUITE_END()
