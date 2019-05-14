#include "MainTesting.h"
#include "Environment.h"

#include "Reader.h"
#include "RandomMatrixFactory.h"
#include "RandomEngine.h"

#include "Matrix.h"
#include "Transformation.h"
#include "AffineTransformation.h"

using namespace std;
using namespace matrixes;
using namespace transformations;
using namespace IO;
using namespace random;

void MainTesting::test()
{
	int n = 5;


	Environment env(n);
	string foldername = env.run();

	Reader reader(foldername);
	RowB v1(n), v2(n), x(n);
	MatrixB M1, M2;
	Transformation S, T, F, FT, P_result;
	reader.read(v1, "v1.txt");
	reader.read(v2, "v2.txt");
	reader.read(M1, "M1.txt");
	reader.read(M2, "M2.txt");
	reader.read(S, "S.txt");
	reader.read(T, "T.txt");
	reader.read(F, "F.txt");
	reader.read(FT, "FoT.txt");
	reader.read(P_result, "P.txt");

	MatrixB invM1, invM2; // обратные к М1 и М2 соотв
	invM1.initInverse(M1);
	invM2.initInverse(M2);

	RandomMatrixFactory<BOOL> fact(RandomEngine().getRandomEngine());
	fact.getRandomRow(x);

	
	
}

