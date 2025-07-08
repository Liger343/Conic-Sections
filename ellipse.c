#include <stdio.h>
#include <math.h>
#include <string.h>

struct Ellipse
{
    char general_equation [100]; //User Inputted General Equation
    char standard_equation [100]; // User Inputted Standard Equation
    char ellipse_direction [100]; //Direction of Ellipse for Standard Form Input

    float A, C, D, E, F; //Ax^2 + Cy^2 + Dx + Ey + F = 0
    float discriminant; //Discriminant of Ellipse: B^2 - 4AC
    float numerator; //Numerator for a^2 and b^2 to simplify calculations
    float a_2, b_2, c_2; //Variables for a^2, b^2, and c^2
    float a, b, c; //Variables for a, b, and c
    float e; //Eccentricity of Ellipse
    
    float h, k; //Coordinates of Center: (h, k)
    float f1x, f1y, f2x, f2y; //Coordinates of 2 Foci
    float v1x, v1y, v2x, v2y; //Coordinates of 2 Vertices
    float cv1x, cv1y, cv2x, cv2y; //Coordinates of 2 Co-Vertices
    float maj_axis, min_axis, focal_length; //Length of Major and Minor Axes as well as Focal Length
    float semi_maj_axis, semi_min_axis; //Length of Semi - Major and Semi - Minor Axes
    float d1, d2; //Directrix 1 and Directrix 2
    float lr1, lr2; //Latus Rectum 1 and Latus Rectum 2
    float focal_width; //Length of Latus Rectum 1 and 2 (Latera Recta)

    int final_solution; //Check the type of solution user inputted for appropriate display 

    //Method 1: Center + Foci + Vertices
    char center[100]; //Center
    char foci[100]; //Foci
    char vertices[100]; //Vertices

    float foci_highest; //Highest Number for Foci Input
    float foci_lowest; //Lowest Number for Foci Input
    float vertices_highest; //Highest Number for Vertices Input
    float vertices_lowest; //Lowest Number for Vertices Input

    int solution_type; //Type of Solution to calculate Standard and General Form as well as Missing Parameters
    int restart; //Ask if user wants to restart their whole inputted data

    //Method 2: Vertices + Co-vertices
    char covertices[100]; //Co-vertices
    float h_vertices, h_covertices; //x-coordinates of center via vertices and co-vertices
    float k_vertices, k_covertices; //y-coordinates of center via vertices and co-vertices

    //Method 3: Domain and Range + Foci
    char domain[100]; //Domain
    char range[100]; //Range
    char opening_bracket [2], closing_bracket [2]; //Brackets for Domain and Range []
    float domain_endpoint1, domain_endpoint2; //Domain Endpoints 1 and 2 
    float range_endpoint1, range_endpoint2; //Range Endpoints 1 and 2
    float h_foci, k_foci; //Coordinates of Center using Foci 
    float h_domain, k_range; //Coordinates of Center using Domain and Range

    //Method 4: Derivative of Ellipse + 2 Points on Ellipse
    char derivative [100]; //Derivative of Ellipse (User Input)
    char point_ellipse[100]; //Point on Ellipse -> P: (x, y)
    float coefficient_x, coefficient_y, constant_D, constant_E; //Coefficients of Variables: x and y and constants D and E in derivative of ellipse: dy/dx = -2Ax - D / 2Cy + E
    float neg_constant_D; //Value of Constant 1 in derivative of ellipse: -D
    float Point_x, Point_y; //Coordinates of Point on Ellipse
    float derivative_denominator; //Variable to check value of denominator when value of y in Solution is implemented -> Cannot be Zero strictly

    //Method 5: Values of E & F + 3 Points on the Ellipse
    char Point1[100], Point2[100], Point3[100]; //Variables to Input full Points
    char constants[100]; //Variable to Input Equivalent Values of 1st, 2nd, and 3rd Equations 
    float Point1_x, Point1_y; //P1: (X1, Y1) -> Extract coordinates from Point1 
    float Point2_x, Point2_y; //P2: (X2, Y2) -> Extract coordinates from Point2
    float Point3_x, Point3_y; //P3: (X3, Y3) -> Extract coordinates from Point3
    float system_coefficients[3][3]; //Matrix to store coefficients of equations in system
    float matrix_A[3][3], matrix_C[3][3], matrix_D[3][3]; //Matrices to be used for getting determinant for solving unknown values of A, C, and D respectively
    float A_1, B_1, C_1; //Coefficients of 1st Equation
    float A_2, B_2, C_2; //Coefficients of 2nd Equation
    float A_3, B_3, C_3; //Coefficients of 3rd Equation
    float constant_1, constant_2, constant_3; //Equivalent Value of 1st, 2nd, and 3rd Equations respectively
    float determinant; //Determinant of Matrix
    float determinant_A, determinant_C, determinant_D; //Determinant for the Matrices of unknowns A, C, and D
    float constant; //Right Hand Side unsimplified constant

};

void ellipse_equation (struct Ellipse *ellipse, int input_equation)
{
    if (input_equation == 1)
    {
        ellipse_direction:
        printf("Enter Direction of Ellipse: ");
        scanf("%s", ellipse->ellipse_direction);
        getchar();

        if (strcasecmp(ellipse->ellipse_direction, "Vertical") == 0)
        {
            while (1)
            {
                printf("Enter Values for h, k, a^2 and b^2: ");
                fgets(ellipse->standard_equation, sizeof(ellipse->standard_equation), stdin);
                ellipse->standard_equation[strcspn(ellipse->standard_equation, "\n")] = '\0';

                if (sscanf(ellipse->standard_equation, "%f %f %f %f", &ellipse->h, &ellipse->k, &ellipse->a_2, &ellipse->b_2) == 4)
                {
                    if (ellipse->a_2 > ellipse->b_2)
                    {
                        ellipse->c_2 = ellipse->a_2 - ellipse->b_2;
                        
                        ellipse->a = sqrt(ellipse->a_2);
                        ellipse->b = sqrt(ellipse->b_2);
                        ellipse->c = sqrt(ellipse->c_2);

                        ellipse->e = sqrt(1 - pow(ellipse->b, 2) / pow(ellipse->a, 2));

                        ellipse->f1x = ellipse->h;
                        ellipse->f1y = ellipse->k - ellipse->c;
                        ellipse->f2x = ellipse->h;
                        ellipse->f2y = ellipse->k + ellipse->c;

                        ellipse->v1x = ellipse->h;
                        ellipse->v1y = ellipse->k - ellipse->a;
                        ellipse->v2x = ellipse->h;
                        ellipse->v2y = ellipse->k + ellipse->a;

                        ellipse->cv1x = ellipse->h - ellipse->b;
                        ellipse->cv1y = ellipse->k;
                        ellipse->cv2x = ellipse->h + ellipse->b;
                        ellipse->cv2y = ellipse->k;

                        ellipse->maj_axis = 2*ellipse->a;
                        ellipse->min_axis = 2*ellipse->b;
                        ellipse->focal_length = 2*ellipse->c;
                        ellipse->semi_maj_axis = ellipse->a;
                        ellipse->semi_min_axis = ellipse->b;

                        ellipse->d1 = ellipse->k - pow(ellipse->a, 2) / ellipse->c;
                        ellipse->d2 = ellipse->k + pow(ellipse->a, 2) / ellipse->c;

                        ellipse->lr1 = ellipse->k - ellipse->c;
                        ellipse->lr2 = ellipse->k + ellipse->c;

                        ellipse->focal_width = 2*pow(ellipse->b, 2)/ellipse->a;
                        break;
                    }
                    else
                    {
                        printf("Invalid! a^2 is always bigger than b^2\n");
                    }
                }
                else
                {
                    printf("Incomplete Information!\n");
                }
            }
        }
        else if (strcasecmp(ellipse->ellipse_direction, "Horizontal") == 0)
        {
            while (1)
            {
                printf("Enter Values for h, k, a^2 and b^2: ");
                fgets(ellipse->standard_equation, sizeof(ellipse->standard_equation), stdin);
                ellipse->standard_equation[strcspn(ellipse->standard_equation, "\n")] = '\0';

                if (sscanf(ellipse->standard_equation, "%f %f %f %f", &ellipse->h, &ellipse->k, &ellipse->a_2, &ellipse->b_2) == 4)
                {
                    if (ellipse->a_2 > ellipse->b_2)
                    {
                        ellipse->c_2 = ellipse->a_2 - ellipse->b_2;
                        ellipse->a = sqrt(ellipse->a_2);
                        ellipse->b = sqrt(ellipse->b_2);
                        ellipse->c = sqrt(ellipse->c_2);

                        ellipse->e = sqrt(1 - ellipse->b_2/ellipse->a_2);
                      
                        ellipse->f1x = ellipse->h - ellipse->c;
                        ellipse->f1y = ellipse->k;
                        ellipse->f2x = ellipse->h + ellipse->c;
                        ellipse->f2y = ellipse->k;

                        ellipse->v1x = ellipse->h - ellipse->a;
                        ellipse->v1y = ellipse->k;
                        ellipse->v2x = ellipse->h + ellipse->a;
                        ellipse->v2y = ellipse->k;

                        ellipse->cv1x = ellipse->h;
                        ellipse->cv1y = ellipse->k - ellipse->b;
                        ellipse->cv2x = ellipse->h;
                        ellipse->cv2y = ellipse->k + ellipse->b;

                        ellipse->maj_axis = 2*ellipse->a;
                        ellipse->min_axis = 2*ellipse->b;
                        ellipse->focal_length = 2*ellipse->c;
                        ellipse->semi_maj_axis = ellipse->a;
                        ellipse->semi_min_axis = ellipse->b;

                        ellipse->d1 = ellipse->h - ellipse->a_2 / ellipse->c;
                        ellipse->d2 = ellipse->h + ellipse->a_2 / ellipse->c;

                        ellipse->lr1 = ellipse->h - ellipse->c;
                        ellipse->lr2 = ellipse->h + ellipse->c;

                        ellipse->focal_width = 2*pow(ellipse->b, 2)/ ellipse->a;
                        break;
                    }
                    else
                    {
                        printf("Invalid! a^2 is always bigger than b^2\n");
                    }
                }
                else
                {
                    printf("Incomplete Information!\n");
                }


            }
        }
        else
        {
            printf("Invalid Direction!\n");
            goto ellipse_direction;
        }
    }

    else if (input_equation == 2)
    {   
        generalform_input:
        printf("Enter Coefficients for A, C, D, E, F: ");
        fgets(ellipse->general_equation, sizeof(ellipse->general_equation), stdin);
        ellipse->general_equation[strcspn(ellipse->general_equation, "\n")] = '\0';
    
        if (sscanf(ellipse->general_equation, "%f %f %f %f %f", &ellipse->A, &ellipse->C, &ellipse->D, &ellipse->E, &ellipse->F) == 5)
        {
            if (ellipse->A > ellipse->C && ellipse->A > 0 && ellipse->C > 0) //Vertical Ellipse
            {
                ellipse->numerator = (4*ellipse->C*pow(ellipse->D, 2) + 4*ellipse->A*pow(ellipse->E, 2) - 16*ellipse->A*ellipse->C*ellipse->F)/(16*ellipse->A*ellipse->C); //4CD^2 + 4AE^2 - 16ACF / (16AC)
                ellipse->a_2 = ellipse->numerator / ellipse->C;
                ellipse->b_2 = ellipse->numerator / ellipse->A;
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

                 if (ellipse->a_2 < 0 || ellipse->b_2 < 0)
                {
                    printf("Invalid Ellipse!\n");
                    goto generalform_input;
                }
                
                ellipse->a = sqrt(ellipse->a_2);
                ellipse->b = sqrt(ellipse->b_2);
                ellipse->c = sqrt(ellipse->c_2);

                ellipse->h = -ellipse->D / (2*ellipse->A);
                ellipse->k = -ellipse->E / (2*ellipse->C);

                ellipse->f1x = ellipse->h;
                ellipse->f1y = ellipse->k - ellipse->c;
                ellipse->f2x = ellipse->h;
                ellipse->f2y = ellipse->k + ellipse->c;

                ellipse->v1x = ellipse->h;
                ellipse->v1y = ellipse->k - ellipse->a;
                ellipse->v2x = ellipse->h;
                ellipse->v2y = ellipse->k + ellipse->a;

                ellipse->cv1x = ellipse->h - ellipse->b;
                ellipse->cv1y = ellipse->k;
                ellipse->cv2x = ellipse->h + ellipse->b;
                ellipse->cv2y = ellipse->k;

                ellipse->maj_axis = 2*ellipse->a;
                ellipse->min_axis = 2*ellipse->b;
                ellipse->focal_length = 2*ellipse->c;
                ellipse->semi_maj_axis = ellipse->a;
                ellipse->semi_min_axis = ellipse->b;

                ellipse->d1 = ellipse->k - pow(ellipse->a, 2) / ellipse->c;
                ellipse->d2 = ellipse->k + pow(ellipse->a, 2) / ellipse->c;
                
                ellipse->lr1 = ellipse->k - ellipse->c;
                ellipse->lr2 = ellipse->k + ellipse->c;

                ellipse->focal_width = (2*pow(ellipse->b, 2))/(ellipse->a);

            }
            else if (ellipse-> A < ellipse->C && ellipse->A > 0 && ellipse->C > 0) //Horizontal Ellipse
            {
                ellipse->numerator = (4*ellipse->C*pow(ellipse->D, 2) + 4*ellipse->A*pow(ellipse->E, 2) - 16*ellipse->A*ellipse->C*ellipse->F)/(16*ellipse->A*ellipse->C); //4CD^2 + 4AE^2 - 16ACF / (16AC)
                ellipse->a_2 = ellipse->numerator / ellipse->A;
                ellipse->b_2 = ellipse->numerator / ellipse->C;

                if (ellipse->a_2 < 0 || ellipse->b_2 < 0)
                {
                    printf("Invalid Ellipse!\n");
                    goto generalform_input;
                }
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;
                ellipse->a = sqrt(ellipse->a_2);
                ellipse->b = sqrt(ellipse->b_2);
                ellipse->c = sqrt(ellipse->c_2);

                ellipse->h = -ellipse->D/(2*ellipse->A);
                ellipse->k = -ellipse->E/(2*ellipse->C);

                ellipse->f1x = ellipse->h - ellipse->c;
                ellipse->f1y = ellipse->k;
                ellipse->f2x = ellipse->h + ellipse->c;
                ellipse->f2y = ellipse->k; 
                ellipse->v1x = ellipse->h - ellipse->a;
                ellipse->v1y = ellipse->k;
                ellipse->v2x = ellipse->h + ellipse->a;
                ellipse->v2y = ellipse->k;
                ellipse->cv1x = ellipse->h;
                ellipse->cv1y = ellipse->k - ellipse->b;
                ellipse->cv2x = ellipse->h;
                ellipse->cv2y = ellipse->k + ellipse->b; 

                ellipse->maj_axis = 2*ellipse->a;
                ellipse->min_axis = 2*ellipse->b;
                ellipse->focal_length = 2*ellipse->c;
                ellipse->semi_maj_axis = ellipse->a;
                ellipse->semi_min_axis = ellipse->b;

                ellipse->d1 = ellipse->h - pow(ellipse->a, 2) / ellipse->c;
                ellipse->d2 = ellipse->h + pow(ellipse->a, 2) / ellipse->c;

                ellipse->lr1 = ellipse->h - ellipse->c;
                ellipse->lr2 = ellipse->h + ellipse->c;

                ellipse->focal_width = 2*pow(ellipse->b, 2) / ellipse->a;
            }
            
            else
            {
                printf("Invalid Ellipse!\n");
                goto generalform_input;
            }
        }
        else
        {
            printf("Incomplete Information!\n");
            goto generalform_input;
        }
    }
}

void ellipse_parameter (struct Ellipse *ellipse)
{
    ellipse->solution_type = 0;
    int loop_check = 0; //Stop Direction Input loop if data is valid
    int center_check = 0; //Stop Center Input loop if data is valid
    int foci_check = 0; //Stop Foci Input loop if data is valid
    int vertices_check = 0; //Stop Vertices Input loop if data is valid
    int covertices_check = 0; //Stop Covertices Input loop if data is valid
    int domain_check = 0; //Stop Domain Input loop if data is valid
    int range_check = 0; //Stop Range Input loop if data is valid
    int pointderivative_check = 0; //Stop Solution to Derivative Input loop if data is valid (Method 4)
    int derivative_check = 0; //Stop Derivative Input loop if data is valid (Method 4)
    int point_check = 0; //Stop Point on Ellipse Input if data is valid (Method 4)
    char methods[5][100] = {"Center + Foci + Vertices", "Vertices + Co - Vertices", "Domain and Range + Foci", "Derivative of Ellipse + Point on Ellipse", "Values of E & F + 3 Point on Ellipse"};

    for (int z = 0; z < 5; z++)
    {
        printf("Solution [%d]: %s\n", z+1, methods[z]);
    }
    
    for (int k = 0; ellipse->solution_type == 0; k++)
    {   
        printf("Enter Method [1-5]: ");
        scanf("%d", &ellipse->final_solution);
        getchar();

        if (ellipse->final_solution >= 1 || ellipse->final_solution <= 5)
        {
            ellipse->solution_type = 1;
        }
    }
    
    if (ellipse->final_solution == 1)
    {
        ellipse_input:
        while (!loop_check)
        {   
            printf("Enter Direction [Horizontal] [Vertical]: ");
            fgets(ellipse->ellipse_direction, sizeof(ellipse->ellipse_direction), stdin);
            ellipse->ellipse_direction[strcspn(ellipse->ellipse_direction, "\n")] = '\0';

            if (strcasecmp(ellipse->ellipse_direction, "Vertical") == 0)
            {
                loop_check = 1;
            }
            else if (strcasecmp(ellipse->ellipse_direction, "Horizontal") == 0)
            {
                loop_check = 1;
            }
        }
        
        if (strcasecmp(ellipse->ellipse_direction, "Vertical") == 0) //Vertical Ellipse
        {
            while (!center_check)
            {
                while (!foci_check)
                {
                    while (!vertices_check)
                    {
                        printf("Enter Vertices [x1, y1, x2, y2]: ");
                        fgets(ellipse->vertices, sizeof(ellipse->vertices), stdin);
                        ellipse->vertices[strcspn(ellipse->vertices, "\n")] = '\0';

                        if (sscanf(ellipse->vertices, "%f %f %f %f", &ellipse->v1x, &ellipse->v1y, &ellipse->v2x, &ellipse->v2y) == 4)
                        {
                            if (ellipse->v1x == ellipse->v2x && ellipse->v1y != ellipse->v2y)
                            {

                                float difference_vertices = ellipse->v2y - ellipse->v1y;
                                
                                if (difference_vertices < 0)
                                {
                                    float temporary_vertex = ellipse->v1y;
                                    ellipse->v1y = ellipse->v2y;
                                    ellipse->v2y = temporary_vertex;
                                }
                                vertices_check = 1;
                            }
                            else
                            {
                                printf("Invalid Vertices!\n");
                            }
                        }
                        else
                        {
                            printf("Incomplete Vertices Information!\n");
                        }
                    } //End of Vertices Loop
                
                    printf("Enter Foci [x1, y1, x2, y2]: ");
                    fgets(ellipse->foci, sizeof(ellipse->foci), stdin);
                    ellipse->foci[strcspn(ellipse->foci, "\n")] = '\0';

                    if (sscanf(ellipse->foci, "%f %f %f %f", &ellipse->f1x, &ellipse->f1y, &ellipse->f2x, &ellipse->f2y) == 4)
                    {
                        if (ellipse->f1x == ellipse->f2x && ellipse->f1y != ellipse->f2y) //Condition 1: Foci have equal x-coordinates
                        {
                            if (ellipse->f1x == ellipse->v1x && ellipse->f1x == ellipse->v2x && ellipse->f2x == ellipse->v1x && ellipse->f2x == ellipse->v2x) //Condition 2: Foci and Vertices have equal x-coordinates
                            {
                                float difference_foci = ellipse->f2y - ellipse->f1y;
                            
                                if (difference_foci < 0)
                                {
                                    float temporary_foci = ellipse->f1y;
                                    ellipse->f1y = ellipse->f2y;
                                    ellipse->f2y = temporary_foci;
                                }
                            
                                if (ellipse->f1y > ellipse->v1y && ellipse->f2y < ellipse->v2y) //Condition 3: Y - coordinates of Foci are within the y - coordinates of Vertices
                                {
                                    foci_check = 1;
                                }
                                else
                                {
                                    printf("Invalid Foci!\n");
                                }
                            }
                            else
                            {
                                printf("Invalid Foci!\n");
                            }
                        }
                        else
                        {
                            printf("Invalid Foci!\n");
                        }
                    }
                    else
                    {
                        printf("Incomplete Foci Information!\n");
                    }
                } //End of Foci Loop
                
                ellipse_center: 
                printf("Enter Coordinates of Center [h, k]: ");
                fgets(ellipse->center, sizeof(ellipse->center), stdin);
                ellipse->center[strcspn(ellipse->center, "\n")] = '\0';

                if (sscanf(ellipse->center, "%f %f", &ellipse->h, &ellipse->k) == 2)
                {
                    if (ellipse->h == ellipse->f1x && ellipse->h == ellipse->f2x && ellipse->h == ellipse->v1x && ellipse->h == ellipse->v2x) //Condition 1: x-coordinate of center is equal to x-coordinates of Foci and Vertices
                    {
                        if (ellipse->k == (ellipse->f1y + ellipse->f2y) / 2 && ellipse->k == (ellipse->v1y + ellipse->v2y) / 2) //Condition 2: y-coordinate of center is equal to the midpoint of the y-coordinates of the Foci and Vertices
                        {
                            center_check = 1;
                        }
                        else
                        {
                            do
                            {
                                ellipse->restart = 0;
                                printf("Invalid Parameters!\n");
                                printf("Would you like to restart your input [1] Yes [2] No: ");
                                scanf("%d", &ellipse->restart);
                                getchar();
                            
                            } while (ellipse->restart != 1 && ellipse->restart != 2);

                            switch (ellipse->restart)
                            {
                                case 1:
                                center_check = 0;
                                foci_check = 0;
                                vertices_check = 0;
                                goto ellipse_input;
                                break;

                                case 2:
                                printf("");
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid Center!\n");
                    }
                }
                else
                {
                    printf("Incomplete Information ");
                }
            } //End of Center Loop
        } //End of Vertical Ellipse Input

        else if (strcasecmp(ellipse->ellipse_direction, "Horizontal") == 0)
        {
            while (!center_check)
            {
                while (!foci_check)
                {
                    while (!vertices_check)
                    {
                        printf("Enter Vertices [x1, y1, x2, y2]: ");
                        fgets(ellipse->vertices, sizeof(ellipse->vertices), stdin);
                        ellipse->vertices[strcspn(ellipse->vertices, "\n")] = '\0';

                        if (sscanf(ellipse->vertices, "%f %f %f %f", &ellipse->v1x, &ellipse->v1y, &ellipse->v2x, &ellipse->v2y) == 4)
                        {
                            if (ellipse->v1x != ellipse->v2x && ellipse->v1y == ellipse->v2y) //Vertex Condition 1: x-coordinates of vertices are different, y-coordinates of vertices are equal
                            {
                                float difference_vertices = ellipse->v2x - ellipse->v1x; //Determine the bigger number: difference_vertices > 0 if ellipse->v2x > ellipse->v1x, difference_vertices < 0 if ellipse->v1x > ellipse->v2x
                                if (difference_vertices < 0)
                                {
                                    float temporary_vertices = ellipse->v1x;
                                    ellipse->v1x = ellipse->v2x;
                                    ellipse->v2x = temporary_vertices;
                                }
                                vertices_check = 1;
                            }
                            else
                            {
                                printf("Invalid Vertices!\n");
                            }
                        }
                        else
                        {
                            printf("Incomplete Vertices Information!\n");
                        }
                    } //End of Vertices Loop

                    printf("Enter Foci [x1, y1, x2, y2]: ");
                    fgets(ellipse->vertices, sizeof(ellipse->vertices), stdin);
                    ellipse->vertices[strcspn(ellipse->vertices, "\n")] = '\0';

                    if (sscanf(ellipse->vertices, "%f %f %f %f", &ellipse->f1x, &ellipse->f1y, &ellipse->f2x, &ellipse->f2y) == 4)
                    {
                        if (ellipse->f1x != ellipse->f2x) //Foci Condition 1: x-coordinates of Foci are different
                        {
                            if (ellipse->f1y == ellipse->f2y) //Foci Condition 2: y-coordinates of Foci are equal
                            {
                                float differences_foci = ellipse->f2x - ellipse->f1x; //Determine the bigger number: difference_foci > 0 if ellipse->f2x > ellipse->f1x, difference_foci < 0 if ellipse->f1x > ellipse->f2x
                                if (differences_foci < 0)
                                {
                                    float temporary_foci = ellipse->f1x;
                                    ellipse->f1x = ellipse->f2x;
                                    ellipse->f2x = temporary_foci;
                                }

                                if (ellipse->f1x > ellipse->v1x && ellipse->f2x < ellipse->v2x) //Foci Condition 3: x-coordinates of Foci are within the range of x-coordinates of the vertices
                                {
                                    foci_check = 1;
                                }
                                else
                                {
                                    printf("Invalid Foci!\n");
                                }
                            }
                            else
                            {
                                printf("Invalid Foci!\n");
                            }
                        }
                        else
                        {
                            printf("Invalid Foci!\n");
                        }
                    }
                    else
                    {
                        printf("Incomplete Foci Information!\n");
                    }
                } //End of Foci Loop
                printf("Enter Center (h, k): ");
                fgets(ellipse->center, sizeof(ellipse->center), stdin);
                ellipse->center[strcspn(ellipse->center, "\n")] = '\0';
                
                if (sscanf(ellipse->center, "%f %f", &ellipse->h, &ellipse->k) == 2)
                {
                    if (ellipse->k == ellipse->f1y && ellipse->k == ellipse->f2y && ellipse->k == ellipse->v1y && ellipse->k == ellipse->v2y) //Center Condition 1: y-coordinate of Center is equal to the y - coordinates of the Foci and Vertices
                    {
                        if (ellipse->h == (ellipse->f1x + ellipse->f2x) / 2 && ellipse->h == (ellipse->v1x + ellipse->v2x) == 2) //Center Condition 2: x-coordinate of Center is the midpoint of the Foci and Vertices
                        {
                            center_check = 1;
                        }
                        else
                        {
                            do
                            {
                                ellipse->restart = 0;
                                printf("Would you like to restart your whole input [1] Yes [2] No: ");
                                scanf("%d", &ellipse->restart);
                                getchar();
                            
                            } while (ellipse->restart != 1 && ellipse->restart != 2);

                            switch (ellipse->restart)
                            {
                                case 1:
                                center_check = 0;
                                foci_check = 0;
                                vertices_check = 0;
                                goto ellipse_input;
                                break;

                                case 2:
                                break;
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid Center!\n");
                    }
                }
                else
                {
                    printf("Incomplete Center Information!\n");
                }
            } //End of Center Loop
        }
        
        if (ellipse->h == (ellipse->f1x + ellipse->f2x) / 2 && ellipse->h == (ellipse->v1x + ellipse->v2x) / 2 || ellipse->k == (ellipse->f1y + ellipse->f2y) / 2 && ellipse->k == (ellipse->v1y + ellipse->v2y) / 2)
        {
            printf("Parameters Acquired: \n");
            printf("|Center: (%.2f, %.2f) || Foci: (%.2f, %.2f) & (%.2f, %.2f) || Vertices (%.2f, %.2f) & (%.2f, %.2f)|\n", ellipse->h, ellipse->k, ellipse->f1x, ellipse->f1y, ellipse->f2x, ellipse->f2y, ellipse->v1x, ellipse->v1y, ellipse->v2x, ellipse->v2y);

            if (ellipse->h == ellipse->f1x && ellipse->h == ellipse->f2x && ellipse->h == ellipse->v1x && ellipse->h == ellipse->v2x) //Vertical Ellipse
            {   
                ellipse->a = sqrt(pow(ellipse->v2y - ellipse->v1y, 2))/2;
                ellipse->c = sqrt(pow(ellipse->f2y - ellipse->f1y, 2))/2;
                ellipse->a_2 = pow(ellipse->a, 2);
                ellipse->c_2 = pow(ellipse->c, 2);
                ellipse->b_2 = ellipse->a_2 - ellipse->c_2;
                ellipse->b = sqrt(ellipse->b_2);

                ellipse->cv1x = ellipse->h - ellipse->b;
                ellipse->cv1y = ellipse->k;
                ellipse->cv2x = ellipse->h + ellipse->b;
                ellipse->cv2y = ellipse->k;

                ellipse->maj_axis = 2*ellipse->a;
                ellipse->min_axis = 2*ellipse->b;
                ellipse->focal_length = 2*ellipse->c;
                ellipse->semi_maj_axis = ellipse->a;
                ellipse->semi_min_axis = ellipse->b;
                
                ellipse->d1 = ellipse->k - ellipse->a_2/ellipse->c;
                ellipse->d2 = ellipse->k + ellipse->a_2/ellipse->c;

                ellipse->lr1 = ellipse->k - ellipse->c;
                ellipse->lr2 = ellipse->k + ellipse->c;
                ellipse->focal_width = 2*ellipse->b_2/ellipse->a;

                //General Form Solution

                ellipse->A = ellipse->b_2;
                ellipse->C = ellipse->a_2;
                ellipse->D = -2*ellipse->b_2*ellipse->h;
                ellipse->E = -2*ellipse->a_2*ellipse->k;
                ellipse->F = ellipse->b_2 * pow(ellipse->h, 2) + ellipse->a_2 * pow(ellipse->k, 2) - ellipse->a_2*ellipse->b_2;

            }
            else if (ellipse->k == ellipse->f1y && ellipse->k == ellipse->f2y && ellipse->k == ellipse->v1y && ellipse->k == ellipse->v2y) //Horizontal Ellipse
            {
                ellipse->a = (ellipse->v2x - ellipse->v1x) / 2;
                ellipse->c = (ellipse->f2x - ellipse->f1x) / 2;
                ellipse->a_2 = pow(ellipse->a, 2);
                ellipse->c_2 = pow(ellipse->c, 2);
                ellipse->b_2 = ellipse->a_2 - ellipse->c_2;
                ellipse->b = sqrt(ellipse->b_2);

                ellipse->cv1x = ellipse->k - ellipse->b;
                ellipse->cv1y = ellipse->h;
                ellipse->cv2x = ellipse->k + ellipse->b;
                ellipse->cv2y = ellipse->h;
            }
        }
        else
        {
            //Reinitialization of Checkers from stored values of 1 to 0 to satisfy nested loops conditions
            center_check = 0; 
            foci_check = 0;
            vertices_check = 0;
            goto ellipse_input;
        }
        
    } //End of Method 1: Center + Foci + Vertices

    else if (ellipse->final_solution == 2)
    {
        while (!vertices_check)
        {
            ellipse_coverticesinput:
            while (!covertices_check)
            {
                printf("Enter Covertices [x1, y1, x2, y2]: ");
                fgets(ellipse->covertices, sizeof(ellipse->covertices), stdin);
                ellipse->covertices[strcspn(ellipse->covertices, "\n")] = '\0';

                if (sscanf(ellipse->covertices, "%f %f %f %f", &ellipse->cv1x, &ellipse->cv1y, &ellipse->cv2x, &ellipse->cv2y) == 4)
                {
                    if (ellipse->cv1y == ellipse->cv2y) //Condition 1 [Vertical Ellipse]: y-coordinates of co-vertices are equal
                    {
                        if (ellipse->cv1x != ellipse->cv2x) //Condition 2 [Vertical Ellipse]: x-coordinates of co-vertices are not equal
                        {
                            float difference_covertices = ellipse->cv2x - ellipse->cv1x; //check which of the 2 x-coordinates are bigger in the inputted co-vertices, difference_covertices < 0 if ellipse->cv1x > ellipse->cv2x , difference_covertices > 0 if ellipse->cv2x > ellipse->cv1x

                            if (difference_covertices < 0)
                            {
                                float temporary_covertices = ellipse->cv1x;
                                ellipse->cv1x = ellipse->cv2x;
                                ellipse->cv2x = temporary_covertices;
                            }

                            covertices_check = 1;
                        }
                        else
                        {
                            printf("Invalid Data!\n");
                            covertices_check = 0;
                            goto ellipse_coverticesinput;
                        }
                    }
                    else if (ellipse->cv1x == ellipse->cv2x) //Horizontal Ellipse
                    {
                        if (ellipse->cv1x == ellipse->cv2x) //Condition 1 [Horizontal Ellipse]: x-coordinates of co-vertices are equal
                        {
                            if (ellipse->cv1y != ellipse->cv2y) //Condition 2 [Horizontal Ellipse]: y-coordinates of co-vertices are not equal
                            {
                                float difference_covertices = ellipse->cv2y - ellipse->cv1y;

                                if (difference_covertices < 0)
                                {
                                    float temporary_covertices = ellipse->cv1y;
                                    ellipse->cv1y = ellipse->cv2y;
                                    ellipse->cv2y = temporary_covertices;
                                }

                                covertices_check = 1;
                            }
                            else
                            {
                                printf("Invalid Data!\n");
                                covertices_check = 0;
                                goto ellipse_coverticesinput;
                            }
                        }
                        else
                        {
                            printf("Invalid Data!\n");
                            covertices_check = 0;
                            goto ellipse_coverticesinput;
                        }
                    }
                    else
                    {
                        printf("Invalid Data!\n");
                        covertices_check = 0;
                        goto ellipse_coverticesinput;
                    }   
                }
                else
                {
                    printf("Incomplete Information!\n");
                }   
            } //End of Co-vertices Input Loop

            printf("Enter Vertices [x1, y1, x2, y2]: ");
            fgets(ellipse->vertices, sizeof(ellipse->vertices), stdin);
            ellipse->vertices[strcspn(ellipse->vertices, "\n")] = '\0';

            if (sscanf(ellipse->vertices, "%f %f %f %f", &ellipse->v1x, &ellipse->v1y, &ellipse->v2x, &ellipse->v2y) == 4) //Check if Vertices input is complete
            {
                if (ellipse->v1x == ellipse->v2x && ellipse->v1y != ellipse->v2y) //Condition [Vertical Ellipse]: x-coordinates of vertices are equal, y-coordinates of vertices are not equal
                {
                    float difference_vertices = ellipse->v2y - ellipse->v1y;
                        
                    if (difference_vertices < 0)
                    {
                        float temporary_vertices = ellipse->v1y;
                        ellipse->v1y = ellipse->v2y;
                        ellipse->v2y = temporary_vertices;
                    }
                    //Calculations for Final Check of Co-vertices and Vertices
                    ellipse->h_vertices = (ellipse->v1x + ellipse->v2x) / 2;
                    ellipse->k_vertices = (ellipse->v1y + ellipse->v2y) / 2;

                    ellipse->h_covertices = (ellipse->cv1x + ellipse->cv2x) / 2;
                    ellipse->k_covertices = (ellipse->cv1y + ellipse->cv2y) / 2;

                    if (ellipse->h_vertices == ellipse->h_covertices && ellipse->k_vertices == ellipse->k_covertices) //Final Condition [Vertical Ellipse]: The co-vertices and vertices are valid if their calculated midpoints are equal
                    {
                        vertices_check = 1;
                    }
                    else
                    {
                        ellipse->restart = 0;
                        do
                        {
                            printf("Invalid Data!\n");
                            printf("Would you like to restart your input [1] Yes [2] No: ");
                            scanf("%d", &ellipse->restart);

                        } while (ellipse->restart != 1 && ellipse->restart != 2);
                        
                        if (ellipse->restart == 1)
                        {
                            getchar();
                            covertices_check = 0;
                            vertices_check = 0;
                            goto ellipse_coverticesinput;
                        }

                        else if (ellipse->restart == 2)
                        {
                            getchar();
                        }
                        
                    }
                }
                else if (ellipse->v1x != ellipse->v2x && ellipse->v1y == ellipse->v2y) //Condition [Horizontal Ellipse]: x-coordinates of vertices are not equal, y-coordinates of vertices are equal
                {
                    float difference_vertices = ellipse->v2x - ellipse->v1x;

                    if (difference_vertices < 0)
                    {
                        float temporary_vertices = ellipse->v1x;
                        ellipse->v1x = ellipse->v2x;
                        ellipse->v2x = temporary_vertices;
                    }

                    //Calculations for Final check of Co-vertices and Vertices

                    ellipse->h_vertices = (ellipse->v1x + ellipse->v2x) / 2;
                    ellipse->k_vertices = (ellipse->v1y + ellipse->v2y) / 2;

                    ellipse->h_covertices = (ellipse->cv1x + ellipse->cv2x) / 2;
                    ellipse->k_covertices = (ellipse->cv1y + ellipse->cv2y) / 2;

                    if (ellipse->h_vertices == ellipse->h_covertices && ellipse->k_vertices == ellipse->k_covertices)
                    {
                        vertices_check = 1;
                    }
                    else
                    {
                        printf("Invalid Data!\n");
                        ellipse->restart = 0;
                        do
                        {
                            printf("Would you like to restart your input [1] Yes [2] No: ");
                            scanf("%d", &ellipse->restart);

                            if (ellipse->restart == 1)
                            {
                                getchar();
                                covertices_check = 0;
                                vertices_check = 0;
                                goto ellipse_coverticesinput;
                            }
                            
                            else if (ellipse->restart == 2)
                            {
                                getchar();
                            }

                        } while (ellipse->restart != 1 && ellipse->restart != 2);
                        
                    }
                }
                else
                {
                    printf("Invalid Data!\n");
                }
            }
            else
            {
                printf("Incomplete Information!\n");
            }
        } //End of Vertices Input Loop
        

        //Commonalities across both Horizontal and Vertical Ellipse
        
        ellipse->maj_axis = sqrt(pow(ellipse->v2y - ellipse->v1y, 2) + pow(ellipse->v2x - ellipse->v1x, 2));
        ellipse->min_axis = sqrt(pow(ellipse->cv2y - ellipse->cv1y, 2) + pow(ellipse->cv2x - ellipse->cv1x, 2));

        ellipse->semi_maj_axis = ellipse->maj_axis / 2;
        ellipse->semi_min_axis = ellipse->min_axis / 2;

        ellipse->a = ellipse->maj_axis / 2;
        ellipse->b = ellipse->min_axis / 2;
            
        ellipse->a_2 = pow(ellipse->a, 2);
        ellipse->b_2 = pow(ellipse->b, 2);
        ellipse->c_2 = ellipse->a_2 - ellipse->b_2; //If c^2 < 0, then degenerate ellipse

        ellipse->c = sqrt(ellipse->c_2);
        ellipse->focal_length = 2*ellipse->c;

        ellipse->h = (ellipse->v1x + ellipse->v2x) / 2;
        ellipse->k = (ellipse->v1y + ellipse->v2y) / 2;


        if (ellipse->v1x == ellipse->v2x && ellipse->v1y != ellipse->v2y && ellipse->c_2 > 0) //Vertical Ellipse Condition
        {
            ellipse->f1x = ellipse->h;
            ellipse->f1y = ellipse->k - ellipse->c;
            ellipse->f2x = ellipse->h;
            ellipse->f2y = ellipse->k + ellipse->c;

            ellipse->d1 = ellipse->k - pow(ellipse->a, 2) / ellipse->c;
            ellipse->d2 = ellipse->k + pow(ellipse->a, 2) / ellipse->c;

            ellipse->lr1 = ellipse->k - ellipse->c;
            ellipse->lr2 = ellipse->k + ellipse->c;

            ellipse->focal_width = 2*pow(ellipse->b, 2) / ellipse->a;

            ellipse->A = ellipse->a_2;
            ellipse->C = ellipse->b_2;
            ellipse->D = -2*ellipse->a_2*ellipse->h;
            ellipse->E = -2*ellipse->b_2*ellipse->k;
            ellipse->F = ellipse->a_2 * pow (ellipse->h, 2) + ellipse->b_2 * pow (ellipse->k, 2) - ellipse->a_2 * ellipse->b_2;
        }

        else if (ellipse->v1x != ellipse->v2x && ellipse->v1y == ellipse->v2y && ellipse->c_2 > 0) //Horizontal Ellipse Condition in terms of Vertices
        {
            ellipse->f1x = ellipse->h - ellipse->c;
            ellipse->f1y = ellipse->k;
            ellipse->f2x = ellipse->h + ellipse->c;
            ellipse->f2y = ellipse->k;

            ellipse->d1 = ellipse->h - pow(ellipse->a, 2) / ellipse->c;
            ellipse->d2 = ellipse->h + pow(ellipse->a, 2) / ellipse->c;

            ellipse->lr1 = ellipse->h - ellipse->c;
            ellipse->lr2 = ellipse->h + ellipse->c;

            ellipse->focal_width = 2*pow(ellipse->b, 2) / ellipse->a;

            ellipse->A = ellipse->b_2;
            ellipse->C = ellipse->a_2;
            ellipse->D = 2*ellipse->b_2*ellipse->h;
            ellipse->E = 2*ellipse->a_2*ellipse->k;
            ellipse->F = ellipse->b_2 * pow(ellipse->h, 2) + ellipse->a_2 * pow(ellipse->k, 2) - ellipse->a_2 * ellipse->b_2;
        }
        else
        {
            printf("Invalid Ellipse!\n");
            covertices_check = 0;
            vertices_check = 0;
            goto ellipse_coverticesinput;
        }

        
        
    } //End of Method 2: Vertices + Co-vertices
    
    else if (ellipse->final_solution == 3)
    {
        method3_input:
        while (!range_check)
        {
            while (!domain_check)
            {
                while (!foci_check)
                {
                    printf("Enter Coordinates of Foci [x1, y1, x2, y2]: ");
                    fgets(ellipse->foci, sizeof(ellipse->foci), stdin);
                    ellipse->foci[strcspn(ellipse->foci, "\n")] = '\0';

                    if (sscanf(ellipse->foci, "%f %f %f %f", &ellipse->f1x, &ellipse->f1y, &ellipse->f2x, &ellipse->f2y) == 4)
                    {
                        if (ellipse->f1x == ellipse->f2x && ellipse->f1y != ellipse->f2y) //Foci in Vertical Ellipse: same x-coordinates, different y-coordinates
                        {
                            float difference_foci = ellipse->f2y - ellipse->f1y; //Determine which input is bigger first y-coordinate or second y-coordinate

                            if (difference_foci < 0) //ellipse->f1y > ellipse->f2y
                            {
                                float temporary_foci = ellipse->f1y;
                                ellipse->f1y = ellipse->f2y;
                                ellipse->f2y = temporary_foci;
                            }

                            foci_check = 1;
                        }
                        else if (ellipse->f1x != ellipse->f2x && ellipse->f1y == ellipse->f2y) //Foci in Horizontal Ellipse: different x-coordinates, same y-coordinates
                        {
                            float difference_foci = ellipse->f2x - ellipse->f1x; //Determine which input is bigger first x-coordinate or second y-coordinate
                            
                            if (difference_foci < 0) //ellipse->f1x > ellipse->f2x
                            {
                                float temporary_foci = ellipse->f1x;
                                ellipse->f1x = ellipse->f2x;
                                ellipse->f2x = temporary_foci;
                            }

                            foci_check = 1;
                        }
                        else
                        {
                            printf("Invalid Focus!\n");
                        }
                    }
                    else
                    {
                        printf("Incomplete Information!\n");
                    }
                    
                } //End of Foci Loop

                printf("Enter Domain [Endpoint 1 Endpoint 2]: "); //Assumption: Endpoint 2 > Endpoint 1
                fgets(ellipse->domain, sizeof(ellipse->domain), stdin);
                ellipse->domain[strcspn(ellipse->domain, "\n")] = '\0';
                
                if (sscanf(ellipse->domain, "%c%f %f%c", &ellipse->opening_bracket, &ellipse->domain_endpoint1, &ellipse->domain_endpoint2, &ellipse->closing_bracket) == 4)
                {
                    if (ellipse->domain_endpoint2 <= ellipse->domain_endpoint1)
                    {
                        printf("Invalid Domain!\n");
                        ellipse->restart = 0;
                        do
                        {
                            printf("Would you like to restart your input [1] Yes [2] No: ");
                            scanf("%d", &ellipse->restart);
                            getchar();

                        } while (ellipse->restart != 1 && ellipse->restart != 2);

                        if (ellipse->restart == 1)
                        {
                            foci_check = 0;
                            domain_check = 0;
                            range_check = 0;
                            goto method3_input;
                        }
                        else 
                        {
                            printf("");
                        }
                        
                    }
                    else
                    {
                        domain_check = 1;
                    }

                }
                else
                {
                    printf("Incomplete Information!\n");
                }
            } //End of Domain Loop

            printf("Enter Range [Endpoint 1 Endpoint 2]: ");
            fgets(ellipse->range, sizeof(ellipse->range), stdin);
            ellipse->range[strcspn(ellipse->range, "\n")] = '\0';

            if (sscanf(ellipse->range, "%c%f %f%c", &ellipse->opening_bracket, &ellipse->range_endpoint1, &ellipse->range_endpoint2, ellipse->closing_bracket) == 4)
            {
                if (ellipse->range_endpoint2 <= ellipse->range_endpoint1)
                {
                    printf("Invalid Range!\n");
                    ellipse->restart = 0;
                    do
                    {
                        printf("Would you like to restart your input [1] Yes [2] No: ");
                        scanf("%d", &ellipse->restart);
                        getchar();
                    
                    } while (ellipse->restart != 1 && ellipse->restart != 2);

                    if (ellipse->restart == 1)
                    {
                        foci_check = 0;
                        domain_check = 0;
                        range_check = 0;

                        goto method3_input;
                    }
                    else
                    {
                        printf("");
                    }
                    
                }
                else
                {
                    range_check = 1;
                }
            }
            else
            {
                printf("Incomplete Information!\n");
            }

        } //End of Range Loop

        ellipse->h_foci = (ellipse->f1x + ellipse->f2x) / 2;
        ellipse->k_foci = (ellipse->f1y + ellipse->f2y) / 2;

        ellipse->h_domain = (ellipse->domain_endpoint1 + ellipse->domain_endpoint2) / 2;
        ellipse->k_range = (ellipse->range_endpoint1 + ellipse->range_endpoint2) / 2;

        if (ellipse->h_foci == ellipse->h_domain && ellipse->k_foci == ellipse->k_range) //Check if Foci, Domain, and Range are valid
        {
            ellipse->focal_length = sqrt(pow(ellipse->f2y - ellipse->f1y, 2) + pow(ellipse->f2x - ellipse->f1x, 2));
            ellipse->h = ellipse->h_foci;
            ellipse->k = ellipse->k_foci;
             
            if (ellipse->f1x == ellipse->f2x && ellipse->f1y != ellipse->f2y) //Foci in a Vertical Ellipse: x-coordinates are equal, y-coordinates are different
            {
                ellipse->maj_axis = sqrt(pow(ellipse->range_endpoint2 - ellipse->range_endpoint1, 2));
                ellipse->min_axis = sqrt(pow(ellipse->domain_endpoint2 - ellipse->domain_endpoint1, 2));
                ellipse->semi_maj_axis = ellipse->maj_axis / 2;
                ellipse->semi_min_axis = ellipse->min_axis / 2;
                
                ellipse->a = ellipse->maj_axis / 2;
                ellipse->b = ellipse->min_axis / 2;
                ellipse->c = ellipse->focal_length / 2;

                ellipse->a_2 = pow(ellipse->a, 2);
                ellipse->b_2 = pow(ellipse->b, 2);
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

                ellipse->v1x = ellipse->h;
                ellipse->v1y = ellipse->k - ellipse->a;
                ellipse->v2x = ellipse->h;
                ellipse->v2y = ellipse->k + ellipse->a;

                ellipse->cv1x = ellipse->h - ellipse->b;
                ellipse->cv1y = ellipse->k;
                ellipse->cv2x = ellipse->h + ellipse->b;
                ellipse->cv2y = ellipse->k;

                ellipse->d1 = ellipse->k - ellipse->a_2 / ellipse->c;
                ellipse->d2 = ellipse->k + ellipse->a_2 / ellipse->c;
                ellipse->lr1 = ellipse->k - ellipse->c;
                ellipse->lr2 = ellipse->k + ellipse->c;
                ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;

                ellipse->A = ellipse->a_2;
                ellipse->C = ellipse->b_2;
                ellipse->D = -2*ellipse->a_2 * ellipse->h;
                ellipse->E = -2*ellipse->b_2 * ellipse->k;
                ellipse->F = ellipse->a_2*pow(ellipse->h, 2) + ellipse->b_2*pow(ellipse->k, 2) - ellipse->a_2*ellipse->b_2;
            }
            
            else if (ellipse->f1x != ellipse->f2x && ellipse->f1y == ellipse->f2y) //Foci in a Horizontal Ellipse: x-coordinates are not equal, y-coordinates are equal
            {
                ellipse->maj_axis = sqrt(pow(ellipse->domain_endpoint2 - ellipse->domain_endpoint1, 2));
                ellipse->min_axis = sqrt(pow(ellipse->range_endpoint2 - ellipse->range_endpoint1, 2));
                ellipse->semi_maj_axis = ellipse->maj_axis / 2;
                ellipse->semi_min_axis = ellipse->min_axis / 2;

                ellipse->a = ellipse->maj_axis / 2;
                ellipse->b = ellipse->min_axis / 2;
                ellipse->c = ellipse->focal_length / 2;

                ellipse->a_2 = pow(ellipse->a, 2);
                ellipse->b_2 = pow(ellipse->b, 2);
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;
                
                ellipse->v1x = ellipse->h - ellipse->a;
                ellipse->v1y = ellipse->k;
                ellipse->v2x = ellipse->h + ellipse->a;
                ellipse->v2y = ellipse->k;

                ellipse->cv1x = ellipse->h;
                ellipse->cv1y = ellipse->h - ellipse->b;
                ellipse->cv2x = ellipse->h;
                ellipse->cv2y = ellipse->h + ellipse->b;

                ellipse->d1 = ellipse->h - ellipse->a_2 / ellipse->c;
                ellipse->d2 = ellipse->h + ellipse->a_2 / ellipse->c;
                ellipse->lr1 = ellipse->h - ellipse->c;
                ellipse->lr2 = ellipse->h + ellipse->c;
                ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;

                ellipse->A = ellipse->b_2;
                ellipse->C = ellipse->a_2;
                ellipse->D = -2*ellipse->b_2 * ellipse->h;
                ellipse->E = -2*ellipse->a_2 * ellipse->k;
                ellipse->F = ellipse->b_2*pow(ellipse->h, 2) + ellipse->a_2*pow(ellipse->k, 2) - ellipse->a_2*ellipse->b_2;
            }
        }
        else
        {
            printf("Invalid Data!\n");
            range_check = 0;
            domain_check = 0;
            foci_check = 0;
            goto method3_input;
        }

    } //End of Method 3: Domain and Range + Foci
    
    else if (ellipse->final_solution == 4) 
    {
        method4_input:
        while (!point_check)
        {
            while (!derivative_check)
            {
                printf("Enter Derivative of Ellipse [Coefficients: x and y | Constants: D and E]: ");
                fgets(ellipse->derivative, sizeof(ellipse->derivative), stdin);
                ellipse->derivative[strcspn(ellipse->derivative, "\n")] = '\0';

                if (sscanf(ellipse->derivative, "%f %f %f %f", &ellipse->coefficient_x, &ellipse->neg_constant_D, &ellipse->coefficient_y, &ellipse->constant_E) == 4)
                {
                    printf("Inputted Derivative: dy / dx = %.2fx + %.2f / %.2fy + %.2f\n", ellipse->coefficient_x, ellipse->neg_constant_D, ellipse->coefficient_y, ellipse->constant_E);
                    derivative_check = 1;
                }
                else
                {
                    printf("Incomplete Data!\nIf you are missing a variable or constant, input 0\n");
                }

            } //End of Derivative Input
            
            printf("Enter Point on Ellipse (x, y): ");
            fgets(ellipse->point_ellipse, sizeof(ellipse->point_ellipse), stdin);
            ellipse->point_ellipse[strcspn(ellipse->point_ellipse, "\n")] = '\0';

            if (sscanf(ellipse->point_ellipse, "%f %f", &ellipse->Point_x, &ellipse->Point_y) == 2)
            {
                point_check = 1;
            }

            else
            {
                printf("Incomplete Data!\n");
            }
        }

        ellipse->A = -ellipse->coefficient_x / 2;
        ellipse->C = ellipse->coefficient_y / 2;
        ellipse->D = -ellipse->neg_constant_D;
        ellipse->E = ellipse->constant_E;
        ellipse->F = -ellipse->A*pow(ellipse->Point_x, 2) - ellipse->C*pow(ellipse->Point_y, 2) - ellipse->D*ellipse->Point_x - ellipse->E*ellipse->Point_y;


        if (ellipse->A != ellipse->C && ellipse->A > 0 && ellipse->C > 0)
        {
            ellipse->numerator = (ellipse->C*pow(ellipse->D, 2) + ellipse->A*pow(ellipse->E, 2) - 4*ellipse->A*ellipse->C*ellipse->F) / (4*ellipse->A*ellipse->C);
            if (ellipse->A > ellipse->C) //Vertical Ellipse
            {
                ellipse->a_2 = ellipse->numerator / ellipse->C;
                ellipse->b_2 = ellipse->numerator / ellipse->a;
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

                ellipse->a = sqrt(ellipse->a_2);
                ellipse->b = sqrt(ellipse->b_2);
                ellipse->c = sqrt(ellipse->a_2 - ellipse->b_2);

                ellipse->h = -ellipse->D / (2*ellipse->A);
                ellipse->k = -ellipse->E / (2*ellipse->E);

                ellipse->f1x = ellipse->h;
                ellipse->f1y = ellipse->k - ellipse->c;
                ellipse->f2x = ellipse->h;
                ellipse->f2y = ellipse->k + ellipse->c;

                ellipse->v1x = ellipse->h;
                ellipse->v1y = ellipse->k - ellipse->a;
                ellipse->v2x = ellipse->h;
                ellipse->v2y = ellipse->k + ellipse->a;

                ellipse->cv1x = ellipse->h - ellipse->b;
                ellipse->cv1y = ellipse->k;
                ellipse->cv2x = ellipse->h + ellipse->b;
                ellipse->cv2y = ellipse->k;

                ellipse->maj_axis = 2*ellipse->a;
                ellipse->min_axis = 2*ellipse->b;
                ellipse->focal_length = 2*ellipse->c;

                ellipse->semi_maj_axis = ellipse->a;
                ellipse->semi_min_axis = ellipse->b;

                ellipse->d1 = ellipse->k - ellipse->a_2 / ellipse->c;
                ellipse->d2 = ellipse->k + ellipse->a_2 / ellipse->c;

                ellipse->lr1 = ellipse->k - ellipse->c;
                ellipse->lr2 = ellipse->k + ellipse->c;

                ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;
            }

            else if (ellipse->A < ellipse->C)
            {
                ellipse->a_2 = ellipse->numerator / ellipse->A;
                ellipse->b_2 = ellipse->numerator / ellipse->C;
                ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

                ellipse->a = sqrt(ellipse->a_2);
                ellipse->b = sqrt(ellipse->b_2);
                ellipse->c = sqrt(ellipse->a_2 - ellipse->b);

                ellipse->f1x = ellipse->h - ellipse->c;
                ellipse->f1y = ellipse->k;
                ellipse->f2x = ellipse->h + ellipse->c;
                ellipse->f2y = ellipse->k;

                ellipse->v1x = ellipse->h - ellipse->a;
                ellipse->v1y = ellipse->k;
                ellipse->v2x = ellipse->h + ellipse->a;
                ellipse->v2y = ellipse->k;

                ellipse->cv1x = ellipse->h;
                ellipse->cv1y = ellipse->k - ellipse->b;
                ellipse->cv2x = ellipse->h;
                ellipse->cv2y = ellipse->k + ellipse->b;

                ellipse->maj_axis = 2*ellipse->a;
                ellipse->min_axis = 2*ellipse->b;
                ellipse->focal_length = 2*ellipse->c;
                ellipse->semi_maj_axis = ellipse->a;
                ellipse->semi_min_axis = ellipse->b;

                ellipse->d1 = ellipse->h - ellipse->a_2 / ellipse->c;
                ellipse->d2 = ellipse->h + ellipse->a_2 / ellipse->c;

                ellipse->lr1 = ellipse->h - ellipse->c;
                ellipse->lr2 = ellipse->h + ellipse->c;
                ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;
                
            }
        }
        else
        {
            printf("Invalid Data!\n");
            pointderivative_check = 0;
            point_check = 0;
            derivative_check = 0;
            goto method4_input;
        }

    } //End of Method 4: Derivative of Ellipse Equation + Point on Ellipse -> P: (x, y)
    else 
    {
        float Point1_check = 0, Point2_check = 0, Point3_check = 0; //Conditional Variables to stop loops if inputted points are complete
        float constants_check = 0; //Conditional Variables to stop loop if inputted equivalent values are complete
        int decision_check; //Variable to check if user wants to change input or not
        float determinant_p1A, determinant_p2A, determinant_p3A, determinant_p4A; //4 parts to add to find resultant determinant of Matrix A
        float determinant_p1C, determinant_p2C, determinant_p3C, determinant_p4C; //4 parts to add to find resultant determinant of Matrix C
        float determinant_p1D, determinant_p2D, determinant_p3D, determinant_p4D; //4 parts to add to find resultant determinant of Matrix D

        method5_input:
        while (!Point3_check)
        {
            while (!Point2_check)
            {
                while (!Point1_check)
                {
                    printf("Enter Point 1 (X1, Y1): ");
                    fgets(ellipse->Point1, sizeof(ellipse->Point1), stdin);
                    ellipse->Point1[strcspn(ellipse->Point1, "\n")] = '\0';

                    if (sscanf(ellipse->Point1, "%f %f", &ellipse->Point1_x, &ellipse->Point1_y) == 2)
                    {
                        Point1_check = 1;
                    }
                    else
                    {
                        printf("Incomplete Data!\n");
                    }
                } //End of Point 1 Input
                
                printf("Enter Point 2 (X2, Y2): ");
                fgets(ellipse->Point2, sizeof(ellipse->Point2), stdin);
                ellipse->Point2[strcspn(ellipse->Point2, "\n")] = '\0';

                if (sscanf(ellipse->Point2, "%f %f", &ellipse->Point2_x, &ellipse->Point2_y) == 2)
                {
                    Point2_check = 1;
                }
                else
                {
                    printf("Incomplete Data!\n");
                }

            } //End of Point 2 Input 

            printf("Enter Point 3 (X3, Y3): ");
            fgets(ellipse->Point3, sizeof(ellipse->Point3), stdin);
            ellipse->Point3[strcspn(ellipse->Point3, "\n")] = '\0';

            if (sscanf(ellipse->Point3, "%f %f", &ellipse->Point3_x, &ellipse->Point3_y) == 2)
            {
                Point3_check = 1;
            }
            else
            {
                printf("Incomplete Data!\n");
            }

        } //End of Point 3 Input 

        while (!constants_check)
        {
            printf("Enter Values of E & F: ");
            fgets(ellipse->constants, sizeof(ellipse->constants), stdin);
            ellipse->constants[strcspn(ellipse->constants, "\n")] = '\0';

            if (sscanf(ellipse->constants, "%f %f ", &ellipse->E, &ellipse->F) == 2)
            {
                constants_check = 1;
            }
            else
            {
                printf("Incomplete Data!\n");
            }
        }

        printf("Would you like to change your inputs [1] Yes [2] No: ");
        scanf("%d", &decision_check);
        getchar();

        if (decision_check == 1)
        {
            Point1_check = 0;
            Point2_check = 0;
            Point3_check = 0;
            constants_check = 0;
            goto method5_input;
        }
        else
        {
            printf("");
        }

        ellipse->A_1 = pow(ellipse->Point1_x, 2);
        ellipse->B_1 = pow(ellipse->Point1_y, 2);
        ellipse->C_1 = ellipse->Point1_x;

        ellipse->A_2 = pow(ellipse->Point2_x, 2);
        ellipse->B_2 = pow(ellipse->Point2_y, 2);
        ellipse->C_2 = ellipse->Point2_x;

        ellipse->A_3 = pow(ellipse->Point3_x, 2);
        ellipse->B_3 = pow(ellipse->Point3_y, 2);
        ellipse->C_3 = ellipse->Point3_x;

        ellipse->constant_1 = -ellipse->E*ellipse->Point1_y - ellipse->F;
        ellipse->constant_2 = -ellipse->E*ellipse->Point2_y - ellipse->F;
        ellipse->constant_3 = -ellipse->E*ellipse->Point3_y - ellipse->F;

        ellipse->system_coefficients[1][1] = ellipse->A_1;
        ellipse->system_coefficients[2][1] = ellipse->B_1;
        ellipse->system_coefficients[3][1] = ellipse->C_1;

        ellipse->system_coefficients[1][2] = ellipse->A_2;
        ellipse->system_coefficients[2][2] = ellipse->B_2;
        ellipse->system_coefficients[3][2] = ellipse->C_2;

        ellipse->system_coefficients[1][3] = ellipse->A_3;
        ellipse->system_coefficients[2][3] = ellipse->B_3;
        ellipse->system_coefficients[3][3] = ellipse->C_3;

        float determinant_p1 = (ellipse->system_coefficients[1][1] * ellipse->system_coefficients[2][2] * ellipse->system_coefficients[3][3]) + (ellipse->system_coefficients[2][1] * ellipse->system_coefficients[3][2] * ellipse->system_coefficients[1][3]);
        float determinant_p2 = (ellipse->system_coefficients[3][1] * ellipse->system_coefficients[1][2] * ellipse->system_coefficients[2][3]);
        float determinant_p3 = -(ellipse->system_coefficients[2][1] * ellipse->system_coefficients[1][2] * ellipse->system_coefficients[3][3]) - (ellipse->system_coefficients[1][1] * ellipse->system_coefficients[3][2] * ellipse->system_coefficients[2][3]);
        float determinant_p4 = -(ellipse->system_coefficients[3][1] * ellipse->system_coefficients[2][2] * ellipse->system_coefficients[1][3]);

        ellipse->determinant = determinant_p1 + determinant_p2 + determinant_p3 + determinant_p4;
        if (ellipse->determinant == 0)
        {
            printf("Invalid Parameters!\n");
            Point1_check = 0, Point2_check = 0, Point3_check = 0;
            constants_check = 0;
            goto method5_input;
        }

        ellipse->matrix_A[1][1] = ellipse->constant_1;
        ellipse->matrix_A[1][2] = ellipse->constant_2;
        ellipse->matrix_A[1][3] = ellipse->constant_3;

        determinant_p1A = (ellipse->matrix_A[1][1] * ellipse->system_coefficients[2][2] * ellipse->system_coefficients[3][3]) + (ellipse->system_coefficients[2][1] * ellipse->system_coefficients[3][2] * ellipse->matrix_A[1][3]);
        determinant_p2A = (ellipse->system_coefficients[3][1] * ellipse->matrix_A[1][2] * ellipse->system_coefficients[2][3]);
        determinant_p3A = -(ellipse->system_coefficients[2][1] * ellipse->matrix_A[1][2] * ellipse->system_coefficients[3][3]) - (ellipse->matrix_A[1][1] * ellipse->system_coefficients[3][2] * ellipse->system_coefficients[2][3]);
        determinant_p4A = -(ellipse->system_coefficients[3][1] * ellipse->system_coefficients[2][2] * ellipse->matrix_A[1][3]);

        ellipse->determinant_A = determinant_p1A + determinant_p2A + determinant_p3A + determinant_p4A;

        ellipse->matrix_C[2][1] = ellipse->constant_1;
        ellipse->matrix_C[2][2] = ellipse->constant_2;
        ellipse->matrix_C[2][3] = ellipse->constant_3;


        determinant_p1C = (ellipse->system_coefficients[1][1] * ellipse->matrix_C[2][2] * ellipse->system_coefficients[3][3]) + (ellipse->matrix_C[2][1] * ellipse->system_coefficients[3][2] * ellipse->system_coefficients[1][3]);
        determinant_p2C = (ellipse->system_coefficients[3][1] * ellipse->system_coefficients[1][2] * ellipse->matrix_C[2][3]);
        determinant_p3C = -(ellipse->matrix_C[2][1] * ellipse->system_coefficients[1][2] * ellipse->system_coefficients[3][3]) - (ellipse->system_coefficients[1][1] * ellipse->system_coefficients[3][2] * ellipse->matrix_C[2][3]);
        determinant_p4C = -(ellipse->system_coefficients[3][1] * ellipse->matrix_C[2][2] * ellipse->system_coefficients[1][3]);

        ellipse->determinant_C = determinant_p1C + determinant_p2C + determinant_p3C + determinant_p4C;
        
        ellipse->matrix_D[3][1] = ellipse->constant_1;
        ellipse->matrix_D[3][2] = ellipse->constant_2;
        ellipse->matrix_D[3][3] = ellipse->constant_3;

        determinant_p1D = (ellipse->system_coefficients[1][1] * ellipse->system_coefficients[2][2] * ellipse->matrix_D[3][3]) + (ellipse->system_coefficients[2][1] * ellipse->matrix_D[3][2] * ellipse->system_coefficients[1][3]);
        determinant_p2D = (ellipse->matrix_D[3][1] * ellipse->system_coefficients[1][2] * ellipse->system_coefficients[2][3]);
        determinant_p3D = -(ellipse->system_coefficients[2][1] * ellipse->system_coefficients[1][2] * ellipse->matrix_D[3][3]) - (ellipse->system_coefficients[1][1] * ellipse->matrix_D[3][2] * ellipse->system_coefficients[2][3]);
        determinant_p4D = -(ellipse->matrix_D[3][1] * ellipse->system_coefficients[2][2] * ellipse->system_coefficients[1][3]);

        ellipse->determinant_D = determinant_p1D + determinant_p2D + determinant_p3D + determinant_p4D;

        ellipse->A = ellipse->determinant_A / ellipse->determinant;
        ellipse->C = ellipse->determinant_C / ellipse->determinant;
        ellipse->D = ellipse->determinant_D / ellipse->determinant;

        if (ellipse->A == ellipse->C || ellipse->A < 0 || ellipse->C < 0) //If values of A and C are equal or A < 0 or C < 0 or A and C < 0, the ellipse is invalid
        {
            printf("Invalid ellipse!\n");
            Point1_check = 0, Point2_check = 0, Point3_check = 0;
            constants_check = 0;
            goto method5_input;
        }
        ellipse->h = -ellipse->D/(2*ellipse->A);
        ellipse->k = -ellipse->E/(2*ellipse->C);

        if (ellipse->A > ellipse->C) //Vertical Ellipse
        {
            ellipse->constant = -ellipse->F + ellipse->A*pow(ellipse->h, 2) + ellipse->C*pow(ellipse->h, 2);
            ellipse->a_2 = ellipse->constant / ellipse->C;
            ellipse->b_2 = ellipse->constant / ellipse->A;
            ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

            ellipse->a = sqrt(ellipse->a_2);
            ellipse->b = sqrt(ellipse->b_2);
            ellipse->c = sqrt(ellipse->a_2 - ellipse->b_2);

            ellipse->f1x = ellipse->h;
            ellipse->f1y = ellipse->k - ellipse->c;
            ellipse->f2x = ellipse->h;
            ellipse->f2y = ellipse->k + ellipse->c;

            ellipse->v1x = ellipse->h;
            ellipse->v1y = ellipse->h - ellipse->a;
            ellipse->v2x = ellipse->h;
            ellipse->v2y = ellipse->h + ellipse->a;

            ellipse->cv1x = ellipse->h - ellipse->b;
            ellipse->cv1y = ellipse->k;
            ellipse->cv2x = ellipse->h + ellipse->b;
            ellipse->cv2y = ellipse->k;

            ellipse->maj_axis = 2*ellipse->a;
            ellipse->min_axis = 2*ellipse->b;
            ellipse->focal_width = 2*ellipse->c;

            ellipse->semi_maj_axis = ellipse->a;
            ellipse->semi_min_axis = ellipse->b;

            ellipse->d1 = ellipse->k - ellipse->a_2 / ellipse->c;
            ellipse->d2 = ellipse->k + ellipse->a_2 / ellipse->c;

            ellipse->lr1 = ellipse->k - ellipse->c;
            ellipse->lr2 = ellipse->k + ellipse->c;

            ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;
        }

        else if (ellipse->A < ellipse->C) //Horizontal Ellipse
        {
            ellipse->constant = -ellipse->F + ellipse->A*pow(ellipse->h, 2) + ellipse->C*pow(ellipse->k, 2);
            ellipse->a_2 = ellipse->constant / ellipse->A;
            ellipse->b_2 = ellipse->constant / ellipse->C;
            ellipse->c_2 = ellipse->a_2 - ellipse->b_2;

            ellipse->a = sqrt(ellipse->a_2);
            ellipse->b = sqrt(ellipse->b_2);
            ellipse->c = sqrt(ellipse->a_2 - ellipse->b_2);

            ellipse->f1x = ellipse->h - ellipse->c;
            ellipse->f1y = ellipse->k;
            ellipse->f2x = ellipse->h + ellipse->c;
            ellipse->f2y = ellipse->k;

            ellipse->v1x = ellipse->h - ellipse->a;
            ellipse->v1y = ellipse->k;
            ellipse->v2x = ellipse->h + ellipse->a;
            ellipse->v2y = ellipse->k;

            ellipse->cv1x = ellipse->h;
            ellipse->cv1y = ellipse->k - ellipse->b;
            ellipse->cv2x = ellipse->h;
            ellipse->cv2y = ellipse->k + ellipse->b;

            ellipse->maj_axis = 2*ellipse->a;
            ellipse->min_axis = 2*ellipse->b;
            ellipse->focal_length = 2*ellipse->c;

            ellipse->semi_maj_axis = ellipse->a;
            ellipse->semi_min_axis = ellipse->b;

            ellipse->d1 = ellipse->h - ellipse->a_2 / ellipse->c;
            ellipse->d2 = ellipse->h + ellipse->a_2 / ellipse->c;
            
            ellipse->lr1 = ellipse->h - ellipse->c;
            ellipse->lr2 = ellipse->h + ellipse->c;
            
            ellipse->focal_width = 2*ellipse->b_2 / ellipse->a;
        }
    } //End of Method 5: Values of E & F + 3 Points on Ellipse
}

void display_output (struct Ellipse *ellipse, int input_equation)
{
    if (input_equation == 1) //Standard Form Equation Inputs
    {
        ellipse_equation (ellipse, input_equation);
        
        if (strcasecmp(ellipse->ellipse_direction, "Vertical") == 0)
        {
            if (ellipse->h == 0 && ellipse->k == 0) //Center at Origin
            {
                printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k == 0) //Center at Positive x-axis
            {
                printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k == 0) //Center at Negative x-axis
            {
                printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k > 0) //Center at Positive y-axis
            {
                printf("(y - %.2f)^2 / %.2f + x^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k < 0) //Center at Negative y-axis
            {
                printf("(y + %.2f)^2 / %.2f + x^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k > 0) //Center at Quadrant 1
            {
                printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k > 0) //Center at Quadrant 2
            {
                printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k < 0) //Center at Quadrant 3
            {
                printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse-> k < 0) //Center at Quadrant 4
            {
                printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
            }
        }
        
        else if (strcasecmp(ellipse->ellipse_direction, "Horizontal") == 0) 
        {
            if (ellipse->h == 0 && ellipse->k == 0) //Center at Origin
            {
                printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k == 0) //Center at Positive x-axis
            {
                printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k == 0) //Center at Negative x-axis
            {
                printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k > 0) //Center at Positive y-axis
            {
                printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k < 0) //Center at Negative y-axis
            {
                printf("x^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k > 0) //Center at Quadrant 1
            {
                printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k > 0) //Center at Quadrant 2
            {
                printf("(x + %.2f)^2 / %.2f + (y - %.2f)^2 = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k < 0) //Center at Quadrant 3
            {
                printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k < 0) //Center at Quadrant 4
            {
                printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
            }
        }

       
        printf("Center: (%.2f, %.2f)\n", ellipse->h, ellipse->k);
        printf("Foci: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->f1x, ellipse->f1y, ellipse->f2x, ellipse->f2y);
        printf("Vertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->v1x, ellipse->v1y, ellipse->v2x, ellipse->v2y);
        printf("Covertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->cv1x, ellipse->cv1y, ellipse->cv2x, ellipse->cv2y);
        printf("Major Axis Length: %.2f units\n", ellipse->maj_axis);
        printf("Minor Axis Length: %.2f units\n", ellipse->min_axis);
        printf("Semi Major Axis Length: %.2f units\n", ellipse->semi_maj_axis);
        printf("Semi Minor Axis Length: %.2f units\n", ellipse->semi_min_axis);
        
        if (strcasecmp(ellipse->ellipse_direction, "Vertical") == 0)
        {
            printf("Directrices: y = %.2f || y = %.2f\n", ellipse->d1, ellipse->d2);
            printf("Latera Recta: y = %.2f || y = %.2f\n", ellipse->lr1, ellipse->lr2);
        }

        else if (strcasecmp(ellipse->ellipse_direction, "Horizontal") == 0)
        {
            printf("Directrices: x = %.2f || x = %.2f\n", ellipse->d1, ellipse->d2);
            printf("Latera Recta: x = %.2f || x = %.2f\n", ellipse->lr1, ellipse->lr2);
        }
    
        printf("Focal Length: %.2f units\n", ellipse->focal_length);
        printf("Focal Width: %.2f units\n", ellipse->focal_width);

    }
    else if (input_equation == 2) //General Form Input
    {
        ellipse_equation(ellipse, input_equation);

        if (ellipse->A > ellipse->C && ellipse->A > 0 && ellipse->C > 0) //Vertical Ellipse
        {
            if (ellipse->h == 0 && ellipse->k == 0) //Origin
            {
                ("y^2 /%.2f + x^2 / %.2f= 1\n", ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k  == 0) //Positive x-axis
            {
                printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
            {
                printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k > 0) //Positive y-axis
            {
                printf("(y - %.2f)^2 / %.2f + x^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k < 0) //Negative y-axis
            {
                printf("(y + %.2f)^2 / %.2f + x^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k > 0) // Quadrant 1
            {
                printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k > 0) // Quadrant 2
            {
                printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
            {
                printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
            {
                printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
            }
        }
        
        else if (ellipse->A < ellipse->C && ellipse->A > 0 && ellipse->C > 0) //Horizontal Ellipse
        {
            if (ellipse->h == 0 && ellipse->k == 0) //Origin
            {
                printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k == 0) //Positive x-axis
            {
                printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
            {
                printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k > 0) //Positive y-axis
            {
                printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h == 0 && ellipse->k < 0) //Negative y-axis
            {
                printf("x^2 / %.2f + (y + %.2f)^2 / %,2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
            {
                printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
            {
                printf("(x + %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
            {
                printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
            }
            else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
            {
                printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
            }

        }

        printf("Center: (%.2f, %.2f)\n", ellipse->h, ellipse->k);
        printf("Foci: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->f1x, ellipse->f1y, ellipse->f2x, ellipse->f2y);
        printf("Vertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->v1x, ellipse->v1y, ellipse->v2x, ellipse->v2y);
        printf("Covertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->cv1x, ellipse->cv1y, ellipse->cv2x, ellipse->cv2y);
        printf("Major Axis Length: %.2f units\n", ellipse->maj_axis);
        printf("Minor Axis Length: %.2f units\n", ellipse->min_axis);
        printf("Semi Major Axis Length: %.2f units\n", ellipse->semi_maj_axis);
        printf("Semi Minor Axis Length: %.2f units\n", ellipse->semi_min_axis);

        if (ellipse->A > ellipse->C && ellipse->A > 0 && ellipse->C > 0)
        {
            printf("Directrices: y = %.2f || y = %.2f\n", ellipse->d1, ellipse->d2);
            printf("Latera Recta: y = %.2f || y = %.2f\n", ellipse->lr1, ellipse->lr2);
        }
        else if (ellipse->A < ellipse->C && ellipse->A > 0 && ellipse->C > 0)
        {
            printf("Directrices: x = %.2f || x = %.2f\n", ellipse->d1, ellipse->d2);
            printf("Latera Recta: x = %.2f || x = %.2f\n", ellipse->lr1, ellipse->lr2);
        }

        printf("Focal Length: %.2f units\n", ellipse->focal_length);
        printf("Focal Width: %.2f units\n", ellipse->focal_width);

    }
    
    else if (input_equation == 3) //Parameters Input
    {
        ellipse_parameter(ellipse);
        if (ellipse->final_solution == 1) //Method 1: Center + Foci + Vertices
        {
            if (ellipse->h == ellipse->f1x && ellipse->h == ellipse->f2x && ellipse->h == ellipse->v1x && ellipse->h == ellipse->v2x) //x coordinates are constant across center, foci, and vertices in a vertical ellipse
            {
                if (ellipse->h == 0 && ellipse->k == 0) //Origin
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //Positive x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //Positive y - axis
                {
                    printf("(y - %.2f)^2 / %.2f + x^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //Negative x - axis
                {
                    printf("(y + %.2f)^2 / %.2f + x^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Qudrant 4
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->k, ellipse->b_2);
                }

            }
            
            else if (ellipse->k == ellipse->f1y && ellipse->k == ellipse->f2y && ellipse->k == ellipse->v1y && ellipse->v2y) //y-coordinates of the center, foci, and vertices are constant in a horizontal ellipse
            {
                if (ellipse->h == 0 && ellipse->k == 0) //Origin
                {
                    printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //Positive x-axis
                {
                    printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
                {
                    printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //Positive y-axis
                {
                    printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //Negative y-axis
                {
                    printf("x^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("x + %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
            } //End of Solution 1 Display
        }

        else if (ellipse->final_solution == 2) //Method 2: Covertices + Vertices
        {
            if (ellipse->cv1x != ellipse->cv2x && ellipse->cv1y == ellipse->cv2y && ellipse->v1x == ellipse->v2x && ellipse->v1y != ellipse->v2y) //Vertical Ellipse Condition: Covertices [x-coordinates are not same, y-coordinates are the same], Vertices [x-coordinates are the same, y-coordinates are not the same]
            {
                if (ellipse->h == 0 && ellipse->k == 0) //Origin
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //Positive x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //Positive y-axis
                {
                    printf("(y - %.2f)^2 / %.2f + x^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //Negative y-axis
                {
                    printf("(y + %.2f)^2 / %.2f + x^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
            }

            else if (ellipse->cv1x == ellipse->cv2x && ellipse->cv1y != ellipse->cv2y && ellipse->v1x != ellipse->v2x && ellipse->v1y == ellipse->v2y)
            {
                if (ellipse->h == 0 && ellipse->k == 0) //Origin
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //Positive x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //Negative x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //Positive y-axis
                {
                    printf("(y - %.2f)^2 / %.2f + x^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //Negative y-axis
                {
                    printf("(y + %.2f)^2 / %.2f + x^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
            }
        } //End of Solution 2 Display

        else if (ellipse->final_solution == 3) //Domain and Range + Foci
        {
            if (ellipse->f1x == ellipse->f2x && ellipse->f1y != ellipse->f2y) //Vertical Ellipse: Foci have the same x-coordinates, but different y-coordinates
            {
                if (ellipse->h == 0 && ellipse->k == 0)
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //+x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4)
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
            }
            else if (ellipse->f1x != ellipse->f2x && ellipse->f1y == ellipse->f2y) //Horizontal Ellipse: Foci have different x-coordinates, but the same y-coordinates
            {
                if (ellipse->h == 0 && ellipse->k == 0)
                {
                    printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //+x-axis
                {
                    printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //-y-axis
                {
                    printf("x^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(x + %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
            }
        } //End of Solution 3 Display

        else if (ellipse->final_solution == 4) //Method 4: Derivative of Ellipse + Point on Ellipse
        {
            if (ellipse->A > ellipse->C) //Vertical Ellipse
            {
                if (ellipse->h == 0 && ellipse->k == 0)
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //+x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4)
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
            }
            else if (ellipse->A < ellipse->C) //Horizontal Ellipse
            {
                if (ellipse->h == 0 && ellipse->k == 0)
                {
                    printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k == 0) //+x-axis
                {
                    printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //-y-axis
                {
                    printf("x^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(x + %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }

            }
        }

        else if (ellipse->final_solution == 5) //Method 5: Values of E & F + 3 Points on the Ellipse
        {
            if (ellipse->A > ellipse->C) //Vertical Ellipse
            {
                if (ellipse->h > 0 && ellipse->k == 0) //+x-axis
                {
                    printf("y^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("y^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(y - %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(y - %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(y + %.2f)^2 / %.2f + (x + %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, -ellipse->h, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4)
                {
                    printf("(y + %.2f)^2 / %.2f + (x - %.2f)^2 / %.2f = 1\n", -ellipse->k, ellipse->a_2, ellipse->h, ellipse->b_2);
                }
                else
                {
                    printf("y^2 / %.2f + x^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }
            }
            else if (ellipse->A < ellipse->C) //Horizontal Ellipse
            {
                if (ellipse->h > 0.025 && ellipse->k == 0) //+x-axis
                {
                    printf("(x - %.2f)^2 / %.2f + y^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k == 0) //-x-axis
                {
                    printf("(x + %.2f)^2 / %.2f + y^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k > 0) //+y-axis
                {
                    printf("x^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h == 0 && ellipse->k < 0) //-y-axis
                {
                    printf("x^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k > 0) //Quadrant 1
                {
                    printf("(x - %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k > 0) //Quadrant 2
                {
                    printf("(x + %.2f)^2 / %.2f + (y - %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h < 0 && ellipse->k < 0) //Quadrant 3
                {
                    printf("(x + %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", -ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else if (ellipse->h > 0 && ellipse->k < 0) //Quadrant 4
                {
                    printf("(x - %.2f)^2 / %.2f + (y + %.2f)^2 / %.2f = 1\n", ellipse->h, ellipse->a_2, -ellipse->k, ellipse->b_2);
                }
                else
                {
                    printf("x^2 / %.2f + y^2 / %.2f = 1\n", ellipse->a_2, ellipse->b_2);
                }

            }

       }

            printf("Center: (%.2f, %.2f)\n", ellipse->h, ellipse->k);
            printf("Foci: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->f1x, ellipse->f1y, ellipse->f2x, ellipse->f2y);
            printf("Vertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->v1x, ellipse->v1y, ellipse->v2x, ellipse->v2y);
            printf("Covertices: (%.2f, %.2f) || (%.2f, %.2f)\n", ellipse->cv1x, ellipse->cv1y, ellipse->cv2x, ellipse->cv2y);
            printf("Major Axis Length: %.2f\n", ellipse->maj_axis);
            printf("Minor Axis Length: %.2f\n", ellipse->min_axis);
            printf("Focal Length: %.2f\n", ellipse->focal_length);
            printf("Semi Major Axis Length: %.2f\n", ellipse->semi_maj_axis);
            printf("Semi Minor Axis Length: %.2f\n", ellipse->semi_min_axis);

            if (ellipse->h == ellipse->f1x && ellipse->h == ellipse->f2x && ellipse->h == ellipse->v1x && ellipse->h == ellipse->v2x || ellipse->A > ellipse->C) //Vertical Ellipse description for Directrices and Latera Recta (Works for All Methods)
            {
                printf("Directrices: y = %.2f || y = %.2f\n", ellipse->d1, ellipse->d2);
                printf("Latera Recta: y = %.2f || y = %.2f\n", ellipse->lr1, ellipse->lr2);
            }
            else if (ellipse->k == ellipse->f1y && ellipse->k == ellipse->f2y && ellipse->k == ellipse->v1y && ellipse->k == ellipse->v2y || ellipse->A < ellipse->C) //Horizontal Ellipse description for Directrices and Latera Recta (Work for All Methods)
            {
                printf("Directrices: x = %.2f || x = %.2f\n", ellipse->d1, ellipse->d2);
                printf("Latera Recta: x = %.2f || x = %.2f\n", ellipse->lr1, ellipse->lr2);
            }

            printf("Focal Width: %.2f\n", ellipse->focal_width);
            printf("General Form: %.2fx^2 + %.2fy^2 + %.2fx + %.2fy + %.2f = 0\n", ellipse->A, ellipse->C, ellipse->D, ellipse->E, ellipse->F);
    }
}

int main()
{
    struct Ellipse ellipse;
    int input_equation = 0; //Type of Equation: General & Standard Form
    int loop_check = 0;

    while (!loop_check)
    {
        printf("Enter Type of Data [1] Standard Equation [2] General Equation [3] Parameters: ");
        scanf("%d", &input_equation);
        getchar();

        if (input_equation == 1 || input_equation == 2)
        {
            printf("If equation has missing variables, input 0\n");
            display_output (&ellipse, input_equation);
            loop_check = 1;
        }
        else if (input_equation == 3)
        {
            display_output(&ellipse, input_equation);
            loop_check = 1;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}