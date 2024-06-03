#pragma once
#include <vector>
class Matrix final {
public:
	Matrix()=default;
	Matrix(size_t cols);
	Matrix(size_t rows, size_t cols);
	~Matrix();

	Matrix(const Matrix& mat);
	Matrix operator*(const Matrix& mat)const;
	Matrix operator-(const Matrix& mat)const;
	Matrix operator+(const Matrix& mat)const;

	Matrix operator*(double value)const;
	Matrix operator/(double value)const;

	Matrix& operator=(const Matrix& mat);
	Matrix& operator*=(const Matrix& mat);
	Matrix& operator+=(const Matrix& mat);
	Matrix& operator-=(const Matrix& mat);

	Matrix& operator*=(double value);
	Matrix& operator/=(double value);

	bool isValid()const;//

	void resize(size_t rows, size_t cols);

	const double& coeffRef(size_t rowIdx, size_t colIdx) const;
	double& coeffRef(size_t rowIdx, size_t colIdx);

	const double* data() const;
	double* data();

	size_t rows()const;
	size_t cols()const;

	Matrix& setIdentity();
	Matrix& setZero();
	Matrix& setConstants(const double value);

	Matrix& setIdentity(size_t rows, size_t cols);
	Matrix& setZero(size_t rows, size_t cols);
	Matrix& setConstants(size_t rows, size_t cols,const double value);

	Matrix transpose() const;
	Matrix inverse()const;
	double det()const;

static	Matrix identity(const size_t rows, const size_t cols);
static	Matrix zeros(size_t rows, size_t cols);
static	Matrix constants(size_t rows, size_t cols,const double value);

	friend Matrix operator*(const double value, const Matrix& mat);
private:
	void set(size_t rows, size_t cols);
	size_t rows_{};
	size_t cols_{};
	double* data_{};
	bool valide_{};
	const double algebraic_addition(size_t element_i, size_t element_j) const;
};