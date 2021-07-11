#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "key.h"
#include <math.h>

#define WIN_WIDTH 480
#define WIN_HEIGHT 320
#define PI = 3.1415
#define MOVE_SPEED 4
#define ROTATION_SPEED (4 * (M_PI / 180))

typedef struct	s_pos
{
	float		x;
	float		y;
}				t_pos;

typedef struct	s_line
{
	t_pos		pos;
	float		alpha;
	float		d;
	int			color;
}				t_line;

typedef struct	s_rec
{
	t_pos		pos;
	t_pos		size;
	int			color;
}				t_rec;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct player
{
	float x;
	float y;
	int walk_deriction;
	int turn_deriction;
	float rotation_angle;
}player;

typedef struct s_game
{
	void *mlx_ptr;
	void *wind_ptr;
	char **map;
	player my_player;
}		t_game;

t_data img;
t_game g_game;

void            my_mlx_pixel_put(int x, int y, int color)
{
    char    *dst;

    dst = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_line(t_line line)
{
	float i;
	float new_x;
	float new_y;

	i = 0;
	while (i < line.d)
	{
		new_x = line.pos.x + cos(line.alpha) * i;
		new_y = line.pos.y + sin(line.alpha) * i;
		my_mlx_pixel_put(new_x, new_y, line.color);
		i = i + 0.2;
	}
}

// void	draw_rect(t_rec rec)
// {
// 	float w;
// 	float h;
// 	float x;

// 	h = 0;
// 	x = rec.pos.x;
// 	while (h < rec.size.y)
// 	{
// 		w = 0;
// 		while (w < rec.size.x)
// 		{
// 			my_mlx_pixel_put(x, rec.pos.y, rec.color);
// 			x++;
// 			w++;
// 		}
// 		rec.pos.y++;
// 		x = rec.pos.x;
// 		h++;
// 	}
// }

void rectangle_render(int i, int j, int w, int h,  int x)
{
	int k,l;

	k = i;
	l = j;

	while (k < i + 32)
	{
		while(l < j + 32)
		{
			
			my_mlx_pixel_put(k, l, x);
			l++;
		}
		l  -= 32;
		k++;
	}
	
}

void render()
{
	int i, j,x ,screen_x,screen_y;
	// t_rec rec;

	i =0; 
	j =0; 
	while(i < 10)
	{
		screen_y = i * 32;
		while(j < 16)
		{  
			screen_x= j * 32;
			// rec.pos.x = screen_x;
			// rec.pos.y = screen_y;
			// rec.size.x = 32;
			// rec.size.y = 32;
			if (g_game.map[i][j] == '1')
			{
				x = 15168962;
				// rec.color = x;
				rectangle_render(screen_x,screen_y, 32, 32, x);
				// draw_rect(rec);
				

			}
			else if (g_game.map[i][j] == '0')
			{
				x = 4802546;
				// rec.color = x;
				rectangle_render(screen_x,screen_y, 32, 32, x);
				// draw_rect(rec);
				
			}
			j++;
		}
		i++;
		j = 0;
	}
	
}


int keyPressed(int key_code)
{
	if(key_code == KEY_A)
		g_game.my_player.turn_deriction = -1;
	if(key_code == KEY_S)
		 g_game.my_player.walk_deriction = -1;
	if(key_code == KEY_W)
		g_game.my_player.walk_deriction = 1;
	if(key_code == KEY_D)
		g_game.my_player.turn_deriction = 1;
		return(0);
}

int keyReleased(int key_code)
{
	if(key_code == KEY_A)
		g_game.my_player.turn_deriction = 0;
	if(key_code == KEY_S)
		g_game.my_player.walk_deriction = 0;
	if(key_code == KEY_W)
		g_game.my_player.walk_deriction = 0;
	if(key_code == KEY_D)
		g_game.my_player.turn_deriction = 0;
		return(0);
}
int		hit_wall(float x, float y)
{
	float i_x;
	float i_y;

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
			return 1;
	i_x = floor(x / 32);
	i_y = floor(y / 32);
	if (g_game.map[(int)i_y][(int)i_x] == '1')
		return 1;
	return 0;
}
  int  update_myplayer_position()
 {
	int move_steep;
	float new_x;
	float new_y;

	g_game.my_player.rotation_angle += g_game.my_player.turn_deriction * ROTATION_SPEED ;
	move_steep = g_game.my_player.walk_deriction * MOVE_SPEED;
	
	new_x = g_game.my_player.x + (move_steep * cos(g_game.my_player.rotation_angle));
	new_y = g_game.my_player.y + (move_steep * sin(g_game.my_player.rotation_angle));

	if (!hit_wall(new_x, new_y))
	{
		g_game.my_player.x = new_x;
		g_game.my_player.y = new_y;
	}

	//rectangle_render(mlx_ptr, data,my_player -> x, my_player -> y, 1501968);
	return (0);
 }
void render_my_player()
{ 
	//update_myplayer_position(mlx_ptr, data, wind_ptr, my_player);
	
	int k,l;
	t_line line;

	k = g_game.my_player.x;
	l = g_game.my_player.y ;
	line.pos.x =  g_game.my_player.x;
	line.pos.y =  g_game.my_player.y;
	line.d = 20;
	line.color = 1501968;
	line.alpha = g_game.my_player.rotation_angle;

	while (k < g_game.my_player.x + 10)
	{
		while(l < g_game.my_player.y + 10)
		{
			//mlx_pixel_put (mlx_ptr, wind_ptr, k, l, 1501968 );
			my_mlx_pixel_put(k, l, 1501968);
			l++;
		}
		l -=10;
		k++;
	}
	draw_line(line);
}

void	clear_image()
{
	t_rec rec;

	rec.pos.x = 0;
	rec.pos.y = 0;
	rec.size.x = WIN_WIDTH;
	rec.size.y = WIN_HEIGHT;
	rec.color = 16777215;
	 rectangle_render(0, 0, WIN_WIDTH, WIN_HEIGHT, 16777215);
	//draw_rect(rec);
}

int		main_loop(void)
{
	 clear_image();
	update_myplayer_position();
	render();
	render_my_player();
	mlx_put_image_to_window(g_game.mlx_ptr, g_game.wind_ptr, img.img, 0, 0);
	return 0;	
}
int main ()
{
	
	int k;
	
	g_game.map = malloc(sizeof(char*) * 11);

	g_game.mlx_ptr = mlx_init();
	g_game.wind_ptr = mlx_new_window(g_game.mlx_ptr,WIN_WIDTH,WIN_HEIGHT,"map2d");
	img.img = mlx_new_image(g_game.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);

	g_game.my_player.x = WIN_WIDTH / 2;
	g_game.my_player.y = WIN_HEIGHT / 2;
	g_game.my_player.walk_deriction = 0;
	g_game.my_player.turn_deriction = 0;
	g_game.my_player.rotation_angle = M_PI / 2;

	g_game.map[0] = strdup("111111111111111");
	g_game.map[1] = strdup("100000000000101");
	g_game.map[2] = strdup("100001000000101");
	g_game.map[3] = strdup("111100000010101");
	g_game.map[4] = strdup("100000000010101");
	g_game.map[5] = strdup("100000000011101");
	g_game.map[6] = strdup("100000000000001");
	g_game.map[7] = strdup("111110000111101");
	g_game.map[8] = strdup("100000000000001");
	g_game.map[9] = strdup("111111111111111");
	
	mlx_hook(g_game.wind_ptr, 2, 0, keyPressed, (void*)0);
	mlx_hook(g_game.wind_ptr, 3, 0, keyReleased, (void*)0);
	mlx_loop_hook(g_game.mlx_ptr, main_loop, (void*)0);
	

	mlx_loop(g_game.mlx_ptr);
	 return(0);

}
