#define MAX_NAME_LENGTH 		32
#define NUM_SAMPLE_YEARS 		 5


// This structure will represent a co-worker
typedef struct person {
  unsigned int 		id;
  unsigned short 	age;
  float 					salary[NUM_SAMPLE_YEARS];
  char 						first[MAX_NAME_LENGTH];
  char                      middleInitial;
  char 						last[MAX_NAME_LENGTH];
} Person;


// Functions for populating a Person structure
void createSamplePerson(Person *p);
void print(Person *p);
char alreadyContains(Person people[], int numPeople, char *first, char*last);
void processEveryone(Person people[], int numPeople, void (*pFunc) (Person *p));
void increaseSalary(Person *p);
int compareSalaries(const void *param1, const void *param2);
