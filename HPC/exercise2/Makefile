CC = mpicc
CFLAGS = -fopenmp -O3
SRC_DIR = src
INC_DIR = include

OBJS = $(SRC_DIR)/main.o $(SRC_DIR)/mandelbrot.o $(SRC_DIR)/image_utils.o

mandelbrot: $(OBJS)
	$(CC) $(CFLAGS) -o mandelbrot $(OBJS)

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/mandelbrot.h $(INC_DIR)/image_utils.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(SRC_DIR)/mandelbrot.o: $(SRC_DIR)/mandelbrot.c $(INC_DIR)/mandelbrot.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/mandelbrot.c -o $(SRC_DIR)/mandelbrot.o

$(SRC_DIR)/image_utils.o: $(SRC_DIR)/image_utils.c $(INC_DIR)/image_utils.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $(SRC_DIR)/image_utils.c -o $(SRC_DIR)/image_utils.o

clean:
	rm -f mandelbrot $(SRC_DIR)/*.o

