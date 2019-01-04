package com.ifdsgroup.pdf.pdfelement;

import java.io.InputStream;
import java.net.URL;

import javax.activation.URLDataSource;

/*
 * @author Zijian Ying
 */

public class Externalgraphic extends PDFElement {
	private int MAX_IMG_SIZE = 1024 * 1024 * 10; // 10m

	public void doStart() throws Exception {
		String uri = getString("src");
		int image = -1;
		if (uri.startsWith("http"))
			image = fromuri();
		else
			image = fromfile();

		if (image != -1)
			drawimg(image);
	}

	private void drawimg(int image) throws Exception {
		float width = getFloat("content-width");
		float height = getFloat("content-height");

		float top = 0;
		try {
			top = getFloat("top");
		} catch (RuntimeException e) {
		}
		float left = 0;
		try {
			left = getFloat("left");
		} catch (RuntimeException e) {
		}

		// keep aspect ratio
//		float scale_x = width / pl.get_value("imagewidth", image);
//		float scale_y = Math.min(scale_x, height
//				/ pl.get_value("imageheight", image));
		double scale_x = width / pl.get_value("imagewidth", image);
		double scale_y = Math.min(scale_x, height
				/ pl.get_value("imageheight", image));

		pl.save();
		pl.scale((float)scale_x, (float)scale_y);
		pl.place_image(image, (float)(left / scale_x), (float)(top / scale_y), 1f);
		pl.close_image(image);
		pl.restore();
	}

	private int fromuri() throws Exception {
		int width = getInt("width");
		int height = getInt("height");

		URLDataSource fds = new URLDataSource(new URL(getString("src")));

		InputStream is = fds.getInputStream();
		byte bytes[] = new byte[MAX_IMG_SIZE];

		int length = 0, actbyteread;
		while ((actbyteread = is.read(bytes, length, 2048)) != -1) {
			length += actbyteread;
		}

		is.close();

		// must be RGB jpeg
		return pl.open_image("jpeg", "memory", bytes, length, width, height, 3,
				8, null);
	}

	private int fromfile() throws Exception {
		return pl.open_image_file("jpeg", getString("src"), "", 0);
	}
}
