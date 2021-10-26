#include <stdio.h>

//Global vars

int rows, cols;

//Functions

int main()
{
    printf("Enter # Rows: "); scanf("%i", &rows);
    printf("Enter # Cols: "); scanf("%i", &cols);

    float origMatrix[rows][cols], equivMatrix[rows][cols];
    void getMatrix( float matrix[rows][cols] );
    void copyMatrix( float matrix[rows][cols], float matrixCopy[rows][cols] );
    void swapRows( float matrixCopy[rows][cols] );
    void reduceMatrix( float matrixCopy[rows][cols] );
    void printMatrices( float matrix[rows][cols], float matrixCopy[rows][cols] );

    getMatrix( origMatrix );
    copyMatrix( origMatrix, equivMatrix );
    swapRows( equivMatrix );
    reduceMatrix( equivMatrix );
    printMatrices( origMatrix, equivMatrix );

    return 0;
}

void getMatrix( float matrix[rows][cols] )
{
    int i, j;
    printf("\nEnter first row (enter individual element and hit enter for each one): \n\n");
    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j )
            scanf("%f", &matrix[i][j]);
        printf("\nEnter next row (enter individual element and hit enter for each one):\n\n");
    }
}

void copyMatrix( float matrix[rows][cols], float matrixCopy[rows][cols] )
{
    int i, j;
    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j )
            matrixCopy[i][j] = matrix[i][j];
    }
}

void swapRows( float matrixCopy[rows][cols] )
{
    int m, i, j, n;
    float temp = 0;

    for( m = 0; m < rows; ++m ) {
        for( i = 0; i < rows-1; ++i ) {
            for( j = 0; j < cols; ++j ) {
                if( matrixCopy[i][j] != 0 )
                    break;
                else if( matrixCopy[i][j] == matrixCopy[i+1][j] )
                    continue;
                else {
                    for( n = 0; n < cols; ++n ) {
                        temp = matrixCopy[i][n];
                        matrixCopy[i][n] = matrixCopy[i+1][n];
                        matrixCopy[i+1][n] = temp;
                    }
                    break;
                }
            }
        }
    }
}

void reduceMatrix( float matrixCopy[rows][cols] )
{
    int i, iPrime, j;
    int leadingOneIndex = 0;
    float reductionFactor = 1.0;
    int getLeadingOne( int currentRow, float matrixCopy[rows][cols] );

    for( i = 0; i < rows; ++i ) {

        // Get index of leading non-zero while reducing current row to a leading one
        leadingOneIndex = getLeadingOne( i, matrixCopy );

        for( iPrime = 0; iPrime < rows; ++iPrime ) {
            if( iPrime == i )
                continue;
            else {
                reductionFactor = matrixCopy[iPrime][leadingOneIndex];
                for( j = 0; j < cols; ++j )
                    matrixCopy[iPrime][j] -= matrixCopy[i][j] * reductionFactor;
            }
        }
    }
}

int getLeadingOne( int currentRow, float matrixCopy[rows][cols] )
{
    int j, leadingIndex = 0;
    float reductionFactor = 1.0;

    for( j = 0; j < cols; ++j ) {
        if( matrixCopy[currentRow][j] == 0)
            continue;
        else {
            leadingIndex = j;
            reductionFactor = matrixCopy[currentRow][leadingIndex];
            break;
        }
    }
    for( j = 0; j < cols; ++j ) {
        matrixCopy[currentRow][j] /= reductionFactor;
    }

    return leadingIndex;
}

void printMatrices( float matrix[rows][cols], float matrixCopy[rows][cols] )
{
    int i, j;

    printf("\nOriginal matrix:\n\n");
    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j )
            printf("%8.2g", matrix[i][j]);
        printf("\n");
    }

    printf("\nReduced matrix:\n\n");
    for( i = 0; i < rows; ++i ) {
        for( j = 0; j < cols; ++j )
            printf("%8.2g", matrixCopy[i][j]);
        printf("\n");
    }
}
