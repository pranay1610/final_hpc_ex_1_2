import numpy as np
import matplotlib.pyplot as plt

def read_pgm(filename):
    with open(filename, 'rb') as f:
        header = f.readline()
        assert header.strip() == b'P5'
        dimensions = f.readline()
        width, height = [int(i) for i in dimensions.split()]
        max_val = int(f.readline().strip())
        assert max_val <= 255

        image = np.fromfile(f, dtype=np.uint8).reshape((height, width))
        return image

def plot_image(image, output_filename):
    plt.imshow(image, cmap='gray')
    plt.colorbar()
    plt.title('Mandelbrot Set')
    plt.savefig(output_filename)
    plt.show()

if __name__ == "__main__":
    input_filename = "mandelbrot.pgm"
    output_filename = "mandelbrot_plot.png"
    image = read_pgm(input_filename)
    plot_image(image, output_filename)
