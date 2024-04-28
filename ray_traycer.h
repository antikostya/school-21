/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_traycer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlucanti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 11:38:33 by tlucanti          #+#    #+#             */
/*   Updated: 2021/04/20 15:34:47 by tlucanti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRAYCER_H
# define RAY_TRAYCER_H
# ifndef	_GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include "objects.h"

# include <guilib.h>
# include <math.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_object
{
	 void			*obj;
	int				id;
	t_point			normal;
	t_color			alpha_rgb;
	unsigned int	local_color;
	float			reflective;
	float			t;
}					t_object;

typedef struct s_scene
{
	int			res_x;
	int			res_y;
	struct gui_window	*window;
	float		dist;

	t_camera	**cameras;
	int			cameras_num;
	t_camera	*current_camera;
	int			current_camera_num;

	t_sphere	**spheres;
	int			spheres_num;

	t_plane		**planes;
	int			planes_num;

	t_triangle	**triangles;
	int			triangles_num;

	t_square	**squares;
	int			squares_num;

	t_cylinder	**cylinders;
	int			cylinders_num;

	t_circle	**circles;
	int			circles_num;

	t_light		**lights;
	int			lights_num;
}				t_scene;

extern t_scene	*g_scene;

# define RECURSION_DEPTH 4
# define EPS 0.001f
# define INF INFINITY
# define MINF -INFINITY
# define PI 3.1415926535f
# define PI_HALF 1.5707963267948966f

# define BACKGROUND_COLOR	BLACK
# define RED				0x00ff0000u
# define GREEN				0x0000ff00u
# define BLUE				0x000000ffu
# define YELLOW				0x00ffff00u
# define CYAN				0x0000ffffu
# define MAGNETA			0x00ff00ffu
# define WHITE				0x00ffffffu
# define GREY				0x00888888u
# define BLACK				0x00000000u

# define DARKRED			0x00880000u
# define DARKGREEN			0x00008800u
# define DARKBLUE			0x00000088u
# define DARKYELLOW			0x00888800u
# define DARKCYAN			0x00008888u
# define DARKMAGNETA		0x00880088u
# define DARKGREY			0x00444444u

# define GOOD				"\e[1;32m"
# define WARNING			"\e[1;33m"
# define ERROR				"\e[1;31m"
# define RESET				"\e[0m"

int				main(int argc, char **argv);
int				main_1(int argc, char **argv);
unsigned int	trace_ray(t_point *o, t_point *d, t_pair *t,
					int recursion_depth);
t_color			compute_lightning(t_point *p, t_point *n, t_point *v, int s);

int				camera(t_camera_input *inp, t_camera **dest);
int				light(t_light_input *inp, t_light **dest);
int				sphere(t_sphere_input *inp, t_sphere **dest);
int				plane(t_plane_input *inp, t_plane **dest);
int				triangle(t_triangle_input *inp, t_triangle **dest);
int				square(t_square_input *inp, t_square **dest);
int				square_4p(t_triangle_input *inp, t_square **dest);
int				cylinder(t_cylinder_input *inp, t_cylinder **dest);
int				circle(t_circle_input *inp, t_circle **dest);
int				circle_append(t_cylinder_input *i);

float			intersect_sphere(t_point *o, t_point *d, t_sphere *sphere,
					t_pair arg);
float			intersect_plane(t_point *o, t_point	*d, t_plane *plane);
float			intersect_triangle(t_point *o, t_point *d,
					t_triangle *triangle);
float			intersect_square(t_point *o, t_point *d, t_square *square);
t_pair			intersect_cylinder(t_point *o, t_point *d, t_cylinder *cylinder,
					float t_min);
float			intersect_circle(t_point *o, t_point *d, t_circle *circle);

float			closest_intersection_sphere(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
float			closest_intersection_plane(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
float			closest_intersection_triangle(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
float			closest_intersection_square(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
float			closest_intersection_cylinder(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
float			closest_intersection_circle(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);

t_color			*color(float red, float green, float blue, float intensity);
t_color			color_stack(float red, float green, float blue,
					float intensity);
int				color_plmul_color(t_color *p, t_color *to_sum, float to_mul);
unsigned int	color_mul(unsigned int col, float alpha);
unsigned int	color_mul_rgb(unsigned int col, t_color *alpha);
unsigned int	color_sum(unsigned int col1, unsigned int col2);

t_point			*point(float x, float y, float z);
t_point			*point_minus(t_point *p1, t_point *p2);
t_point			*point_plus(t_point *p1, t_point *p2);
t_point			point_stack(float x, float y, float z);
t_point			point_copy_stack(t_point *to_cpy);
t_point			point_plus_stack(t_point *p1, t_point *p2);
t_point			point_minus_stack(t_point *p1, t_point *p2);
t_point			*point_cross(t_point *p1, t_point *p2);
t_point			point_cross_stack(t_point *p1, t_point *p2);
void			point_mul_num(t_point *p, float num);
void			point_mul_point(t_point *p, t_point *to_mul);
void			point_plus_num(t_point *p, float to_sum);
void			point_plus_point(t_point *p, t_point *to_sum);

void			rotate_matrix(t_matrix3 *matr, float alpha, float theta,
					float gamma);
void			matrix3_mul(t_matrix3 *matr, t_point *vect);

float			ft_pow(float num, int power);
float			triple_product(t_point *n, t_point *a, t_point *p, t_point *v);
float			dot(t_point *a, t_point *b);
float			det2(float a1, float a2, float b1, float b2);
t_point			*normalize(t_point *n);
t_point			*normalize_fast(t_point *n);

t_point			*reflect_ray(t_point *l, t_point *n);
float			min3(float a, float b, float c);
float			q_rsqrt(float number );
float			dot_fun(t_point *t1, t_point *t2);
void			*ft_realloc(void *ptr, size_t size, size_t new_size);
int				ft_free(void *ptr);
void			*ft_free2(void *p1, void *p2);
void			*ft_free3(void *p1, void *p2, void *p3);
void			*ft_free4(void *p1, void *p2, void *p3, void *p4);
int				ft_array_size( char **arr);
int				ft_check_rangef(float f, int mi, int ma, char *message);
int				ft_check_rangei(int i, int mi, int ma, char *message);
int				ft_iscomma(int c__);
void			ft_normalize_vect(t_point *p, char *message);
float			tern_f(int cond, float tru, float flse);
int				tern_i(int cond, int tru, int flse);
int				tern_atoi(int cond, int flse, char *str);
float			tern_atof(int cond, float flse, char *str);

void			ft_clean_scene(void);
void			free_spheres(t_sphere **sp, int num);
void			free_planes(t_plane **pl, int num);
void			free_triangles(t_triangle **tr, int num);
void			free_squares(t_square **sq, int num);
void			free_cylinders(t_cylinder **cy, int num);
void			free_circles(t_circle **cr, int num);
void			free_lights(t_light **li, int num);
void			free_cameras(t_camera **cam, int num);

void				key_hook(struct gui_window *window, int keycode, bool pressed);
void			minirt_loop(void);
int				screenshot(const char *fname);
int				ft_close_window(int code, void *_);
int				ft_exit_all(char *message);

int				ft_inside(char c, char *syms);
char			**ft_append(char **src, char *new_el, size_t wc, size_t size);

int				init_scene(void);
int				parce_scene(int fd);
int				switcher(char **splt);
int				ft_set_resolution(char **line);
int				ft_add_ambient(char **line);
int				ft_add_camera(char **line);
int				ft_add_point(char **line);
int				ft_add_direct(char **line);
int				ft_add_sphere(char **line);
int				ft_add_plane(char **line);
int				ft_add_square(char **line);
int				ft_add_cylinder(char **line);
int				ft_add_triangle(char **line);

t_color			*color_str_struct(char *line, float	intensity);
void			ft_line_free(char **line);
int				ft_append_array(void ***array_ptr, size_t wc, size_t size);
t_point			*point_str(char *line);
unsigned int	color_str(char *line);

int				masi2(int *dest1, int source1, int *dest2, int source2);
int				masi1(int *dest, int source);
int				masp2(t_point **dest1, t_point *source1, t_point **dest2,
					t_point *source2);
int				masp1(t_point **dest, t_point *source);
int				masf2(float *dest1, float source1, float *dest2, float source2);
int				masf1(float *dest, float source);

void			object_switcher_0(t_point *o, t_point *d, t_pair *t,
					t_object *closest_object);
void			object_switcher_1(t_point *p, t_object *closest_object,
					t_point *minus_d);
void			object_switcher_2(t_point *p, t_object *closest_object,
					t_point *minus_d);
void			object_switcher_3(t_point *p, t_object *closest_object,
					t_point *minus_d);
float			shadow_switcher_1(t_point *p, t_point *l, float t_max);
float			shadow_switcher_2(t_point *p, t_point *l,
					t_object *closest_object, float t_max);
float			color_switcher(int i, t_point *p, t_point *l);
int				key_switcher_1(int keycode, t_point *n);
int				key_switcher_2(int keycode, t_point *n);
int				key_switcher_3(int keycode, t_point *n);
int				key_switcher_4(int keycode, t_point *n);
int				key_switcher_5(int keycode);

int				do_screenshot(int argc, char **argv);
int				check_extention(char *fname);
void			set_angles(t_camera *new_camera, t_point *view_vector);
t_color			*normalize_colors(t_color *intensity_rgb);

#endif
