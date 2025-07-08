#include <stdio.h>
#include <math.h>
#include <string.h>

struct Parabola
{
   float A, C, D, E, F; //Coefficients of x^2, y^2, x, y, constant
   float h, k; //Vertex: (h, k)
   float fx, fy; //Focus: (fx, fy)
   float axis_symmetry; //Axis of Symmetry
   float directrix; //Directrix
   float latus_rectum; //Latus Rectum
   int direction; //Opening Direction of Parabola
   char coefficients[100]; //Coefficients of A or C, D, E, F in General Form

   //Method 2: Vertex + Directrix
   char directrix_2[100]; //User - Inputted Directrix (Also used for Method 3)
   char vertex[100]; //User - Inputted Vertex
   char variable, eq_sign; //Variable: x or y, Equal Sign: = 
   float value; //Value of Directrix: h + c (Leftwards) or h - c (Rightwards) | k + c (Downwards) or k - c (Upwards)

   //Method 3: Focus + Directrix
   char focus[100]; //User -  Inputted Focus
};

void parabola_equation (struct Parabola parabola, char direction [100], float *h, float *k, float *fx, float *fy, float *axis_symmetry, float *directrix, float *latus_rectum)
{
    
    if (strcasecmp(direction, "Vertical") == 0)
    {
        while (1)
        {  
            printf("Enter Coefficients [A, D, E, F]: ");
            fgets(parabola.coefficients, sizeof(parabola.coefficients), stdin);
            parabola.coefficients[strcspn(parabola.coefficients, "\n")] = '\0';
        
            if (sscanf(parabola.coefficients, "%f %f %f %f", &parabola.A, &parabola.D, &parabola.E, &parabola.F) == 4)
            {
                break;
            }
            else
            {  
                printf("");
            }
        }
   
        float a = -parabola.A / parabola.E;
        *latus_rectum = 1/a;
        float c = (*latus_rectum) / 4;

        *h = -parabola.D / (2*parabola.A);
        *k = (pow(parabola.D, 2) - 4*parabola.A*parabola.F) / (4*parabola.A*parabola.E);
        *axis_symmetry = *h;
        *fx = *h;

        if (a > 0)
        {
            *fy = *k + c;
            *directrix = *k - c;
        }
        else if (a < 0)
        {
            *fy = *k - c;
            *directrix = *k + c;
        }
    }

    else if (strcasecmp(direction, "Horizontal") == 0)
    {
        printf("Enter Coefficients [C, D, E, F]: ");
        scanf("%f %f %f %f", &parabola.C, &parabola.D, &parabola.E, &parabola.F);

        float a = -parabola.C / parabola.D;
        *latus_rectum = (1/a);
        float c = (*latus_rectum) / 4;

        *h = (pow(parabola.E, 2) - 4*parabola.C*parabola.F) / (4*parabola.C*parabola.D);
        *k = -parabola.E / (2*parabola.C);
        *axis_symmetry = *k;
        *fy = *k;
        if (a > 0)
        {
            *fx = *h + c;
            *directrix = *h - c;
        }
        else if (a < 0)
        {
            *fx = *h - c;
            *directrix = *h + c;
        }
    }
}

void parabola_parameter (struct Parabola parabola, int method, float *h, float *k, float *latus_rectum, int *p_direction)
{
    float c;
    parabola.h = 0;
    parabola.k = 0;
    parabola.fx = 0;
    parabola.fy = 0;
    
    if (method == 1)
    {
        for (int j = 0; parabola.h == parabola.fx && parabola.k == parabola.fy || parabola.h != parabola.fx && parabola.k != parabola.fy; j++)
        {
            printf("Enter Coordinates of Vertex: ");
            scanf("%f %f", &parabola.h, &parabola.k);

            printf("Enter Coordinates of Focus: ");
            scanf("%f %f", &parabola.fx, &parabola.fy);

            if (parabola.h == parabola.fx && parabola.k == parabola.fy || parabola.h != parabola.fx && parabola.k != parabola.fy)
            {
                printf("Invalid Vertex and Focus!\n");
            }
        }

        if (parabola.h == parabola.fx) // Vertical Opening
        {
            c = parabola.fy - parabola.k;
            *h = parabola.h;
            *k = parabola.k;
            *latus_rectum = 4*c;
            *p_direction = 1;
        }
        else if (parabola.k == parabola.fy) // Horizontal Opening
        {
            c = parabola.fx - parabola.h;
            *h = parabola.h;
            *k = parabola.k;
            *latus_rectum = 4*c;
            *p_direction = 2;
        }
    }

    else if (method == 2)
    {
        while (sscanf(parabola.vertex, " %f %f", &parabola.h, &parabola.k) != 2)
        {
            printf("Enter Coordinates of Vertex: ");
            fgets(parabola.vertex, sizeof(parabola.vertex), stdin);
            parabola.vertex[strcspn(parabola.vertex, "\n")] = '\0';

            if (sscanf(parabola.vertex, " %f %f", &parabola.h, &parabola.k) == 2)
            {
                break;
            }
            else
            {
                printf("Invalid Vertex!\n");
            }
        }
        
        input_directrix:
        printf("Enter Directrix [x = value or y = value]: ");
        fgets(parabola.directrix_2, sizeof(parabola.directrix_2), stdin);
        parabola.directrix_2[strcspn(parabola.directrix_2, "\n")] = '\0';

        if (sscanf(parabola.directrix_2, " %c %c %f", &parabola.variable, &parabola.eq_sign, &parabola.value) == 3)
        {
            if (parabola.eq_sign == '=')
            {
    
                if (parabola.variable == 'x' || parabola.variable == 'X') //Horizontal
                {
                    if (parabola.h != parabola.value)
                    {
                        *h = parabola.h;
                        *k = parabola.k;
                        c = parabola.h - parabola.value;
                        *latus_rectum = 4*c;
                        *p_direction = 2;
                    }
                    else
                    {
                        printf("Error! Directrix and x - coordinate of Vertex can't be the same for Horizontal Parabolas!\n");
                        goto input_directrix;
                    }
                }
                else if (parabola.variable == 'y' || parabola.variable == 'Y') //Vertical
                {
                    if (parabola.k != parabola.value)
                    {
                        *h = parabola.h;
                        *k = parabola.k;
                        c = parabola.k - parabola.value;
                        *latus_rectum = 4*c;
                        *p_direction = 1;
                    }
                    else
                    {
                        printf("Error! Directrix and y - coordinate of Vertex can't be the same for Vertical Parabolas!\n");
                        goto input_directrix;
                    }
                }
            }
            else
            {
                printf("Invalid Form: Add an Equal Sign\n");
                goto input_directrix;
            }
        }
        else
        {
            printf("Incomplete Form\n");
            goto input_directrix;
        }
    }

    else if (method == 3)
    {
        int check_inputs = 0;
        while (!check_inputs) //Same as while (check_inputs == 0)
        {
            printf("Enter Coordinates of Focus: ");
            fgets(parabola.focus, sizeof(parabola.focus), stdin);
            parabola.focus[strcspn(parabola.focus, "\n")] = '\0';

            if (sscanf(parabola.focus, " %f %f", &parabola.fx, &parabola.fy) == 2)
            {
                while (1)
                {
                    printf("Enter Directrix [x = value or y = value]: ");
                    fgets(parabola.directrix_2, sizeof(parabola.directrix_2), stdin);
                    parabola.directrix_2[strcspn(parabola.directrix_2, "\n")] = '\0';
                    if (sscanf(parabola.directrix_2, "%c %c %f", &parabola.variable, &parabola.eq_sign, &parabola.value) == 3)
                    {
                        if (parabola.eq_sign == '=')
                        {
                            if (parabola.variable == 'x' || parabola.variable == 'X') //Horizontal Parabola
                            {
                                if (parabola.fx != parabola.value)
                                {
                                    *h = (parabola.fx + parabola.value) / 2;
                                    *k = parabola.fy;
                                    c = parabola.fx - *h;
                                    *latus_rectum = 4*c;
                                    check_inputs = 1;
                                    *p_direction = 2;
                                    break;
                                }
                                else
                                {
                                    printf("Error! Directrix and x - coordinate of Focus can't be the same for Horizontal Parabolas!\n");
                                }

                            }
                            
                            else if (parabola.variable == 'y' || parabola.variable == 'Y') //Vertical Parabola
                            {
                                if (parabola.fy != parabola.value)
                                {
                                    *h = parabola.fx;
                                    *k = (parabola.fy + parabola.value) / 2;
                                    c = parabola.fy - *k;
                                    *latus_rectum = 4*c;
                                    check_inputs = 1;
                                    *p_direction = 1;
                                    break;
                                }
                                else
                                {
                                    printf("Error! Directrix and y - coordinate of Focus can't be the same for Vertical Parabolas!\n");
                                }
                            }
                        }
                        else
                        {
                            printf("Invalid Directrix!\n");
                        }
                    }
                    else
                    {
                        printf("Invalid Form!\n");
                    }
                }
            }
            else
            {
                printf("Invalid Focus!\n");
            }
        }
    }
}

void display_output (struct Parabola parabola, char direction [100], char methods[100], int choice)
{
    if (choice == 1)
    {
        parabola_equation(parabola, direction, &parabola.h, &parabola.k, &parabola.fx, &parabola.fy, &parabola.axis_symmetry, &parabola.directrix, &parabola.latus_rectum);
        if (strcasecmp(direction, "Vertical") == 0)
        {
            if (parabola.h > 0 && parabola.k > 0) // Q1
            {
                printf("Standard Equation: (x - %.2f)^2 = %.2f (y - %.2f)^2\n", parabola.h, parabola.latus_rectum, parabola.k);
            }
            else if (parabola.h < 0 && parabola.k > 0) // Q2
            {
                printf("Standard Equation: (x + %.2f)^2 = %.2f (y - %.2f)^2\n", -parabola.h, parabola.latus_rectum, parabola.k);
            }
            else if (parabola.h < 0 && parabola.k < 0) // Q3
            {
                printf("Standard Equation: (x + %.2f)^2  = %.2f (y + %.2f)\n", -parabola.h, parabola.latus_rectum, -parabola.k);
            }
            else if (parabola.h > 0 && parabola.k < 0) //Q4
            {
                printf("Standard Equation: (x - %.2f)^2 = %.2f (y - %.2f)\n", parabola.h, parabola.latus_rectum, -parabola.k);
            }
            else if (parabola.h == 0 && parabola.k == 0) //Origin
            {
                printf("Standard Equation: x^2 = %.2fy\n", parabola.latus_rectum);
            }
            else if (parabola.h > 0 && parabola.k == 0) //+x - axis
            {
                printf("Standard Equation: (x - %.2f)^2 = %.2fy\n", parabola.h, parabola.latus_rectum);
            }
            else if (parabola.h < 0 && parabola.k == 0) //-x - axis
            {
                printf("Standard Equation: (x + %.2f)^2 = %.2fy\n", -parabola.h, parabola.latus_rectum);
            }
            else if (parabola.h == 0 && parabola.k > 0) //+y - axis
            {
                printf("Standard Equation: x^2 = %.2f (y - %.2f)\n", parabola.latus_rectum, parabola.k);
            }
            else if (parabola.h == 0 && parabola.k < 0) //-y - axis
            {
                printf("Standard Equation: x^2 = %.2f (y + %.2f)\n", parabola.latus_rectum, parabola.k);
            }
            printf("Vertex: (%.2f, %.2f)\n", parabola.h, parabola.k);
            printf("Focus: (%.2f, %.2f)\n", parabola.fx, parabola.fy);
            printf("Axis of Symmetry: x = %.2f\n", parabola.axis_symmetry);
            printf("Directrix: y = %.2f\n", parabola.directrix);
            printf("Latus Rectum [Focal Width]: %.2f units\n", fabs(parabola.latus_rectum));
            if (parabola.latus_rectum > 0)
            {
               printf("Direction: Upwards\n");
            }
            else if (parabola.latus_rectum < 0)
            {
                printf("Direction: Downwards\n");
            }
        }
    else if (strcasecmp(direction, "Horizontal") == 0)
        {
            if (parabola.h > 0 && parabola.k > 0)
            {
                printf("Standard Equation: (y - %.2f)^2 = %.2f (x - %.2f)\n", parabola.k, parabola.latus_rectum, parabola.h);
            }
            else if (parabola.h < 0 && parabola.k > 0)
            {
                printf("Standard Equation: (y - %.2f)^2 = %.2f (x + %.2f)\n", parabola.k, parabola.latus_rectum, -parabola.h);
            }
            else if (parabola.h < 0 && parabola.k < 0)
            {
                printf("Standard Equation: (y + %.2f)^2 = %.2f (x + %.2f)\n", -parabola.k, parabola.latus_rectum, -parabola.h);
            }
            else if (parabola.h > 0 && parabola.k < 0)
            {
                printf("Standard Equation: (y + %.2f)^2 = %.2f (x - %.2f)\n", -parabola.k, parabola.latus_rectum, parabola.h);
            }
            else if (parabola.h == 0 && parabola.k == 0)
            {
                printf("Standard Equation: y^2 = %.2fx\n", parabola.latus_rectum);
            }
            else if (parabola.h > 0 && parabola.k == 0)
            {
                printf("Standard Equation: y^2 = %.2f (x - %.2f)\n", parabola.latus_rectum, parabola.h);
            }
            else if (parabola.h < 0 && parabola.k == 0)
            {
                printf("Standard Equation: y^2 = %.2f (x + %.2f)\n", parabola.latus_rectum, -parabola.h);
            }
            else if (parabola.h == 0 && parabola.k > 0)
            {
                printf("Standard Equation: (y - %.2f)^2 = %.2fx\n", parabola.k, parabola.latus_rectum);
            }
            else if (parabola.h == 0 && parabola.k < 0)
            {
                printf("Standard Equation: (y + %.2f)^2 = %.2fx\n", -parabola.k, parabola.latus_rectum);
            }
            printf("Vertex: (%.2f, %.2f)\n", parabola.h, parabola.k);
            printf("Focus: (%.2f, %.2f)\n", parabola.fx, parabola.fy);
            printf("Axis of Symmetry: y = %.2f\n", parabola.axis_symmetry);
            printf("Directrix: x = %.2f\n", parabola.directrix);
            printf("Latus Rectum [Focal Width]: %.2f units\n", fabs(parabola.latus_rectum));
            if (parabola.latus_rectum > 0)
            {
                printf("Direction: Rightwards\n");
            }
            else if (parabola.latus_rectum < 0)
            {
                printf("Direction: Leftwards\n");
            }
        }
    }
    else if (choice == 2)
    {
        int counter = 0; //Counter for Array: Stop at methods[4]
        char *methods[] = {"Vertex + Focus", "Vertex + Directrix", "Focus + Directrix"};
        int user_method = 0; //User Input 
            do
            {
               printf("Method [%d]: %s\n", counter+1, methods[counter]);
               counter++;
            } while (counter <= 2);
            
            for (int i = 0; user_method <= 1 || user_method >= 3; i++)
            {
                printf("Enter Method [1 - 3]: ");
                scanf("%d", &user_method);
                getchar();

                if (user_method >= 1 && user_method <= 5)
                {
                    break;
                }
            }
        parabola_parameter(parabola, user_method, &parabola.h, &parabola.k, &parabola.latus_rectum, &parabola.direction);

        if (user_method == 1 || user_method == 2 || user_method == 3) 
        {
            if (parabola.direction == 1)
            {
                if (parabola.h > 0 && parabola.k > 0) // Q1
                {
                    printf("Standard Equation: (x - %.2f)^2 = %.2f (y - %.2f)\n", parabola.h, parabola.latus_rectum, parabola.k);
                }
                else if (parabola.h < 0 && parabola.k > 0) // Q2
                {
                    printf("Standard Equation: (x + %.2f)^2 = %.2f (y - %.2f)\n", -parabola.h, parabola.latus_rectum, parabola.k);
                }
                else if (parabola.h < 0 && parabola.k < 0) // Q3
                {
                    printf("Standard Equation: (x + %.2f)^2  = %.2f (y + %.2f)\n", -parabola.h, parabola.latus_rectum, -parabola.k);
                }
                else if (parabola.h > 0 && parabola.k < 0) //Q4
                {
                    printf("Standard Equation: (x - %.2f)^2 = %.2f (y - %.2f)\n", parabola.h, parabola.latus_rectum, -parabola.k);
                }
                else if (parabola.h == 0 && parabola.k == 0) //Origin
                {
                    printf("Standard Equation: x^2 = %.2fy\n", parabola.latus_rectum);
                }
                else if (parabola.h > 0 && parabola.k == 0) //+x - axis
                {
                    printf("Standard Equation: (x - %.2f)^2 = %.2fy\n", parabola.h, parabola.latus_rectum);
                }
                else if (parabola.h < 0 && parabola.k == 0) //-x - axis
                {
                    printf("Standard Equation: (x + %.2f)^2 = %.2fy\n", -parabola.h, parabola.latus_rectum);
                }
                else if (parabola.h == 0 && parabola.k > 0) //+y - axis
                {
                    printf("Standard Equation: x^2 = %.2f (y - %.2f)\n", parabola.latus_rectum, parabola.k);
                }
                else if (parabola.h == 0 && parabola.k < 0) //-y - axis
                {
                    printf("Standard Equation: x^2 = %.2f (y + %.2f)\n", parabola.latus_rectum, parabola.k);
                }
                
                float c = (parabola.latus_rectum)/4;
                printf("General Form: x^2 + %.2fx + %.2fy + %.2f = 0\n", -2*parabola.h, -4*c, pow(parabola.h, 2) + 4*c*parabola.k);
            }

            else if (parabola.direction == 2)
            {
                if (parabola.h > 0 && parabola.k > 0)
                {
                    printf("Standard Equation: (y - %.2f)^2 = %.2f (x - %.2f)\n", parabola.k, parabola.latus_rectum, parabola.h);
                }
                else if (parabola.h < 0 && parabola.k > 0)
                {
                    printf("Standard Equation: (y - %.2f)^2 = %.2f (x + %.2f)\n", parabola.k, parabola.latus_rectum, -parabola.h);
                }
                else if (parabola.h < 0 && parabola.k < 0)
                {
                    printf("Standard Equation: (y + %.2f)^2 = %.2f (x + %.2f)\n", -parabola.k, parabola.latus_rectum, -parabola.h);
                }   
                else if (parabola.h > 0 && parabola.k < 0)
                {
                    printf("Standard Equation: (y + %.2f)^2 = %.2f (x - %.2f)\n", -parabola.k, parabola.latus_rectum, parabola.h);
                }
                else if (parabola.h == 0 && parabola.k == 0)
                {
                    printf("Standard Equation: y^2 = %.2fx\n", parabola.latus_rectum);
                }
                else if (parabola.h > 0 && parabola.k == 0)
                {
                    printf("Standard Equation: y^2 = %.2f (x - %.2f)\n", parabola.latus_rectum, parabola.h);
                }
                else if (parabola.h < 0 && parabola.k == 0)
                {
                    printf("Standard Equation: y^2 = %.2f (x + %.2f)\n", parabola.latus_rectum, -parabola.h);
                }
                else if (parabola.h == 0 && parabola.k > 0)
                {
                    printf("Standard Equation: (y - %.2f)^2 = %.2fx\n", parabola.k, parabola.latus_rectum);
                }
                else if (parabola.h == 0 && parabola.k < 0)
                {
                    printf("Standard Equation: (y + %.2f)^2 = %.2fx\n", -parabola.k, parabola.latus_rectum);
                }

                float c = (parabola.latus_rectum) / 4;
                printf("General Form: y^2 + %.2fy + %.2fx + %.2f = 0\n", -2*parabola.k, -4*c, pow(parabola.k, 2) + 4*c*parabola.h);
            }
        } 
    }
}


int main()
{
    struct Parabola parabola;
    int choice; //User - Input Choice: [1] Equation [2] Data
    char direction [100]; //Direction of Parabola: Horizontal or Vertical 
    char user_method [100]; //Type of Method to solve for Parabola
    
    user_input:
    printf("Enter Data [1] Equation [2] Data: ");
    scanf("%d", &choice);
    
    if (choice == 1)
    {
        while (strcasecmp(direction, "Vertical") != 0 && strcasecmp(direction, "Horizontal") != 0)
        {
            printf("Enter Direction [Vertical: Has x^2 term] [Horizontal: Has y^2 term]: ");
            scanf("%s", direction);
            getchar();

            if (strcasecmp(direction, "Vertical") != 0 && strcasecmp(direction, "Horizontal") != 0)
            {
                printf("Invalid Direction!\n");
            }   
        }
    }
    else if (choice != 1 && choice != 2)
    {
        printf("Invalid Choice!\n");
        goto user_input;
    }
    

    display_output(parabola, direction, user_method, choice);
    return 0;
}