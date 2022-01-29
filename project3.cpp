#include <iostream>
#include <list>
#include <random>
#include <iomanip>
#include <math.h>
#include <cstddef>

//============================_TASK_1_============================
void pushBackEndAverage(std::list<float>& n)
{
	float sum = 0;
	for (const float& v : n)
	{
		sum += v;
	}

	n.push_back(sum / n.size());

	std::cout << "{";
	for (auto print : n)
		std::cout << " " << print << " ";
	std::cout << "}" << std::endl;

}

//============================_TASK_2_============================


class Matrix {
private:
	const size_t m_Size;
	const size_t m_Capacity;
	double* array;
	double m_Determinant{ 0.0 };

	Matrix getMatrix(Matrix& arr, const size_t item);
	double expectDeterminant(Matrix& arr);
public:
	Matrix(const int size);
	void randomFillMatrix();
	void print() const;
	size_t size() const;
	double determinant() const;

	class Iter {
	private:
		double* m_value;
	public:
		Iter(double* pointer);
		double& operator[](size_t i);
		Iter& operator ++();
		bool operator !=(const Iter& iter);
		double& operator *();
	};

	Iter operator[](size_t i);
	Iter begin();
	Iter end();

	~Matrix();
};


Matrix::Matrix(const int size) : m_Size(size), m_Capacity(size* size)
{
	array = new double[m_Capacity];
}

Matrix::Iter::Iter(double* pointer) : m_value(pointer){}


double& Matrix::Iter::operator[](size_t i)
{
	return *(m_value + i);
}

Matrix::Iter& Matrix::Iter::operator ++()
{
	++m_value;
	return *this;
}

bool Matrix::Iter::operator !=(const Iter& iter)
{
	return m_value != iter.m_value;
}

double& Matrix::Iter::operator *()
{
	return *m_value;
}

Matrix::Iter Matrix::operator[](size_t i)
{
	return Iter(array + i * m_Size);
}

Matrix::Iter Matrix::begin()
{
	return Iter(array);
}

Matrix::Iter Matrix::end()
{
	return Iter(array + m_Capacity);
}

Matrix Matrix::getMatrix(Matrix& arr, const size_t item)
{
	Matrix newArray(arr.size() - 1);
	size_t currentRow = 0;

	for (size_t i = 0; i < arr.size(); ++i)
	{
		if (item == i)
		{
			currentRow = i;
			continue;
		}

		for (size_t j = 0; j < newArray.size(); ++j)
		{
			newArray[currentRow][j] = arr[i][j + 1];
		}

		++currentRow;
	}

	return newArray;
}


double Matrix::expectDeterminant(Matrix& arr)
{
	double determinant = 0;

	if (arr.size() == 1)
	{
		determinant = arr[0][0];
	}
	if (arr.size() == 2)
	{
		determinant = arr[0][0] * arr[1][1] - arr[1][0] * arr[0][1];
	}
	if (arr.size() > 2)
	{
		int d = 1;

		for (size_t i = 0; i < arr.size(); ++i)
		{
			Matrix newArray = getMatrix(arr, i);
			determinant = determinant + d * arr[i][0] * expectDeterminant(newArray);
			d = (-d);
		}
	}

	return determinant;
}


void Matrix::randomFillMatrix()
{
	
	std::random_device rd;
	std::mt19937 mersenne(rd());                                   
	std::uniform_real_distribution<double> urd(-10.0, 10.0);       

	for (size_t i = 0; i < m_Capacity; ++i)
	{
		*(array + i) = round(urd(mersenne) * 10) / 10;
	}

	m_Determinant = expectDeterminant((*this));
	
}

void Matrix::print() const
{
	std::cout << '{';

	for (size_t i = 0; i < m_Capacity;)
	{
		std::cout << std::setw(5) << *(array + i++);

		if (!(i % m_Size))
		{
			std::cout << " }" << std::endl;

			if (i < m_Capacity)
			{
				std::cout << '{';
			}
		}
		else
		{
			std::cout << ',';
		}
	}
}

size_t Matrix::size() const
{
	return m_Size;
}

double Matrix::determinant() const
{
	return m_Determinant;
}

Matrix::~Matrix()
{
	delete[] array;
}

int main()
{
	std::cout << "============================_TASK_1_============================" << "\n" << std::endl;

	std::list<float> n{ 33.2, 2.45, 72.44, 13.12, 5.0 };
	pushBackEndAverage(n);
	
	
	std::cout << "\n" << "============================_TASK_2_============================" << "\n" << std::endl;
		

	for (size_t i = 1; i < 11; ++i)
	{
		std::cout << "Matrix " << i << 'x' << i << ':' << std::endl;
		Matrix m(i);
		m.randomFillMatrix();
		m.print();
		std::cout << "Determinant: " << std::setprecision(3) << m.determinant() << "\n\n";
		
	}
	

	return 0;
}
