#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

#define ITERATIONS 100
#define I_MIN -2
#define I_MAX 2
#define R_MIN -2
#define R_MAX 2
#define RESOLUTION 1000 // pixels per unit

int main () {
	int width = (R_MAX - R_MIN) * RESOLUTION;
	int height = (I_MAX - I_MIN) * RESOLUTION;

  ofstream file;
  file.open ("test.ppm");
  file << "P3\n";
	file << width << " " << height << " 255\n";

	// cout << "width: " << width << endl;
	// cout << "columns: " << (R_MAX * RESOLUTION) - (R_MIN * RESOLUTION) << endl;
	// cout << "height: " << height << endl;
	// cout << "rows: " << (I_MAX * RESOLUTION) - (I_MIN * RESOLUTION) << endl;

	for (int i = I_MAX * RESOLUTION; i > I_MIN * RESOLUTION; i--) {
		for (int j = R_MIN * RESOLUTION; j < R_MAX * RESOLUTION; j++) {

			// int r = (i * 3 + j * 10) % 255;
			// int g = (i * 10 + j * 3) % 255;
			// int b = (i * 5 + j * 5) % 255;

			int r = 100, g = 100, b = 100;

			double cr = j / (double)(RESOLUTION); // real part of c
			double ci = i / (double)(RESOLUTION); // imaginary part of c
			double zr = 0; // real part of z
			double zi = 0; // imaginary part of z
			double zr_tmp = 0;
			double z_abs = 0;
			int k = 0;

			for (k = 0; k < ITERATIONS && z_abs < 2; k++) {
				zr_tmp = zr;
				zr = (zr * zr) - (zi * zi) + cr;
				zi = 2 * zi * zr_tmp + ci;
				z_abs = sqrt((zr * zr) + (zi * zi));
			}

			r = (ITERATIONS - k) * 255 / ITERATIONS * (ITERATIONS - k) / ITERATIONS;
			g = (ITERATIONS - k) * 255 / ITERATIONS * (ITERATIONS - k) / ITERATIONS;
			b = (ITERATIONS - k) * 255 / ITERATIONS * (ITERATIONS - k) / ITERATIONS;

			// if (z_abs >= 2) {
			// 	r = 255;
			// 	g = 255;
			// 	b = 255;
			// }

			// grid lines
			// if (i == 0 || j == 0) {
			// 	r = 0;
			// 	g = 0;
			// 	b = 0;
			// }

			file << r << " " << g << " " << b;

			if (j < (width - 1)) {
				file << " ";
			}
		}

		if (i < (height - 1)) {
			file << "\n";
		}

		if (i % 100 == 0) {
			cout << ((I_MAX * RESOLUTION) - i) * 100 / height << "\%\n";
		}
	}
  file.close();
  return 0;
}