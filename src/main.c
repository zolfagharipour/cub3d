#include "cubid.h"

int main(void)
{
    t_common  d_list;
    
    if (init_structs(&d_list) == 0)
      return (0);
    test_map(&d_list);
    put_image(&d_list, d_list.mlx);
    events(&d_list);
    //basic 3d array for testing --> d_list->map->raw_map
    //read from the map_file
    
    return 1;
}
