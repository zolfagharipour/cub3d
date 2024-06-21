#include "cubid.h"

//for a red square
int main(void)
{
    t_common  d_list;
    
    init_structs(&d_list);
    //init_mlx(&mlx);
    if (init_struct(&mlx) == 0)
		return (cleanup(&mlx), 0);
    put_image(&mlx);
    events(&mlx);
    cleanup(&mlx);
}
