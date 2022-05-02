
// TODO: function prototypes of vector and matrix operations

int numRes; //num resources
int numProc; //num processes
int *resourceVector; //vector for total resources
int **demand; //demand matrix
int **alloc; //allocation matrix

void init(int numRes, int numProc);
void freeup();
void printVector(int *vector);
void printMatrix(int **matrix);
void addVectors(int *vec1, int *vec2);
void subractVectors(int *vec1, int *vec2);
int compareVectors(int *vec1, int *vec2);
int** clone(int **matrix);