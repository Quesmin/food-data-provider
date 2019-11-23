#include <stdio.h>
#include <stdlib.h>

#define MAX_FOOD_TYPE_NAME 20
#define MAX_SPECIFIC_FOOD_NAME 20
#define MAX_LINE 40
#define MAX_DRINK_NAME 20

void getSpecificName(char *save);


int main() {

    int NoOfFoodTypes;
    printf("Please input number of food types:\n");
    scanf("%d", &NoOfFoodTypes);
    getchar();

    printf("Please input food types (each on a new line, may contain spaces):\n");
    char ** FoodTypes;
    FoodTypes = (char **) malloc(NoOfFoodTypes * sizeof(char *));
    for(int i=0; i<NoOfFoodTypes; i++)
    {
        FoodTypes[i] = (char *) malloc(MAX_FOOD_TYPE_NAME * sizeof(char));
        gets(FoodTypes[i]);
    }

    int *NoOfSpecificFood = (int *)malloc(NoOfFoodTypes * sizeof(int));
    char ***SpecificFood = (char ***)malloc(NoOfFoodTypes * sizeof(char**));
    double **PriceFood = (double **)malloc(NoOfFoodTypes * sizeof(double *));
    for(int i=0; i<NoOfFoodTypes; i++)
    {
        printf("Please input no of speciffic foods for food \"%s\":\n",FoodTypes[i]);
        scanf("%d", &NoOfSpecificFood[i]);
        getchar();

        SpecificFood[i] = (char **)malloc(NoOfSpecificFood[i] * sizeof(char *));
        PriceFood[i] = (double *)malloc(NoOfSpecificFood[i] * sizeof(double));

        printf("Please input \"%s\" speciffic foods &prices: each line in the format <speciffic food> (price):\n", FoodTypes[i]);
        for(int j=0; j<NoOfSpecificFood[i]; j++)
        {
            SpecificFood[i][j] = (char *)malloc(MAX_SPECIFIC_FOOD_NAME * sizeof(char));
            getSpecificName(SpecificFood[i][j]);
            char line[MAX_LINE];
            gets(line);
            sscanf(line, "%lf)", &PriceFood[i][j]);
        }
    }

    int NoOfDrinks;
    printf("Please input no of drinks:\n");
    scanf("%d", &NoOfDrinks);
    getchar();

    char **Drinks;
    double *PriceDrinks;
    Drinks = (char **)malloc(NoOfDrinks * sizeof(char *));
    PriceDrinks = (double *)malloc(NoOfDrinks * sizeof(double));
    printf("Please input the drinks: each line in the format <drink> (price):\n");
    for(int i=0; i<NoOfDrinks; i++)
    {
        Drinks[i] = (char *)malloc(MAX_DRINK_NAME * sizeof(char));
        getSpecificName(Drinks[i]);
        char line[MAX_LINE];
        gets(line);
        sscanf(line, "%lf)", &PriceDrinks[i]);
    }

    FILE *f;
    f = fopen("C:\\Users\\Cosmin\\Desktop\\CP\\food-ordering\\data.txt", "w");
    fprintf(f,"%d:\n", NoOfFoodTypes);
    for(int i=0; i<NoOfFoodTypes; i++)
    {
        fprintf(f,"%s: ", FoodTypes[i]);
        for(int j=0; j<NoOfSpecificFood[i]; j++) {
            fprintf(f, "(%s - %.2lf)", SpecificFood[i][j], PriceFood[i][j]);
            if (j == NoOfSpecificFood[i] - 1)
                fprintf(f, "\n");
            else
                fprintf(f, " ");
        }
    }
    fprintf(f,"%d:\n", NoOfDrinks);
    for(int i=0; i<NoOfDrinks; i++)
    {
        fprintf(f,"(%s - %.0lf)",Drinks[i],PriceDrinks[i]);
        if(i != NoOfDrinks - 1)
            fprintf(f,", ");
    }
    fclose(f);
    printf("The food data is:\n");
    for(int i=0; i<NoOfFoodTypes; i++)
    {
        printf("%s: ", FoodTypes[i]);
        for(int j=0; j<NoOfSpecificFood[i]; j++)
        {
            printf("(%s - %.2lf) ", SpecificFood[i][j], PriceFood[i][j]);
        }
        printf("\n");
    }

    printf("The drinks data is:\ndrinks: ");
    for(int i=0; i<NoOfDrinks; i++)
        if(i != NoOfDrinks - 1)
            printf("%s, ", Drinks[i]);
        else
            printf("%s\n", Drinks[i]);
    printf("prices: ");
    for(int i=0; i<NoOfDrinks; i++)
        if(i != NoOfDrinks - 1)
            printf("%.0lf, ", PriceDrinks[i]);
        else
            printf("%.0lf\n", PriceDrinks[i]);


    for(int i=0; i<NoOfFoodTypes; i++) {
        for (int j = 0; j < NoOfSpecificFood[i]; j++) {
            free(SpecificFood[i][j]);
        }
        free(SpecificFood[i]);
        free(FoodTypes[i]);
        free(PriceFood[i]);
    }
    free(SpecificFood);
    free(FoodTypes);
    free(PriceFood);
    free(NoOfSpecificFood);
    for(int i=0; i<NoOfDrinks; i++)
        free(Drinks[i]);
    free(Drinks);
    free(PriceDrinks);
    return 0;
}

void getSpecificName(char *save)
{
    int i=0;
    char c = getchar();
    while(c != '(')
    {
        save[i++] = c;
        c = getchar();
    }
   save[--i] = '\0';

}