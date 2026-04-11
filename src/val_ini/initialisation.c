#include "../../include/cub3d.h"

t_main *initialise()
{
    int i = 0;
    t_main *main = malloc(sizeof(t_main));
    if(!main)
        return(NULL);
    main->parser        = NULL;
    main->image         = NULL;
    main->map_data      = NULL;
    main->mlx           = NULL;
    main->player        = NULL;
    while(i < 4)
    {
        main->textures[i]   = NULL;
        i++;
    }
    return(main);
}