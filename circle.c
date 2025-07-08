#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

struct Circle
{
    float A, C, D, E, F; //Coefficient of x^2 (A) y^2 (C) x (D) y (E) constant (F)
    float h, k, r; //x-coordinate of center, y-coordinate of center, radius
    float discriminant; //Discriminant
    float diameter, circumference, area; //Diameter, Circumference, Area
    float x1, y1; //Endpoint 1 or Any Point 1 on Circle 
    float x2, y2; //Endpoint 2 or Any Point 2 on Circle
    float sec_angle; //Sector angle
    
    //Combination 5: Radius + 2 Points + Subtended Sector Angle Variables
    float direc_vectorx, direc_vectory;
    float perpen_vectorx, perpen_vectory;
    float normalization;
    float degrees_radians;
    float distance, displacementx, displacementy;
    float midpointx, midpointy;
};

void circle_equation(struct Circle circle, float *h, float *k, float *r, float *diameter, float *circumference, float *area)
{
    circle.A = 0, circle.C = 0;
    while (circle.A != circle.C || circle.discriminant >= 0 || circle.A == 0 || circle.C == 0)
    {
        printf("Enter Coefficient of A, C, D, E, F [With Spaces]: ");
        scanf("%f %f %f %f %f", &circle.A, &circle.C, &circle.D, &circle.E, &circle.F);
        circle.discriminant = pow(0,2) - 4*circle.A*circle.C;

        if (circle.A != circle.C || circle.discriminant >= 0 || circle.A == 0 || circle.C == 0)
        {
            printf("Invalid Circle!\n");
        }
    }

    printf("General Equation: %.2fx^2 + %.2fy^2 + %.2fx + %.2fy + %.2f = 0\n", circle.A, circle.C, circle.D, circle.E, circle.F);
    
    circle.h = -circle.D/(2*circle.A);
    circle.k = -circle.E/(2*circle.C);
    circle.r = -circle.F + circle.A*pow(circle.D, 2)/4*pow(circle.A, 2) + circle.C*pow(circle.E,2)/4*pow(circle.C, 2);
    circle.diameter = 2*sqrt(circle.r);
    circle.circumference = 2*M_PI*sqrt(circle.r);
    circle.area = M_PI*pow(sqrt(circle.r), 2);

    *h = circle.h;
    *k = circle.k;
    *r = circle.r;
    *diameter = circle.diameter;
    *circumference = circle.circumference;
    *area = circle.area;

}

void circle_parameter(int *combination, struct Circle circle, float *h, float *k, float *r, float *A, float *C, float *D, float *E, float *F)
{

    switch (*combination)
    {
        case 1:
        printf("Enter Coordinates of Center [With Spaces]: ");
        scanf("%f %f", &circle.h, &circle.k);

        printf("Enter Radius: ");
        scanf("%f", &circle.r);

        *h = circle.h;
        *k = circle.k;
        *r = circle.r;
        break;

        case 2:
        printf("Enter Coordinates of Center [With Spaces]: ");
        scanf("%f %f", &circle.h, &circle.k);

        printf("Enter Diameter: ");
        scanf("%f", &circle.diameter);

        *r = circle.diameter/2.00;
        break;

        case 3:
        do
        {
            printf("Enter Radius: ");
            scanf("%f", &circle.r);

            printf("Enter Endpoints of Circle [x1, y1, x2, y2]: ");
            scanf("%f %f %f %f", &circle.x1, &circle.y1, &circle.x2, &circle.y2);

            if (circle.x1 != circle.x2 && circle.y1 != circle.y2 || circle.x1 == circle.x2 && circle.x2 == circle.y1 && circle.y1 == circle.y2)
            {
                printf("Invalid Endpoints!\n");
            }

        } while (circle.x1 != circle.x2 && circle.y1 != circle.y2);

          *r = pow(circle.r, 2);
        
        if (circle.x1 == circle.x2)
        {
            *h = circle.x1;
            *k = (circle.y1 + circle.y2) / 2;
        }
        else if (circle.y1 == circle.y2)
        {
            *h = (circle.x1 + circle.x2) / 2;
            *k = circle.y1;
        }
        break;

        case 4:
        while (circle.area <= 0 || circle.x1 != circle.x2 && circle.y1 != circle.y2 || circle.x1 == circle.x2 && circle.x2 == circle.y1 && circle.y1 == circle.y2)
        {
            printf("Enter Area: ");
            scanf("%f", &circle.area);

            if (circle.area <= 0)
            {
                printf("Invalid Area!\n");
            }
            else
            {
                printf("Enter Endpoints of Circle [x1, y1, x2, y2]: ");
                scanf("%f %f %f %f", &circle.x1, &circle.y1, &circle.x2, &circle.y2);

                if (circle.x1 != circle.x2 && circle.y1 != circle.y2 || circle.x1 == circle.x2 && circle.x2 == circle.y1 && circle.y1 == circle.y2)
                {
                    printf("Invalid Endpoints!\n");
                }
            }
        }
            *r = sqrt(circle.area / M_PI);

            if (circle.x1 == circle.x2)
            {
                *h = circle.x1;
                *k = (circle.y1 + circle.y2)/2;
            }
            else if (circle.y1 == circle.y2)
            {
                *h = (circle.x1 + circle.x2)/2;
                *k = circle.y1;
            }
            break;
        
        case 5:
        while (circle.x1 == circle.x2 && circle.x2 == circle.y1 && circle.y1 == circle.y2)
        {
            printf("Enter 2 Points on the Circle [x1, y1, x2, y2]: ");
            scanf("%f %f %f %f", &circle.x1, &circle.y1, &circle.x2, &circle.y2);
            if (circle.x1 == circle.x2 && circle.x2 == circle.y1 && circle.y1 == circle.y2)
            {
                printf("Invalid Points!\n");
            }
            else
            {
                while (circle.sec_angle <= 0)
                {
                    printf("Enter Subtended Sector Angle [Degrees]: ");
                    scanf("%f", &circle.sec_angle);

                    if (circle.sec_angle <= 0)
                    {
                        printf("Invalid Subtended Sector Angle!\n");
                    }
                    else
                    {
                        while (circle.r <= 0)
                        {
                            printf("Enter Radius: ");
                            scanf("%f", &circle.r);
                            if (circle.r <= 0)
                            {
                                printf("Invalid Radius!\n");
                            }
                        }
                    }
                }
            }
        }

        circle.direc_vectorx = circle.x2 - circle.x1;
        circle.direc_vectory = circle.y2 - circle.y1;
        circle.perpen_vectorx = circle.y1 - circle.y2;
        circle.degrees_radians = (circle.sec_angle * M_PI)/180;
        circle.distance = circle.r * cos(circle.degrees_radians/2); 

        circle.displacementx = (circle.distance*circle.perpen_vectorx) / sqrt(pow(circle.perpen_vectorx, 2) + pow(circle.direc_vectorx, 2));
        circle.displacementy = (circle.distance*circle.direc_vectorx) / sqrt(pow(circle.perpen_vectorx, 2) + pow(circle.direc_vectorx, 2));
        
        circle.midpointx = (circle.x1 + circle.x2)/2;
        circle.midpointy = (circle.y1 + circle.y2)/2;

        *h = circle.midpointx + circle.displacementx;
        *k = circle.midpointy + circle.displacementy;
        *r = circle.r;
        break;

    }


}

void display_output(struct Circle circle, int choice)
{
    if (choice == 1)
    {
        circle_equation (circle, &circle.h, &circle.k, &circle.r, &circle.diameter, &circle.circumference, &circle.area);
        printf("Center: (%.2f, %.2f)\n", circle.h, circle.k);
        printf("Radius: %.2f\n", sqrt(circle.r));
        printf("Diameter: %.2f\n", circle.diameter);
        printf("Circumference: %.2f\n", circle.circumference);
        printf("Area: %.2f\n", circle.area);
        if (circle.h == 0 && circle.k == 0) //Origin
        {
            printf("Standard Equation: x^2 + y^2 = %.2f\n", circle.r);
        }
        else if (circle.h > 0 && circle.k > 0) //Quadrant 1
        {
            printf("Standard Equation: (x - %.2f)^2 + (y - %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
        }
        else if (circle.h < 0 && circle.k > 0) //Quadrant 2
        {
            printf("Standard Equation: (x + %.2f)^2 + (y - %.2f)^2 = %.2f\n", -circle.h, circle.k, circle.r);
        }
        else if (circle.h < 0 && circle.k < 0) //Quadrant 3
        {
            printf("Standard Equation: (x + %.2f)^2 + (y + %.2f)^2 = %.2f\n", -circle.h, -circle.k, circle.r);
        }
        else if (circle.h > 0 && circle.k < 0) //Quadrant 4
        {
            printf("Standard Equation: (x - %.2f)^2 + (y + %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
        }
        else if (circle.h > 0 && circle.k == 0) //+x-axis
        {
            printf("Standard Equation: (x - %.2f)^2 + y^2 = %.2f\n", circle.h, circle.r);
        }
        else if (circle.h < 0 && circle.k == 0) //-x-axis
        {
            printf("Standard Equation: (x + %.2f)^2 + y^2 = %.2f\n", -circle.h, circle.r);
        }
        else if (circle.h == 0 && circle.k > 0) //+y-axis
        {
            printf("Standard Equation: x^2 + (y - %.2f)^2 = %.2f\n", circle.k, circle.r);
        }
        else if (circle.h == 0 && circle.k < 0) //-y-axis
        {
            printf("Standard Equation: x^2 + (y + %.2f)^2 = %.2f\n", -circle.k, circle.r);
        }
    }
    else if (choice == 2)
    {
        char modes[6][1000] = { "[1] Center + Radius", "[2] Center + Diameter", "[3] Radius + Endpoints on Circle", "[4] Area + Endpoints on Circle", "[5] Circumference + Point on Circle" };
        int combination; 
        
        printf("Combinations for Solution: \n");
        for (int i = 0; i <= 4; i++)
        {
            printf("%s\n", modes[i]);
        }
        
        for (int j = 0; combination < 1 || combination > 5; j++)
        {
            printf("Enter your Combination: ");
            scanf("%d", &combination);

            if (combination < 1 || combination > 5)
            {
                printf("Invalid Choice!\n");
            }
        }
        circle_parameter(&combination, circle, &circle.h, &circle.k, &circle.r, &circle.A, &circle.C, &circle.D, &circle.E, &circle.F);
        
        if (combination == 1)
        {
            circle.r = pow(circle.r, 2);
            if (circle.h == 0 && circle.k == 0) //Origin
            {
                printf("Standard Equation: x^2 + y^2 = %.2f\n", circle.r);
            }
            else if (circle.h > 0 && circle.k > 0) //Quadrant 1
            {
                printf("Standard Equation: (x - %.2f)^2 + (y - %.2f)^2 = %.2f\n", circle.h, circle.k, circle.r);
            }
            else if (circle.h < 0 && circle.k > 0) //Quadrant 2
            {
                printf("Standard Equation: (x + %.2f)^2 + (y - %.2f)^2 = %.2f\n", -circle.h, circle.k, circle.r);
            }
            else if (circle.h < 0 && circle.k < 0) // Quadrant 3
            {
                printf("Standard Equation: (x + %.2f)^2 + (y + %.2f)^2 = %.2f\n", -circle.h, -circle.k, circle.r);
            }
            else if (circle.h > 0 && circle.k < 0) //Quadrant 4
            {
                printf("Standard Equation: (x - %.2f)^2 + (y + %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
            }
            else if (circle.h > 0 && circle.k == 0) //+x-axis
            {
                printf("Standard Equation: (x - %.2f)^2 + y^2 = %.2f\n", circle.h, circle.r);
            }
        else if (circle.h < 0 && circle.k == 0) //-x-axis
            {
                printf("Standard Equation: (x + %.2f)^2 + y^2 = %.2f\n", -circle.h, circle.r);
            }
        else if (circle.h == 0 && circle.k > 0) //+y-axis
            {
                printf("Standard Equation: x^2 + (y - %.2f)^2 = %.2f\n", circle.k, circle.r);
            }
        else if (circle.h == 0 && circle.k < 0) //-y-axis
            {
                printf("Standard Equation: x^2 + (y + %.2f)^2 = %.2f\n", -circle.k, circle.r);
            }
        }
        
        if (combination == 2)
        {
            circle.r = pow(circle.r, 2);

            if (circle.h == 0 && circle.k == 0) //Origin
            {
                printf("Standard Equation: x^2 + y^2 = %.2f\n", circle.r);
            }
            
            else if (circle.h > 0 && circle.k == 0) //+x - axis
            {
                printf("Standard Equation: (x - %.2f)^2 + y^2 = %.2f\n", circle.h, circle.r);
            }

            else if (circle.h < 0 && circle.k == 0) //-x - axis
            {
                printf("Standard Equation: (x + %.2f)^2 + y^2 = %.2f\n", -circle.h, circle.r);
            }

            else if (circle.h == 0 && circle.k > 0) //+y - axis
            {
                printf("Standard Equation: x^2 + (y - %.2f)^2 = %.2f\n", circle.k, circle.r);
            }
            
            else if (circle.h == 0 && circle.k < 0) //-y - axis
            {
                printf("Standard Equation: x^2 + (y + %.2f)^2 = %.2f\n", -circle.k, circle.r);
            }
            
            else if (circle.h > 0 && circle.k > 0) //Quadrant 1
            {
                printf("Standard Equation: (x - %.2f)^2 + (y - %.2f)^2 = %.2f\n", circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k > 0) //Quadrant 2
            {
                printf("Standard Equation: (x + %.2f)^2 + (y - %.2f)^2 = %.2f\n", -circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k < 0) //Quadrant 3
            {
                printf("Standard Equation: (x + %.2f)^2 + (y + %.2f)^2 = %.2f\n", -circle.h, -circle.k, circle.r);
            }
            
            else if (circle.h > 0 && circle.k < 0) //Quadrant 4
            {
                printf("Standard Equation: (x - %.2f)^2 + (y + %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
            }
        }

        if (combination == 3)
        {
            if (circle.h == 0 && circle.k == 0) //Origin
            {
                printf("Standard Equation: x^2 + y^2 = %.2f\n", circle.r);
            }

            else if (circle.h > 0 && circle.k == 0) //+x - axis
            {
                printf("Standard Equation: (x - %.2f)^2 + y^2 = %.2f\n", circle.h, circle.r);
            }

            else if (circle.h < 0 && circle.k == 0) //-x - axis
            {
                printf("Standard Equation: (x + %.2f)^2 + y^2 = %.2f\n", -circle.h, circle.r);
            }

            else if (circle.h == 0 && circle.k > 0) //+y - axis
            {
                printf("Standard Equation: x^2 + (y - %.2f)^2 = %.2f\n", circle.k, circle.r);
            }
            
            else if (circle.h == 0 && circle.k < 0) //-y - axis
            {
                printf("Standard Equation: x^2 + (y + %.2f)^2 = %.2f\n", -circle.k, circle.r);
            }
            
            else if (circle.h > 0 && circle.k > 0) //Quadrant 1
            {
                printf("Standard Equation: (x - %.2f)^2 + (y - %.2f)^2 = %.2f\n", circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k > 0) //Quadrant 2
            {
                printf("Standard Equation: (x + %.2f)^2 + (y - %.2f)^2 = %.2f\n", -circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k < 0) //Quadrant 3
            {
                printf("Standard Equation: (x + %.2f)^2 + (y + %.2f)^2 = %.2f\n", -circle.h, -circle.k, circle.r);
            }
            
            else if (circle.h > 0 && circle.k < 0) //Quadrant 4
            {
                printf("Standard Equation: (x - %.2f)^2 + (y + %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
            }
        }

        if (combination == 4 || combination == 5)
        {
            circle.r = pow(circle.r, 2);
            
            if (circle.h == 0 && circle.k == 0) //Origin
            {
                printf("Standard Equation: x^2 + y^2 = %.2f\n", circle.r);
            }
            
            else if (circle.h > 0 && circle.k == 0) //+x - axis
            {
                printf("Standard Equation: (x - %.2f)^2 + y^2 = %.2f\n", circle.h, circle.r);
            }

            else if (circle.h < 0 && circle.k == 0) //-x - axis
            {
                printf("Standard Equation: (x + %.2f)^2 + y^2 = %.2f\n", -circle.h, circle.r);
            }

            else if (circle.h == 0 && circle.k > 0) //+y - axis
            {
                printf("Standard Equation: x^2 + (y - %.2f)^2 = %.2f\n", circle.k, circle.r);
            }
            
            else if (circle.h == 0 && circle.k < 0) //-y - axis
            {
                printf("Standard Equation: x^2 + (y + %.2f)^2 = %.2f\n", -circle.k, circle.r);
            }
            
            else if (circle.h > 0 && circle.k > 0) //Quadrant 1
            {
                printf("Standard Equation: (x - %.2f)^2 + (y - %.2f)^2 = %.2f\n", circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k > 0) //Quadrant 2
            {
                printf("Standard Equation: (x + %.2f)^2 + (y - %.2f)^2 = %.2f\n", -circle.h, circle.k, circle.r);
            }
            
            else if (circle.h < 0 && circle.k < 0) //Quadrant 3
            {
                printf("Standard Equation: (x + %.2f)^2 + (y + %.2f)^2 = %.2f\n", -circle.h, -circle.k, circle.r);
            } 
            
            else if (circle.h > 0 && circle.k < 0) //Quadrant 4
            {
                printf("Standard Equation: (x - %.2f)^2 + (y + %.2f)^2 = %.2f\n", circle.h, -circle.k, circle.r);
            }
        }

        circle.D = -2*circle.h;
        circle.E = -2*circle.k;
        circle.F = circle.r;
        
        if (circle.D != 0 && circle.E != 0)
        {
            printf("General Form: x^2 + y^2 + %.2fx + %.2fy + %.2f = 0\n", circle.D, circle.E, circle.F);
        }
        else
        {
            printf("General Form: x^2 + y^2 = %.2f\n", circle.r);
        }
    }
}

int main()
{
    int choice;
    struct Circle circle;
    
    for (int i = 0; choice < 1 || choice > 2; i++)
    {
       printf("Enter Circle Parameters: ");
       printf("[1] Equation [2] Data: ");
       scanf("%d", &choice);

       if (choice < 1 || choice > 2)
       {
         printf("Invalid Choice!\n");
       }
    }

    if (choice == 1)
    {
        display_output(circle, choice);
    }
    else if (choice == 2)
    {
        display_output(circle, choice);
    }
    
    return 0;
}