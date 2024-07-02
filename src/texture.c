# include "cubid.h"

int check_the_textures_open(void)
{
    if (access("textures/west.xpm", F_OK) == -1)
    {
        perror("Error");
        exit(1);
    }
    else if (access("textures/east.xpm", F_OK) != 0)
    {
        perror("Error");
        exit;
    }
    else if (access("textures/north.xpm", F_OK) != 0)
    {
        perror("Error"); 
        exit(1);
    }
    else if (access("textures/south.xpm", F_OK) != 0)
    {
        perror("Error");
        exit(1);
    }
    return (TRUE);
}

int load_textures(t_common *d_list, t_texture *texture, int i)
{
    void    *img;
    char     *addr;
    int     bpp;
    int     width;
    int     height;
    int     line_length;
    int     endian;

    img = mlx_xpm_file_to_image(texture->mlx, texture->path[i], &width, &height);
    if (texture->img == NULL)
    {
        ft_printf("Texture not found\n");
        return (FALSE);
    }
    addr = mlx_get_data_addr(texture->img, &bpp, &line_length, &endian);
    texture->texture_buffer[i] = (int *)malloc(sizeof(int) * width * height);
    if (!texture->texture_buffer[i])
    {
        ft_printf("Malloc failed\n");
        return (FALSE);
    }
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            texture->texture_buffer[i][width * y + x] = addr[y * line_length / 4 + x];
        }
    }
    texture->img = img;
    return (TRUE);
}

int    initiate_textures(t_common *d_list)
{
    t_texture   *texture;

    texture = d_list->texture;

    int i = 0;
    // while (i < 4)
    // {
        if (load_textures(d_list, texture, i) == FALSE)
            return (FALSE);
    // }
    return (TRUE);
}