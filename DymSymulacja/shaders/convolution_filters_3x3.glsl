//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// GLSL 1.50
//////////////////////////////////////////////////////////////////////
#version 150

//////////////////////////////////////////////////////////////////////
// identyfikatory poszczególnych filtrów splotowych 3x3
//////////////////////////////////////////////////////////////////////
#define NEUTRAL_FILTER               0  // filtr neutralny
#define AVERAGE_FILTER               1  // filtr uœredniaj¹cy
#define LP1_FILTER                   2  // filtr LP1
#define LP2_FILTER                   3  // filtr LP2
#define LP3_FILTER                   4  // filtr LP3
#define GAUSS_FILTER                 5  // filtr Gaussa
#define MEAN_REMOVAL_FILTER          6  // filtr usuwaj¹cy œredni¹
#define HP1_FILTER                   7  // filtr HP1
#define HP2_FILTER                   8  // filtr HP2
#define HP3_FILTER                   9  // filtr HP3
#define HORIZONTAL_FILTER           10  // filtr poziomy
#define VERTICAL_FILTER             11  // filtr pionowy
#define HORIZONTAL_VERTICAL_FILTER  12  // filtr poziomy/pionowy
#define GRADIENT_EAST_FILTER        13  // filtr gradientowy wschód
#define GRADIENT_SOUTH_EAST_FILTER  14  // filtr gradientowy po³udniowy wschód
#define GRADIENT_SOUTH_FILTER       15  // filtr gradientowy po³udnie
#define GRADIENT_SOUTH_WEST_FILTER  16  // filtr gradientowy po³udniowy zachód
#define GRADIENT_WEST_FILTER        17  // filtr gradientowy zachód
#define GRADIENT_NORTH_WEST_FILTER  18  // filtr gradientowy pó³nocny zachód
#define GRADIENT_NORTH_FILTER       19  // filtr gradientowy pó³noc
#define GRADIENT_NORTH_EAST_FILTER  20  // filtr gradientowy pó³nocny wschód
#define EMBOSS_EAST_FILTER          21  // filtr uwypuklaj¹cy wschód
#define EMBOSS_SOUTH_EAST_FILTER    22  // filtr uwypuklaj¹cy po³udniowy wschód
#define EMBOSS_SOUTH_FILTER         23  // filtr uwypuklaj¹cy po³udnie
#define EMBOSS_SOUTH_WEST_FILTER    24  // filtr uwypuklaj¹cy po³udniowy zachód
#define EMBOSS_WEST_FILTER          25  // filtr uwypuklaj¹cy zachód
#define EMBOSS_NORTH_WEST_FILTER    26  // filtr uwypuklaj¹cy pó³nocny zachód
#define EMBOSS_NORTH_FILTER         27  // filtr uwypuklaj¹cy pó³noc
#define EMBOSS_NORTH_EAST_FILTER    28  // filtr uwypuklaj¹cy pó³nocny wschód
#define LAPLACIAN_LAPL1_FILTER      29  // filtr Laplace'a LAPL1
#define LAPLACIAN_LAPL2_FILTER      30  // filtr Laplace'a LAPL2
#define LAPLACIAN_LAPL3_FILTER      31  // filtr Laplace'a LAPL3
#define LAPLACIAN_DIAGONAL_FILTER   32  // filtr Laplace'a skoœny
#define LAPLACIAN_HORIZONTAL_FILTER 33  // filtr Laplace'a poziomy
#define LAPLACIAN_VERTICAL_FILTER   34  // filtr Laplace'a pionowy
#define SOBEL_HORIZONTAL_FILTER     35  // filtr poziomy Sobela
#define SOBEL_VERTICAL_FILTER       36  // filtr pionowy Sobela
#define PREWITT_HORIZONTAL_FILTER   37  // filtr poziomy Prewitta
#define PREWITT_VERTICAL_FILTER     38  // filtr pionowy Prewitta

//////////////////////////////////////////////////////////////////////
// dane poszczególnych filtrów splotowych 3×3
// uwaga: maski filtrów s¹ transponowane, co jest zwi¹zane
// z domyœlnym kolumnowym sposobem inicjacji macierzy w OpenGL)
//////////////////////////////////////////////////////////////////////
const mat3x3 filters[39] = mat3x3[39]
(
    // filtr neutralny, NEUTRAL_FILTER
    mat3x3( 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 0.0 ),

    // filtr uœredniaj¹cy, AVERAGE_FILTER
    mat3x3( 0.11111111, 0.11111111, 0.111111111,
            0.11111111, 0.11111111, 0.111111111,
            0.11111111, 0.11111111, 0.111111111 ),

    // filtr LP1, LP1_FILTER
    mat3x3( 0.1, 0.1, 0.1,
            0.1, 0.2, 0.1,
            0.1, 0.1, 0.1 ),

    // filtr LP2, LP2_FILTER
    mat3x3( 0.08333333, 0.08333333, 0.08333333,
            0.08333333, 0.33333333, 0.08333333,
            0.08333333, 0.08333333, 0.08333333 ),

    // filtr LP3, LP3_FILTER
    mat3x3( 0.05, 0.05, 0.05,
            0.05, 0.6, 0.05,
            0.05, 0.05, 0.05 ),

    // filtr Gaussa, GAUSS_FILTER
    mat3x3( 0.0625, 0.125, 0.0625,
            0.125, 0.25, 0.125,
            0.0625, 0.125, 0.0625 ),

    // filtr usuwaj¹cy œredni¹, MEAN_REMOVAL_FILTER
    mat3x3( -1.0, -1.0, -1.0,
            -1.0,  9.0, -1.0,
            -1.0, -1.0, -1.0 ),

    // filtr HP1, HP1_FILTER
    mat3x3( 0.0, -1.0, 0.0,
            -1.0, 5.0, -1.0,
            0.0, -1.0, 0.0 ),

    // filtr HP2, HP2_FILTER
    mat3x3( 1.0, -2.0, 1.0,
            -2.0, 5.0, -2.0,
            1.0, -2.0, 1.0 ),

    // filtr HP3, HP3_FILTER
    mat3x3( 0.0, -0.0625, 0.0,
            -0.0625, 1.2500, -0.0625,
            0.0, -0.0625, 0.0 ),

    // filtr poziomy, HORIZONTAL_FILTER
    mat3x3( 0.0, -1.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 0.0 ),

    // filtr pionowy, VERTICAL_FILTER
    mat3x3( 0.0, 0.0, 0.0,
            -1.0, 1.0, 0.0,
            0.0, 0.0, 0.0 ),

    // filtr poziomy/pionowy, HORIZONTAL_VERTICAL_FILTER
    mat3x3 ( -1.0, 0.0, 0.0,
             0.0, 1.0, 0.0,
             0.0, 0.0, 0.0 ),

    // filtr gradientowy wschód, GRADIENT_EAST_FILTER
    mat3x3( -1.0, 1.0, 1.0,
            -1.0, -2.0, 1.0,
            -1.0, 1.0, 1.0 ),

    // filtr gradientowy po³udniowy wschód, GRADIENT_SOUTH_EAST_FILTER
    mat3x3( -1.0, -1.0, 1.0,
            -1.0, -2.0, 1.0,
            1.0, 1.0, 1.0 ),

    // filtr gradientowy po³udnie, GRADIENT_SOUTH_FILTER
    mat3x3( -1.0, -1.0, -1.0,
            1.0, -2.0, 1.0,
            1.0, 1.0, 1.0 ),

    // filtr gradientowy po³udniowy zachód, GRADIENT_SOUTH_WEST_FILTER
    mat3x3( 1.0, -1.0, -1.0,
            1.0, -2.0, -1.0,
            1.0, 1.0, 1.0 ),

    // filtr gradientowy zachód, GRADIENT_WEST_FILTER
    mat3x3( 1.0, 1.0, -1.0,
            1.0, -2.0, -1.0,
            1.0, 1.0, -1.0 ),

    // filtr gradientowy pó³nocny zachód, GRADIENT_NORTH_WEST_FILTER
    mat3x3( 1.0, 1.0, 1.0,
            1.0, -2.0, -1.0,
            1.0, -1.0, -1.0 ),

    // filtr gradientowy pó³noc, GRADIENT_NORTH_FILTER
    mat3x3( 1.0, 1.0, 1.0,
            1.0, -2.0, 1.0,
            -1.0, -1.0, -1.0 ),

    // filtr gradientowy pó³nocny wschód, GRADIENT_NORTH_EAST_FILTER
    mat3x3( 1.0, 1.0, 1.0,
            -1.0, -2.0, 1.0,
            -1.0, -1.0, 1.0 ),

    // filtr uwypuklaj¹cy wschód, EMBOSS_EAST_FILTER
    mat3x3( -1.0, 0.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, 0.0, 1.0 ),

    // filtr uwypuklaj¹cy po³udniowy wschód, EMBOSS_SOUTH_EAST_FILTER
    mat3x3( -1.0, -1.0, 0.0,
            -1.0, 1.0, 1.0,
            0.0, 1.0, 1.0 ),

    // filtr uwypuklaj¹cy po³udnie, EMBOSS_SOUTH_FILTER
    mat3x3( -1.0, -1.0, -1.0,
            0.0, 1.0, 0.0,
            1.0, 1.0, 1.0 ),

    // filtr uwypuklaj¹cy po³udniowy zachód, EMBOSS_SOUTH_WEST_FILTER
    mat3x3( 0.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            1.0, 1.0, 0.0 ),

    // filtr uwypuklaj¹cy zachód, EMBOSS_WEST_FILTER
    mat3x3( 1.0, 0.0, -1.0,
            1.0, 1.0, -1.0,
            1.0, 0.0, -1.0 ),

    // filtr uwypuklaj¹cy pó³nocny zachód, EMBOSS_NORTH_WEST_FILTER
    mat3x3( 1.0, 1.0, 0.0,
            1.0, 1.0, -1.0,
            0.0, -1.0, -1.0 ),

    // filtr uwypuklaj¹cy pó³noc, EMBOSS_NORTH_FILTER
    mat3x3( 1.0, 1.0, 1.0,
            0.0, 1.0, 0.0,
            -1.0, -1.0, -1.0 ),

    // filtr uwypuklaj¹cy pó³nocny wschód, EMBOSS_NORTH_EAST_FILTER
    mat3x3( 0.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, 0.0 ),

    // filtr Laplace'a LAPL1, LAPLACIAN_LAPL1_FILTER
    mat3x3( 0.0, -1.0, 0.0,
            -1.0, 4.0, -1.0,
            0.0, -1.0, 0.0 ),

    // filtr Laplace'a LAPL2, LAPLACIAN_LAPL2_FILTER
    mat3x3( -1.0, -1.0, -1.0,
            -1.0, 8.0, -1.0,
            -1.0, -1.0, -1.0 ),

    // filtr Laplace'a LAPL3, LAPLACIAN_LAPL3_FILTER
    mat3x3( 1.0, -2.0, 1.0,
            -2.0, 4.0, -2.0,
            1.0, -2.0, 1.0 ),

    // filtr Laplace'a skoœny, LAPLACIAN_DIAGONAL_FILTER
    mat3x3( -1.0, 0.0, -1.0,
            0.0, 4.0, 0.0,
            -1.0, 0.0, -1.0 ),

    // filtr Laplace'a poziomy, LAPLACIAN_HORIZONTAL_FILTER
    mat3x3( 0.0, -1.0, 0.0,
            0.0, 2.0, 0.0,
            0.0, -1.0, 0.0 ),

    // filtr Laplace'a pionowy, LAPLACIAN_VERTICAL_FILTER
    mat3x3( 0.0, 0.0, 0.0,
            -1.0, 2.0, -1.0,
            0.0, 0.0, 0.0 ),

    // filtr poziomy Sobela, SOBEL_HORIZONTAL_FILTER
    mat3x3( 1.0, 2.0, 1.0,
            0.0, 0.0, 0.0,
            -1.0, -2.0, -1.0 ),

    // filtr pionowy Sobela, SOBEL_VERTICAL_FILTER
    mat3x3( 1.0, 0.0, -1.0,
            2.0, 0.0, -2.0,
            1.0, 0.0, -1.0 ),

    // filtr poziomy Prewitta, PREWITT_HORIZONTAL_FILTER
    mat3x3( -1.0, -1.0, -1.0,
            0.0, 0.0, 0.0,
            1.0, 1.0, 1.0 ),

    // filtr pionowy Prewitta, PREWITT_VERTICAL_FILTER
    mat3x3( 1.0, 0.0, -1.0,
            1.0, 0.0, -1.0,
            1.0, 0.0, -1.0 )
);

//////////////////////////////////////////////////////////////////////
// funkcja zwracaj¹ca maskê filtra 3×3
//////////////////////////////////////////////////////////////////////
mat3x3 Filter3x3( const int filter )
{
    if( filter >= NEUTRAL_FILTER && filter <= PREWITT_VERTICAL_FILTER )
        return filters[filter];
    else
        return filters[NEUTRAL_FILTER];
}
