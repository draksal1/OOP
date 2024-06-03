#include "gtest/gtest.h"
#include"../Matrix/Matrix.hpp"

#include <iostream>
Matrix SquareDiagonal(size_t dim) {

    Matrix matrix{ dim, dim };

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            matrix.coeffRef(i, j) = i + j;
        }
    }

    return matrix;

}
Matrix Same_Size_Mat()
{
    Matrix result{ 3,3 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            result.coeffRef(i, j) = 2 * (double)(i + j);
            double a = result.coeffRef(i, j);
        }
    }
    return result;
}
Matrix Same_Size_Vect_f()
{
    Matrix result{ 3,1 };
    for (size_t i = 0; i < 3; i++)
    {
        result.coeffRef(i, 0) = i * 2.0;
    }
    return result;
}

Matrix Mat_x_x(size_t size)
{
    Matrix result{ size,size };
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            result.coeffRef(i, j) = (i == j ? 0.0 : 1.0);
        }
    }
    return result;
}

namespace
{
    const Matrix same_size_mat = Same_Size_Mat();
    const Matrix mat_4_4 = Mat_x_x(4);
    const Matrix mat_5_5 = Mat_x_x(5);
    const Matrix same_size_vect = Same_Size_Vect_f();
    const Matrix diff_size_mat{ 2,1 };
    const Matrix empty_mat{};
    const double value = 2.0;
    const double precision = 0.001;
}

class Square_Matrix : public ::testing::Test {
protected:
 

    virtual void TearDown(void) {
    }

    Matrix mat = NULL;
};


TEST(Square_Matrix, Constructor) {

    Matrix mat(3, 3);

    EXPECT_TRUE(mat.data());

    EXPECT_EQ(mat.cols(), 3);

    EXPECT_EQ(mat.rows(), 3);

    EXPECT_TRUE(mat.isValid());

}
TEST(Square_Matrix,coeffRef_x_x_FAIL) {
    Matrix mat(3, 3);
    mat = SquareDiagonal(3);
    
    EXPECT_THROW(mat.coeffRef(4, 0), std::out_of_range);
    EXPECT_THROW(mat.coeffRef(0, 4), std::out_of_range);
    EXPECT_THROW(mat.coeffRef(4, 4), std::out_of_range);

}


TEST(Square_Matrix,and_Emat_mult_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat * empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Square_Matrix,and_Emat_summ_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat + empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Square_Matrix,and_Emat_substr_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat - empty_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST(Square_Matrix,and_DSmat_mult_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat * diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Square_Matrix,and_DSmat_summ_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat + diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Square_Matrix,and_DSmat_substr_FAIL) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    Matrix result = mat - diff_size_mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}

TEST(Square_Matrix,assign_OK1) {
    Matrix mat;
    mat = Matrix(3, 3);
    mat = SquareDiagonal(3);
    {
        Matrix result = mat;
        auto m1 = result;
    }
}


TEST(Square_Matrix,and_SSvect_mult_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat * same_size_vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.coeffRef(0, 0), 10);
    EXPECT_EQ(result.coeffRef(1, 0), 16);
    EXPECT_EQ(result.coeffRef(2, 0), 22);
}
TEST(Square_Matrix,and_SSvect_summ_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat + same_size_vect;
    EXPECT_FALSE(result.isValid());
}
TEST(Square_Matrix,and_SSvect_substr_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat - same_size_vect;
    EXPECT_FALSE(result.isValid());
}


TEST(Square_Matrix,and_SSmat_mult_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat * same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 10,16,22,16,28,40,22,40,58 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}
TEST(Square_Matrix,and_SSmat_sum_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat + same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,3,6,3,6,9,6,9,12 };


    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}


TEST(Square_Matrix,and_IDmat_sum_and_assing_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix ID1 = Matrix::identity(3, 3);
    Matrix ID2 = Matrix::identity(3, 3);
    Matrix result = ID1 + ID2;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            EXPECT_DOUBLE_EQ((i == j ? 2.0 : 0.0), result.data()[i * result.cols() + j]);
            EXPECT_DOUBLE_EQ((i == j ? 2.0 : 0.0), result.coeffRef(i, j));
        }
    }
}



TEST(Square_Matrix,and_SSmat_substr_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat - same_size_mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,-1,-2,-1,-2,-3,-2,-3,-4 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST(Square_Matrix,and_double_mult_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat * value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}
TEST(Square_Matrix,and_double_div_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat / value;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,0.5,1,0.5,1,1.5,1,1.5,2 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}



TEST(Square_Matrix,assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), mat.coeffRef(i / 3, i % 3));
    }
}



TEST(Square_Matrix,and_Emat_mult_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat = empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST(Square_Matrix, and_Emat_summ_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat += empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}
TEST(Square_Matrix,and_Emat_substr_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat -= empty_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_FALSE(empty_mat.isValid());
}



TEST(Square_Matrix,and_DSmat_mult_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat *= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST(Square_Matrix,and_DSmat_summ_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat += diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}
TEST(Square_Matrix,and_DSmat_substr_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat -= diff_size_mat;
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(diff_size_mat.isValid());
}


TEST(Square_Matrix,and_SSvect_mult_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat *= same_size_vect;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.coeffRef(0, 0), 10);
    EXPECT_EQ(mat.coeffRef(1, 0), 16);
    EXPECT_EQ(mat.coeffRef(2, 0), 22);
}
TEST(Square_Matrix,and_SSvect_summ_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat += same_size_vect;
    EXPECT_FALSE(mat.isValid());
}
TEST(Square_Matrix, and_SSvect_substr_and_assign_FAIL) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat -= same_size_vect;
    EXPECT_FALSE(mat.isValid());
}


TEST(Square_Matrix,and_SSmat_mult_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat *= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 10,16,22,16,28,40,22,40,58 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}
TEST(Square_Matrix, and_SSmat_sum_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat += same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,3,6,3,6,9,6,9,12 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST(Square_Matrix,and_SSmat_substr_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat -= same_size_mat;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,-1,-2,-1,-2,-3,-2,-3,-4 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}


TEST(Square_Matrix, and_double_mult_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat *= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}
TEST(Square_Matrix, and_double_div_and_assign_OK) {
    Matrix mat;
    mat = SquareDiagonal(3);
    mat /= value;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    double values[9] = { 0,0.5,1,0.5,1,1.5,1,1.5,2 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(mat.coeffRef(i / 3, i % 3), values[i]);
    }
}





TEST(Square_Matrix, resize_0_0_FAIL)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(Square_Matrix, resize_1_0_FAIL)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(Square_Matrix, resize_1_1_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}


TEST(Square_Matrix, set_identity_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.setIdentity();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 2), 1);
}
TEST(Square_Matrix, set_zero_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.coeffRef(0, 0) = 3;
    mat.setZero();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 2), 0);
}
TEST(Square_Matrix, set_constants_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.setConstants(3.0);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 3);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 3.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 2), 3.0);
}

TEST(Square_Matrix, resize_and_set_constants_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.setConstants(3, 2, 2.0);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 2.0);
}
TEST(Square_Matrix, resize_and_set_identity_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.setIdentity(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST(Square_Matrix, resize_and_set_zero_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.setZero(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}



TEST(Square_Matrix, transpose_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.coeffRef(0, 1) = 8;
    mat.coeffRef(0, 2) = 16;
    Matrix result = mat.transpose();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 3);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 2), 4);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 8);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 16);
}

TEST(Square_Matrix, det_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.coeffRef(0, 2) = 3;
    double result = mat.det();
    EXPECT_NEAR(result, -1, precision);
}

TEST(Square_Matrix, det_4_4_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result{ 3,3 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            result.coeffRef(i, j) = (i == 0 ? 1 : (i == j ? 0 : 1));
        }
    }
    EXPECT_DOUBLE_EQ(result.det(), 1.0);
}
TEST(Square_Matrix, inverse_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    mat.coeffRef(0, 2) = 3;
    Matrix result = mat.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 1, -5, 3,-2,6,-3,1,-2,1 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 3, i % 3), values[i], precision);
    }
    result *= mat;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.data()[i * result.cols() + j], precision);
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}

TEST(Square_Matrix, inverse_4_4_OK)
{
    Matrix result = mat_4_4.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 4);
    EXPECT_EQ(result.cols(), 4);
    EXPECT_TRUE(result.isValid());
    double values[16];
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            values[i * 4 + j] = (i == j ? (double)-0.6667 : 0.3333);
        }
    }
    for (size_t i = 0; i < 16; i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 4, i % 4), values[i], precision);
    }
    result *= mat_4_4;
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}
TEST(Square_Matrix, inverse_5_5_OK)
{
    Matrix result = mat_5_5.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 5);
    EXPECT_EQ(result.cols(), 5);
    EXPECT_TRUE(result.isValid());
    double values[25];
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            values[i * 5 + j] = (i == j ? (double)-0.75 : 0.25);
        }
    }
    for (size_t i = 0; i < 25; i++)
    {
        EXPECT_NEAR(result.coeffRef(i / 5, i % 5), values[i], precision);
    }
    result *= mat_5_5;
    for (size_t i = 0; i < 5; i++)
    {
        for (size_t j = 0; j < 5; j++)
        {
            EXPECT_NEAR((i == j ? 1.0 : 0.0), result.coeffRef(i, j), precision);
        }
    }
}

TEST(Square_Matrix, double_and_mat_mult_OK)
{
    Matrix mat;
    mat = SquareDiagonal(3);
    Matrix result = value * mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    double values[9] = { 0,2,4,2,4,6,4,6,8 };
    for (size_t i = 0; i < 9; i++)
    {
        EXPECT_DOUBLE_EQ(result.coeffRef(i / 3, i % 3), values[i]);
    }
}

TEST(Square_Matrix, det_5_5_OK)
{
    Matrix result{ 5, 5 };
    result.coeffRef(0, 0) = 2;
    result.coeffRef(1, 0) = 2;
    result.coeffRef(2, 0) = -1;
    result.coeffRef(3, 0) = -3;
    result.coeffRef(4, 0) = 2;
    result.coeffRef(0, 1) = 2;
    result.coeffRef(1, 1) = 2;
    result.coeffRef(2, 1) = 2;
    result.coeffRef(3, 1) = 3;
    result.coeffRef(4, 1) = 1;
    result.coeffRef(0, 2) = 0;
    result.coeffRef(1, 2) = 2;
    result.coeffRef(2, 2) = 0;
    result.coeffRef(3, 2) = 0;
    result.coeffRef(4, 2) = 2;
    result.coeffRef(0, 3) = 0;
    result.coeffRef(1, 3) = 0;
    result.coeffRef(2, 3) = 1;
    result.coeffRef(3, 3) = 0;
    result.coeffRef(4, 3) = -1;
    result.coeffRef(0, 4) = 0;
    result.coeffRef(1, 4) = 1;
    result.coeffRef(2, 4) = 0;
    result.coeffRef(3, 4) = 3;
    result.coeffRef(4, 4) = 3;

    double res = result.det();
    EXPECT_DOUBLE_EQ(res, 24);

}


class EmptyMatrix : public ::testing::Test {
protected:
    virtual void SetUp(void) {
        Matrix(1, 1).coeffRef(0, 0) = 1;
    }
    virtual void TearDown(void) {
    }
    Matrix mat;
};

TEST(EmptyMatrix, data_FAIL) {
    Matrix mat;
    EXPECT_EQ(mat.data(), nullptr);
    EXPECT_EQ(mat.cols(), 0);
    EXPECT_EQ(mat.rows(), 0);
    EXPECT_FALSE(mat.isValid());
}

TEST(EmptyMatrix, and_mat_mult_FAIL) {
    Matrix mat;
    Matrix result = mat * Matrix(1, 1);
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, and_mat_summ_FAIL) {
    Matrix mat;
    Matrix result = mat + Matrix(1, 1);
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, and_mat_substr_FAIL) {
    Matrix mat;
    Matrix result = mat - Matrix(1, 1);
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, and_double_mult_FAIL) {
    Matrix mat;
    Matrix result = mat * 2.0;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, and_double_div_FAIL) {
    Matrix mat;
    Matrix result = mat / 2.0;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}



TEST(EmptyMatrix, assign_of_empty_FAIL) {
    Matrix mat;
    Matrix result = mat;
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, assing_to_empty_OK)
{
    Matrix mat;
    mat = Matrix(1, 1);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
}

TEST(EmptyMatrix, and_mat_mult_and_assign_FAIL) {
    Matrix mat;
    mat *= Matrix(1, 1);
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, and_mat_summ_and_assign_FAIL) {
    Matrix mat;
    mat += Matrix(1, 1);
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(Matrix(1, 1).isValid());
}
TEST(EmptyMatrix, and_mat_substr_and_assign_FAIL) {
    Matrix mat;
    mat -= Matrix(1, 1);
    EXPECT_FALSE(mat.isValid());
    EXPECT_TRUE(Matrix(1, 1).isValid());
}
TEST(EmptyMatrix, and_double_mult_and_assign_FAIL) {
    Matrix mat;
    mat *= 2.0;
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, and_double_div_and_assign_FAIL) {
    Matrix mat;
    mat /= 2.0;
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, resize_0_0_FAIL)
{
    Matrix mat;
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, resize_1_0_FAIL)
{
    Matrix mat;
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, resize_1_1_OK)
{
    Matrix mat;
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}

TEST(EmptyMatrix, coeffRef_0_0_FAIL)
{
    Matrix mat;
    EXPECT_THROW(mat.coeffRef(0, 0), std::out_of_range);
}
TEST(EmptyMatrix, coeffRef_1_1_FAIL)
{
    Matrix mat;
    EXPECT_THROW(mat.coeffRef(1, 1), std::out_of_range);
}

TEST(EmptyMatrix, set_identity_FAIL)
{
    Matrix mat;
    mat.setIdentity();
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, set_zero_FAIL)
{
    Matrix mat;
    mat.setZero();
    EXPECT_FALSE(mat.isValid());
}
TEST(EmptyMatrix, set_constants_FAIL)
{
    Matrix mat;
    mat.setConstants(2.0);
    EXPECT_FALSE(mat.isValid());
}

TEST(EmptyMatrix, resize_and_set_constants_OK)
{
    Matrix mat;
    mat.setConstants(3, 2, 2.0);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 2.0);
}
TEST(EmptyMatrix, resize_and_set_identity_OK)
{
    Matrix mat;
    mat.setIdentity(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST(EmptyMatrix, resize_and_set_zero_OK)
{
    Matrix mat;
    mat.setZero(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST(EmptyMatrix, transpose_FAIL)
{
    Matrix mat;
    Matrix result = mat.transpose();
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, inverse_FAIL)
{
    Matrix mat;
    Matrix result = mat.inverse();
    EXPECT_FALSE(result.isValid());
}
TEST(EmptyMatrix, det_NaN)
{
    Matrix mat;
    double result = mat.det();
    EXPECT_NE(result, result);
}
TEST(EmptyMatrix, double_and_mat_mult_FAIL)
{
    Matrix mat;
    Matrix result = 2.0 * mat;
    EXPECT_FALSE(result.isValid());
}

TEST(StaticMembers, new_set_zero_OK)
{
    Matrix result = Matrix::zeros(1, 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.0);
    EXPECT_THROW(result.coeffRef(1, 0), std::out_of_range);
    EXPECT_THROW(result.coeffRef(0, 2), std::out_of_range);
}
TEST(StaticMembers, new_set_identity_OK)
{
    Matrix result = Matrix::identity(3, 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 0.0);
}
TEST(StaticMembers, new_set_constants_OK)
{
    Matrix result = Matrix::constants(3, 2, 2.0);
    EXPECT_TRUE(result.isValid());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 2);

    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 1), 2.0);
}










//////////////////////////////////////////




static Matrix Same_Size_Vect_s()
{
    Matrix result{ 3 };
    for (size_t i = 0; i < 3; i++)
    {
        result.coeffRef(0, i) = 2.0 * i;
    }
    return result;
}

static Matrix Same_Size_Vect_Trans()
{
    Matrix result{ 3,1 };
    for (size_t i = 0; i < 3; i++)
    {
        result.coeffRef(i, 0) = 2 * i;
    }
    return result;
}

static Matrix Mat()
{
    Matrix result{ 3,2 };
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            result.coeffRef(i, j) = i + j;
        }
    }
    return result;
}


class Three_Vector : public ::testing::Test {
protected:
    virtual void TearDown(void) { }

    // объекты тестового окружения, доступные в каждом тесте
};


TEST(Three_Vector,Constructor ) {
    Matrix vect;
    vect = Matrix(3);
    
    EXPECT_TRUE(vect.data());

    EXPECT_EQ(vect.cols(), 3);

    EXPECT_EQ(vect.rows(), 1);

    EXPECT_TRUE(vect.isValid());
}

TEST(Three_Vector, coeffRef_0_2_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 1);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 2);
}
TEST(Three_Vector, coeffRef_x_x_FAIL) {

    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 1);

    EXPECT_THROW(vect.coeffRef(1, 1), std::out_of_range);

    EXPECT_THROW(vect.coeffRef(0, 4), std::out_of_range);
}

TEST(Three_Vector, and_Emat_mult_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_Emat_summ_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect + Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_Emat_substr_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect - Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST(Three_Vector, and_DSvect_mult_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * Matrix{ 2, 1 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_DSvect_summ_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect + Matrix{ 2, 1 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_DSvect_substr_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect - Matrix{ 2, 1 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST(Three_Vector, and_SSvect_mult_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * Same_Size_Vect_s();
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_SSvect_summ_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect + Same_Size_Vect_s();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 3);
}
TEST(Three_Vector, and_SSvect_substr_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect - Same_Size_Vect_s();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), -1);
}


TEST(Three_Vector, and_SSvectTrans_mult_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * Same_Size_Vect_Trans();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 10);
}
TEST(Three_Vector, and_SSvectTrans_sum_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect + Same_Size_Vect_Trans();
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, and_SSvectTrans_sub_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect - Same_Size_Vect_Trans();
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}

TEST(Three_Vector, and_SSmatTrans_mult_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * Mat();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 5);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 8);
}


TEST(Three_Vector, and_double_mult_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect * 2.0;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 4);
}
TEST(Three_Vector, and_double_div_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect / 2.0;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 0.5);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 1);
}



TEST(Three_Vector, assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    for (size_t i = 0; i < 3; i++)
        EXPECT_DOUBLE_EQ(result.coeffRef(0, i), vect.coeffRef(0, i));
}



TEST(Three_Vector, and_Emat_mult_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect = Matrix{};
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_Emat_summ_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect += Matrix{};
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_Emat_substr_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect -= Matrix{};
    EXPECT_FALSE(vect.isValid());
}



TEST(Three_Vector, and_DSmat_mult_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect *= Matrix{ 2, 1 };
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_DSmat_summ_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect += Matrix{ 2, 1 };
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_DSmat_substr_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect -= Matrix{ 2, 1 };
    EXPECT_FALSE(vect.isValid());
}


TEST(Three_Vector, and_SSvect_mult_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect *= Same_Size_Vect_s();
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_SSvect_summ_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect += Same_Size_Vect_s();
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 3);
}
TEST(Three_Vector, and_SSvect_substr_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect -= Same_Size_Vect_s();
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), -1);
}


TEST(Three_Vector, and_SSvectTrans_mult_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect *= Same_Size_Vect_Trans();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 1);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 10);
}
TEST(Three_Vector, and_SSvectTrans_sum_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect += Same_Size_Vect_Trans();
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, and_SSvectTrans_sub_and_assign_FAIL) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect -= Same_Size_Vect_Trans();
    EXPECT_FALSE(vect.isValid());
}

TEST(Three_Vector, and_SSvectmat_mult_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect *= Mat();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 5);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 8);
}

TEST(Three_Vector, and_double_mult_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect *= 2.0;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 2);
}
TEST(Three_Vector, and_double_div_and_assign_OK) {
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect /= 2.0;
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.5);
}





TEST(Three_Vector, resize_0_0_FAIL)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.resize(0, 0);
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, resize_1_0_FAIL)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.resize(1, 0);
    EXPECT_FALSE(vect.isValid());
}
TEST(Three_Vector, resize_1_1_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.resize(1, 1);
    EXPECT_TRUE(vect.isValid());
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 1);
}


TEST(Three_Vector, set_identity_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.setIdentity();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 1);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 0);
}
TEST(Three_Vector, set_zero_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.coeffRef(0, 0) = 3;
    vect.setZero();
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 0);
}
TEST(Three_Vector, set_constants_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.setConstants(3.0);
    EXPECT_TRUE(vect.data());
    EXPECT_EQ(vect.rows(), 1);
    EXPECT_EQ(vect.cols(), 3);
    EXPECT_TRUE(vect.isValid());
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 3.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 2), 3.0);
}

TEST(Three_Vector, resize_and_set_constants_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.setConstants(3, 2, 2.0);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 2.0);
}
TEST(Three_Vector, resize_and_set_identity_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.setIdentity(3, 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 0.0);
}
TEST(Three_Vector, resize_and_set_zero_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    vect.setZero(3, 2);
    EXPECT_TRUE(vect.isValid());
    EXPECT_EQ(vect.rows(), 3);
    EXPECT_EQ(vect.cols(), 2);

    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(vect.coeffRef(2, 1), 0.0);
}



TEST(Three_Vector, transpose_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect.transpose();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 3);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0);
    EXPECT_DOUBLE_EQ(result.coeffRef(1, 0), 1);
    EXPECT_DOUBLE_EQ(result.coeffRef(2, 0), 2);
}
TEST(Three_Vector, inverse_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = vect.inverse();
    EXPECT_FALSE(result.isValid());
}
TEST(Three_Vector, det_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    double result = vect.det();
    EXPECT_NE(result, result);
}
TEST(Three_Vector, double_and_mat_mult_OK)
{
    Matrix vect;
    vect = Matrix(3);
    vect.coeffRef(0, 0) = 0;
    vect.coeffRef(0, 1) = 1;
    vect.coeffRef(0, 2) = 2;
    Matrix result = 2.0 * vect;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 3);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 1), 2);
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 2), 4);
}



static Matrix Same_Size_Mat(double value)
{
    Matrix result{ 1,1 };
    result.coeffRef(0, 0) = value;
    return result;
}


class SingleElementMatrix : public ::testing::Test {
protected:
    virtual void TearDown(void) {
    }
};

TEST(SingleElementMatrix, Constructor) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    EXPECT_TRUE(mat.data());

    EXPECT_EQ(mat.cols(), 1);

    EXPECT_EQ(mat.rows(), 1);

    EXPECT_TRUE(mat.isValid());
}

TEST(SingleElementMatrix, coeffRef_0_0_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.coeffRef(0, 0) = 1;
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
}
TEST(SingleElementMatrix, coeffRef_x_x_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    EXPECT_THROW(mat.coeffRef(1, 0), std::out_of_range);

    EXPECT_THROW(mat.coeffRef(0, 1), std::out_of_range);

    EXPECT_THROW(mat.coeffRef(1, 1), std::out_of_range);

}


TEST(SingleElementMatrix, and_Emat_mult_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat * Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(SingleElementMatrix, and_Emat_summ_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat + Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(SingleElementMatrix, and_Emat_substr_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat - Matrix{};
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST(SingleElementMatrix, and_DSmat_mult_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat * Matrix{ 2,3 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(SingleElementMatrix, and_DSmat_summ_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat + Matrix{ 2,3 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}
TEST(SingleElementMatrix, and_DSmat_substr_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat - Matrix{ 2,3 };
    EXPECT_FALSE(result.data());
    EXPECT_EQ(result.rows(), 0);
    EXPECT_EQ(result.cols(), 0);
    EXPECT_FALSE(result.isValid());
}


TEST(SingleElementMatrix, and_SSmat_mult_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat * Same_Size_Mat(2);
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
TEST(SingleElementMatrix, and_SSmat_summ_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat + Same_Size_Mat(2);
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 3);
}
TEST(SingleElementMatrix, and_SSmat_substr_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat - Same_Size_Mat(2);
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), -1);
}


TEST(SingleElementMatrix, and_double_mult_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat * 2.0;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
TEST(SingleElementMatrix, and_double_div_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat / 2.0;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 0.5);
}



TEST(SingleElementMatrix, assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), mat.coeffRef(0, 0));
}

TEST(SingleElementMatrix, and_Emat_mult_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat = Matrix{};
    EXPECT_FALSE(mat.isValid());
}
TEST(SingleElementMatrix, and_Emat_summ_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat += Matrix{};
    EXPECT_FALSE(mat.isValid());
}
TEST(SingleElementMatrix, and_Emat_substr_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat -= Matrix{};
    EXPECT_FALSE(mat.isValid());
}

TEST(SingleElementMatrix, and_DSmat_mult_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat *= Matrix{ 2,3 };
    EXPECT_FALSE(mat.isValid());
}
TEST(SingleElementMatrix, and_DSmat_summ_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat += Matrix{ 2,3 };
    EXPECT_FALSE(mat.isValid());

}
TEST(SingleElementMatrix, and_DSmat_substr_and_assign_FAIL) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat -= Matrix{ 2,3 };
    EXPECT_FALSE(mat.isValid());
}

TEST(SingleElementMatrix, and_SSmat_mult_and_assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat *= Same_Size_Mat(2);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2);
}
TEST(SingleElementMatrix, and_SSmat_summ_and_assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat += Same_Size_Mat(2);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 3);
}
TEST(SingleElementMatrix, and_SSmat_substr_and_assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat -= Same_Size_Mat(2);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), -1);
}


TEST(SingleElementMatrix, and_double_mult_and_assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat *= 2.0;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2);
}
TEST(SingleElementMatrix, and_double_div_and_assign_OK) {
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat /= 2.0;
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.5);
}





TEST(SingleElementMatrix, resize_0_0_FAIL)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.resize(0, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(SingleElementMatrix, resize_1_0_FAIL)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.resize(1, 0);
    EXPECT_FALSE(mat.isValid());
}
TEST(SingleElementMatrix, resize_1_1_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.resize(1, 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
}


TEST(SingleElementMatrix, set_identity_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.coeffRef(0, 0) = 3;
    mat.setIdentity();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
}
TEST(SingleElementMatrix, set_zero_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.setZero();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0);
}
TEST(SingleElementMatrix, set_constants_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.setConstants(2.0);
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
}

TEST(SingleElementMatrix, resize_and_set_constants_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.setConstants(3, 2, 2.0);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 2.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 2.0);
}
TEST(SingleElementMatrix, resize_and_set_identity_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.setIdentity(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 1.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}
TEST(SingleElementMatrix, resize_and_set_zero_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.setZero(3, 2);
    EXPECT_TRUE(mat.isValid());
    EXPECT_EQ(mat.rows(), 3);
    EXPECT_EQ(mat.cols(), 2);

    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 0), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(1, 1), 0.0);
    EXPECT_DOUBLE_EQ(mat.coeffRef(2, 1), 0.0);
}



TEST(SingleElementMatrix, transpose_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = mat.transpose();
    EXPECT_TRUE(mat.data());
    EXPECT_EQ(mat.rows(), 1);
    EXPECT_EQ(mat.cols(), 1);
    EXPECT_TRUE(mat.isValid());
    EXPECT_DOUBLE_EQ(mat.coeffRef(0, 0), 1);
}
TEST(SingleElementMatrix, inverse_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    mat.coeffRef(0, 0) = -4;
    Matrix result = mat.inverse();
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), -0.25);
}
TEST(SingleElementMatrix, det_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    double result = mat.det();
    EXPECT_EQ(result, mat.coeffRef(0, 0));
}
TEST(SingleElementMatrix, double_and_mat_mult_OK)
{
    Matrix mat(1,1);
    mat.coeffRef(0, 0) = 1;
    Matrix result = 2.0 * mat;
    EXPECT_TRUE(result.data());
    EXPECT_EQ(result.rows(), 1);
    EXPECT_EQ(result.cols(), 1);
    EXPECT_TRUE(result.isValid());
    EXPECT_DOUBLE_EQ(result.coeffRef(0, 0), 2);
}
