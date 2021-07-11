#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#include <key.h>

#define WIN_WIDTH 480
#define WIN_HEIGHT 320



typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}





 
void rectangle_render(void *mlx_ptr,t_data data,int i, int j, int x)
{
	int k,l;

	k = i;
	l = j;

	while (k < i + 32)
	{
		while(l < j + 32)
		{
			
			my_mlx_pixel_put(&data, k, l, x);
			l++;
		}
		l -=32;
		k++;
	}
	
}

void render(char **str,void *mlx_ptr,t_data data)
{
	int i, j,x ,screen_x,screen_y;

	i =0; 
	j =0; 
	while(i < 10)
	{
		screen_y = i * 32;
		while(j < 16)
		{  
			screen_x= j * 32;
			if (str[i][j] == '1')
			{
				x = 15168962;
				rectangle_render(mlx_ptr,data,screen_x,screen_y, x);
				

			}
			else if (str[i][j] == '0')
			{
				x = 4802546;
				rectangle_render(mlx_ptr, data,screen_x,screen_y, x);
				
			}
			j++;
		}
		i++;
		j = 0;
	}
	
}


typedef struct player
{
	int x;
	int y;
	int walk_deriction;
	int turn_deriction;
	int rotation_angle;
	int moveSpeed;
	int rotaionSpeed;
}player;

int  keypressed (int key_code /*player *my_player*/)
{
	printf("\n \n \t--->|%d| \n\n" ,key_code);
	// if(key_code ==KEY_A)
	// 	my_player.turnDeriction = -1;
	// if(key_code == KEY_S)
	// 	 my_player.walkDeriction = -1
	// if(key_code == KEY_W)
	// 	my_player.walkDeriction = 1
	// if(key_code == KEY_D)
	// 	my_player.turnDeriction = 1;
	return (0);
}
//    player update_myplayer_position(void *wind_ptr, int x, int y)
//   {
// 	  player blab;
// 	 // mlx_key_hook (wind_ptr, keypressed(), /*player my_player*/blab);
	  
//   }

//  void render_my_player()
//   {
//  	 update_myplayer_position();

//  }

int		key_press(int key, t_data *img)
{
	printf("pressed the key[%d]\n", key);
	return (0);
}
int main ()
{
	char **str;
	void *mlx_ptr;
	void *wind_ptr;
	int k;
	t_data img;
	int key_code = 0;

	mlx_ptr = mlx_init();
	img.img = mlx_new_image(mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	wind_ptr = mlx_new_window(mlx_ptr,WIN_WIDTH,WIN_HEIGHT,"map2d");


	str[0] = "111111111111111";
	str[1] = "100000000000101";
	str[2] = "100001000000101";
	str[3] = "111100000010101";
	str[4] = "100000000010101";
	str[5] = "100000001111101";
	str[6] = "100000000000001";
	str[7] = "111110000111101";
	str[8] = "100000000000001";
	str[9] = "111111111111111";
	 render(str,mlx_ptr, img);
	mlx_put_image_to_window(mlx_ptr, wind_ptr, img.img, 0, 0);
	//mlx_key_hook (wind_ptr, keypressed(key_code), 0);
	mlx_hook(wind_ptr, 2, 0, key_press, &img);
	//key_code

mlx_loop(mlx_ptr);
	 return(0);

}
