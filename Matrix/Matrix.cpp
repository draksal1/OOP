#include "Matrix.hpp"
#include <iostream>

void Matrix::set(size_t rows, size_t cols)
{

	cols_ = cols;
	rows_ = rows;
	if (rows == 0 || cols == 0 )
	{
		valide_ = false;
		data_ = nullptr;
	}
	else
	{
		valide_ = true;
		data_ = new double[cols * rows];
	}
}
Matrix::Matrix(size_t cols) : Matrix{1, cols}
{
}
Matrix::Matrix(size_t rows, size_t cols)
{
	set(rows, cols);
}
Matrix::~Matrix()
{
	delete[] data_;
}

Matrix::Matrix(const Matrix& mat) : Matrix{ mat.rows_, mat.cols_ }
{
	for (int i = 0; i < rows_ * cols_;i++) 
	{
		data_[i] = mat.data_[i];
	}
	valide_ = mat.valide_;
}


Matrix Matrix::operator*(const Matrix& mat)const
{
	if ( cols_ != mat.rows_) {
		return Matrix();
	}
	Matrix result(*this);
	result *= mat;
	return result;
}

Matrix Matrix::operator-(const Matrix& mat) const
{
	Matrix result(*this);
	result -= mat;
	return result;
}

Matrix Matrix::operator+(const Matrix& mat) const 
{
	Matrix result(*this);
	result += mat;
	return result;
}


Matrix Matrix::operator*(const double value) const
{
	Matrix res{ *this };
	res *= value;
	return res;
}

Matrix Matrix::operator/(double value) const
{
	if (cols_ <= 0 || rows_ <= 0)
	{
		return Matrix();
	}
	Matrix res{ *this };
	res /= value;
	return res;
}

Matrix& Matrix::operator=(const Matrix& mat)
{
	if (this == &mat)
	{
		return *this;
	}
	resize(mat.rows_, mat.cols_);
	if (data_)
	{
		std::memcpy(data_, mat.data_, mat.rows_ * mat.cols_ * sizeof(double));
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& mat)
{
	if ( cols_ != mat.rows_ || !isValid() || !mat.isValid()) {
		*this = Matrix();
		return *this;
	}

	double mult_result = 0;
	Matrix S(*this);
	resize(rows_, mat.cols_);
	for (size_t result_i_index = 0; result_i_index < rows_; result_i_index++)
	{
		for (size_t result_j_index = 0; result_j_index < cols_; result_j_index++)
		{
			mult_result = 0;
			for (size_t operands_index = 0; operands_index <mat.rows_; operands_index++)
			{
				mult_result += S.coeffRef(result_i_index, operands_index) * mat.coeffRef(operands_index, result_j_index);
			}
			coeffRef(result_i_index, result_j_index) = mult_result;
		}
	}
	return *this;
}


Matrix& Matrix::operator+=(const Matrix& mat)
{
	if (rows_ != mat.rows_ || cols_ != mat.cols_ || !isValid() || !mat.isValid()) {
		*this = Matrix();
		return *this;
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			coeffRef(i, j) += mat.coeffRef(i, j);
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& mat)
{
	if (rows_ != mat.rows_ || cols_ != mat.cols_ || !isValid() || !mat.isValid()) {
		*this = Matrix();
		return *this;
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			coeffRef(i, j) -= mat.coeffRef(i, j);
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(double value)
{
	if (cols_ <= 0 || rows_ <= 0)
	{
		*this = Matrix();
		return *this;
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			coeffRef(i, j) = coeffRef(i, j) * value;
		}
	}
	return *this;
}

Matrix& Matrix::operator/=(double value)
{
	if (value == 0)
	{
		throw std::overflow_error("division by zero");
	}
	if (cols_ <= 0 || rows_ <= 0 || value==0)
	{
		*this = Matrix();
		return *this;
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			coeffRef(i, j) = coeffRef(i, j) / value;
		}
	}
	return *this;
}



bool Matrix::isValid() const
{
	return rows_ > 0 && cols_ > 0;

}

void Matrix::resize(size_t rows, size_t cols)
{

	delete[] data_;
	set(rows, cols);
}

const double& Matrix::coeffRef(size_t rowIdx, size_t colIdx) const
{
	if (rowIdx<0 || colIdx<0 || colIdx>=cols_ || rowIdx>=rows_)
	{
		throw std::out_of_range("(i, j) element out of range");
	}
	return *(data_ + rowIdx * cols_ + colIdx);
}

double& Matrix::coeffRef(size_t rowIdx, size_t colIdx)
{
	if (colIdx>=cols_ || rowIdx>=rows_)
	{
		throw std::out_of_range("(i, j) element out of range");
	}

	return *(data_ + rowIdx * cols_ + colIdx);
}

const double* Matrix::data() const
{
	return data_;
}

double* Matrix::data()
{
	return data_;
}

size_t Matrix::rows() const
{
	return rows_;
}

size_t Matrix::cols() const
{
	return cols_;
}



Matrix& Matrix::setIdentity()
{
	if (cols_ <= 0 || rows_ <= 0)
	{
		return *this;
	}
	for (int i = 0; i < rows_; i++)
	{
		for (int j = 0; j < cols_; j++)
		{
			data_[i * cols_ + j] = i == j ? 1.0 : 0.0;
		}
	}
	return *this;
}

Matrix& Matrix::setZero()
{
	if (cols_ <= 0 || rows_ <= 0)
	{
		return *this;
	}
	for (int i = 0; i < rows_ * cols_; i++)
	{
		data_[i] = 0;
	}
	return *this;
}

Matrix& Matrix::setConstants(double value)
{
	if (cols_ <= 0 || rows_ <= 0)
	{
		return *this;
	}
	for (int i = 0; i < rows_ * cols_; i++)
	{
		data_[i] = value;
	}
	return *this;
}

Matrix& Matrix::setZero(size_t rows, size_t cols)
{ 
	if (cols <= 0 || rows <= 0)
	{
		return *this;
	}
	resize(rows, cols);
	setZero();
	return *this;
}

Matrix& Matrix::setIdentity(size_t rows, size_t cols)
{
	if (cols <= 0 || rows <= 0)
	{
		return *this;
	}
	resize(rows, cols);
	setIdentity();
	return *this;
}

Matrix& Matrix::setConstants(size_t rows, size_t cols, const double value)
{
	if (cols <= 0 || rows <= 0)
	{
		return *this;
	}
	resize(rows, cols);
	setConstants(value);
	return *this;
}

Matrix Matrix::transpose() const
{
	Matrix result = Matrix(cols_, rows_);
	for (int i = 0; i < result.rows_; i++)
	{
		for (int j = 0; j < result.cols_; j++)
		{

			result.coeffRef(i, j) = coeffRef(j, i);
		}
	}
	return result;
}
double Matrix::det() const
{
	if (!isValid())
	{
		return std::nan("0");
	}
	if (rows_ != cols_) {
		return std::nan("0");
	}

	Matrix m(rows_, cols_);
	double det = 1.0;
	int sgn = 1;
	for (int i = 0; i <rows_*cols_; i++) {
		m.data_[i] = data_[i];
	}
	for (int i = 0; i < cols_; i++) {
		int ind = i;
		while (ind < cols_ && m.data_[i * cols_ + ind] == 0) {
			ind++;
		}
		if (ind >= cols_) {
			return 0.0;
		}
		else if (ind != i) {
			sgn *= -1;
			for (int j = 0; j < rows_; j++) {
				double tmp = m.data_[j * cols_ + i];
				m.data_[j * cols_ + i] = m.data_[j * cols_ + ind];
				m.data_[j * cols_ + ind] = tmp;
			}
		}

		double pivot = m.data_[i * cols_ + i];
		det *= pivot;

		for (int j = i + 1; j < rows_; j++) {
			double factor = m.data_[j * cols_ + i] / pivot;

			for (int k = i + 1; k < cols_; k++) {
				m.data_[j * cols_ + k] -= factor * m.data_[i * cols_ + k];
			}
		}
	}
	return det * sgn;
}

const double Matrix::algebraic_addition(size_t element_i, size_t element_j) const
{
	if (rows_ == 1)
	{
		return 1;
	}
	Matrix mat = Matrix(rows_ - 1, cols_ - 1);

	size_t i_jump = 0;
	size_t j_jump = 0;
	for (size_t i_index = 0; i_index < mat.rows_; i_index++)
	{
		if (i_index == element_i)
		{
			i_jump++;
		}
		j_jump = 0;
		for (size_t j_index = 0; j_index < mat.cols_; j_index++)
		{
			if (j_index == element_j)
			{
				j_jump++;
			}
			double b = coeffRef(i_index + i_jump, j_index + j_jump);
			mat.coeffRef(i_index, j_index) = b;
		}
	}
	double a = mat.det();
	if ((element_i + element_j) % 2 != 0)
	{
		return -a;
	}
	else
	{
		return a;
	}
}


Matrix Matrix::inverse() const
{
	double det = this->det();
	if (rows_ == 1 || cols_ == 1)
	{
		det=data_[0];
	}
	else
	{
		det = this->det();
	}
	if (det==0)
	{
		return Matrix();
	}
	Matrix result = Matrix(cols_, rows_);
	for (size_t i_index = 0; i_index < rows_; i_index++)
	{
		for (size_t j_index = 0; j_index < cols_; j_index++)
		{
			result.coeffRef(i_index, j_index) = algebraic_addition(j_index, i_index) / det;
		}
	}
	return result;
}

Matrix Matrix::identity(const size_t rows, const size_t cols)
{
	Matrix a;
	a.setIdentity(rows, cols);
	return a;
}

Matrix Matrix::zeros(size_t rows, size_t cols)
{
	Matrix a(rows, cols);
	a.setZero(rows, cols);
	return a;
}

Matrix Matrix::constants(size_t rows, size_t cols, double value)
{
	Matrix a(rows, cols);
	a.setConstants(value);
	return a;
}

Matrix operator*(double value, const Matrix& mat)
{
	return mat * value;
}