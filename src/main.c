#include "cubid.h"

int main(int argc, char **argv)
{
    t_common  d_list;
    
    if (error_arguments(argc, argv) == 0)
        return (0);
    if (init_structs(&d_list, argv[1]) == 0)
      return (0);
    read_map_from_file(&d_list);
    //test_map(&d_list);
    minimap(&d_list);
    put_image(&d_list, d_list.mlx);
    events(&d_list);
    //basic 3d array for testing --> d_list->map->raw_map
    //read from the map_file
    cleanup(&d_list);
    return 1;
}
