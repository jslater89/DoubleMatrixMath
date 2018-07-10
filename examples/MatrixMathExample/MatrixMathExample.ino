#include <MatrixMath.h>


#define N  (2)

double A[N][N];
double B[N][N];
double C[N][N];
double v[N];      // This is a row vector
double w[N];

double max = 10;  // maximum random matrix entry range

void setup()
{
	Serial.begin(9600);

	// Initialize matrices
	for (int i = 0; i < N; i++)
	{
		v[i] = i + 1;                  // vector of sequential numbers
		for (int j = 0; j < N; j++)
		{
			A[i][j] = random(max) - max / 2.0f; // A is random
			if (i == j)
			{
				B[i][j] = 1.0f;                  // B is identity
			}
			else
			{
				B[i][j] = 0.0f;
			}
		}
	}

}

void loop()
{

	Matrix.Multiply((double*)A, (double*)B, N, N, N, (double*)C);

	Serial.println("\nAfter multiplying C = A*B:");
	Matrix.Print((double*)A, N, N, "A");

	Matrix.Print((double*)B, N, N, "B");
	Matrix.Print((double*)C, N, N, "C");
	Matrix.Print((double*)v, N, 1, "v");

	Matrix.Add((double*) B, (double*) C, N, N, (double*) C);
	Serial.println("\nC = B+C (addition in-place)");
	Matrix.Print((double*)C, N, N, "C");
	Matrix.Print((double*)B, N, N, "B");

	Matrix.Copy((double*)A, N, N, (double*)B);
	Serial.println("\nCopied A to B:");
	Matrix.Print((double*)B, N, N, "B");

	Matrix.Invert((double*)A, N);
	Serial.println("\nInverted A:");
	Matrix.Print((double*)A, N, N, "A");

	Matrix.Multiply((double*)A, (double*)B, N, N, N, (double*)C);
	Serial.println("\nC = A*B");
	Matrix.Print((double*)C, N, N, "C");

	// Because the library uses pointers and DIY indexing,
	// a 1D vector can be smoothly handled as either a row or col vector
	// depending on the dimensions we specify when calling a function
	Matrix.Multiply((double*)C, (double*)v, N, N, 1, (double*)w);
	Serial.println("\n C*v = w:");
	Matrix.Print((double*)v, N, 1, "v");
	Matrix.Print((double*)w, N, 1, "w");

	while(1);
}
