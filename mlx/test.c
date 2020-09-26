#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mlx.h>

typedef struct    data_s
{
    void          *mlx_ptr;
    void          *mlx_win;
}                 data_t;

int main(void)
{
    data_t        data;

    if ((data.mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
    if ((data.mlx_win = mlx_new_window(data.mlx_ptr, 1920, 1080, "Hello world")) == NULL)
        return (EXIT_FAILURE);
	mlx_pixel_put(data.mlx_ptr, data.mlx_win, 10, 10, 0x00FF0000);
	mlx_loop(data.mlx_ptr);
    return (EXIT_SUCCESS);
}
