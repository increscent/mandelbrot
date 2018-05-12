onmessage = (e) => {
	var width = e.data.width;
	var height = e.data.height;
	var x_min = e.data.x_min;
	var x_max = e.data.x_max;
	var y_min = e.data.y_min;
	var y_max = e.data.y_max;
	var max_iterations = e.data.max_iterations;

	// contents are initalized to 0
	var data = new Uint8ClampedArray(width * height * 4);

	var x_res = width / (x_max - x_min);
	var y_res = height / (y_max - y_min);

	for (var i = height - 1; i >= 0; i--) {
		for (var j = 0; j < width; j++) {
			var cr = (j / x_res) + x_min;
			var ci = (i / y_res) + y_min;
			var zr = 0;
			var zi = 0;
			var z_tmp = 0;

			for (var k = 0; k < max_iterations; k++) {
				z_tmp = zr;
				zr = zr * zr - zi * zi + cr;
				zi = zi * z_tmp * 2 + ci;

				if (Math.sqrt(zr * zr + zi * zi) > 2)
					break;
			}

			var index = ((height - 1 - i) * width + j) * 4;

			if (k == max_iterations) {
				data[index] = 0;
				data[index + 1] = 0;
				data[index + 2] = 0;
				data[index + 3] = 255;
			} else {
				data[index] = Math.pow(k / max_iterations, 2) * 205 + 50;
				data[index + 1] = Math.pow(k / max_iterations, 4) * 225 + 30;
				data[index + 2] = Math.sin(k / max_iterations, 5) * 275 + 80;
				data[index + 3] = 255;
			}
		}
	}

	postMessage(data);
};