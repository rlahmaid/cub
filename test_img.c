#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "mlx.h"

#define WIN_WIDTH 400
#define WIN_HEIGHT 400

int main()
{
	//printf("%lf",tan(4.3));
	int k;
	int x = 30, y = 30;

	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	void *img_ptr= mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

	int *img = (int *)mlx_get_data_addr(img_ptr, &k, &k, &k);

	img[0 /*+ (y * WIN_WIDTH)*/] = 16711680;

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);

/*
	int x = 60, y = 60;

	while (x < 100)
	{
		x++;
		while (y < 100)
			mlx_pixel_put(mlx_ptr, win_ptr, x, y++, 16711680);
	}

*/
	//mlx_clear_window(mlx_ptr, win_ptr);

mlx_loop(mlx_ptr);

//	mlx_clear_window(mlx_ptr, win_ptr);
	return (0);
}




///gcc test.c -lmlx -framework OpenGL -framework AppKit
