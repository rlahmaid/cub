#include<mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct	s_map
{
	char		**map;
	int			w;
	int			h;
}				t_map;
typedef struct	s_pos
{
	float		x;
	float		y;
}				t_pos;

typedef struct	s_rec
{
	t_pos		pos;
	t_pos		size;
	int			color;
}				t_rec;
void	draw_rect(t_rec rec, void* mlx_ptr, void *mlx_window_ptr)
{
	float w;
	float h;
	float x;

	h = 0;
	x = rec.pos.x;
	while (h < rec.size.y)
	{
		w = 0;
		while (w < rec.size.x)
		{
			//mlx_pixel_put(x, rec.pos.y, rec.color);
			mlx_pixel_put(mlx_ptr,mlx_window_ptr,x,rec.pos.y,rec.color);
			x++;
			w++;
		}
		rec.pos.y++;
		x = rec.pos.x;
		h++;
	}
}
void	render_map(void *mlx_ptr, void *mlx_window_ptr, t_map map)
{
	int i;
	int j;
	t_rec rec;

	i = 0;
	while (i < map.h)
	{
		j = 0;
		while (j < map.w)
		{
			rec.size.x = 64;
			rec.size.y = 64;
			rec.pos.x = j * 64;
			rec.pos.y = i * 64;
			rec.color = 13434828;
			if (map.map[i][j] == '1')
			{
				draw_rect(rec, mlx_ptr, mlx_window_ptr);
			}
			j++;
		}
		i++;
	}
}
int main()
{
	t_map map;

	map.map = malloc(sizeof(char*) * 10);
	map.map[0] = strdup("11111111111111111111111111111");
	map.map[1] = strdup("10000000000000000000000000001");
	map.map[2] = strdup("10000000000000000000000000001");
	map.map[3] = strdup("10000000000000002000000000001");
	map.map[4] = strdup("10000000000000000000000000001");
	map.map[5] = strdup("1000000000000000000N000000001");
	map.map[6] = strdup("10000000000000000000000000001");
	map.map[7] = strdup("10000000000000000000000000001");
	map.map[8] = strdup("10000000000000000000000000001");
	map.map[9] = strdup("11111111111111111111111111111");
	map.w = 30;
	map.h = 10;
	void *mlx_ptr;
	void *mlx_window_ptr;
	int mlx_put_ptr;
	//int mlx_loop ;

	int x = 1920, y = 640, z = 50, b = 50;

	mlx_ptr = mlx_init();
	mlx_window_ptr = mlx_new_window(mlx_ptr,x,y,"maincub");
	
	render_map(mlx_ptr, mlx_window_ptr, map);
	// while(z <100)
	// {
	// 	b = 50;
	// 	while (b < 100)
	// 	{
	// 		mlx_put_ptr = mlx_pixel_put(mlx_ptr,mlx_window_ptr,z,b,13434828);
	// 		b++;
	// 	}
	// 	z++;

	// }
	mlx_loop(mlx_ptr);

	return (0);
	

}
