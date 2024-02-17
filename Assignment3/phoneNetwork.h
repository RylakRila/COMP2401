#define UNLIMITED         65535 // Designation for phone plans with unlimited calling
#define PAY_PER_MINUTE    0 // Designation for phone plans that require fixed payment per minute
#define PPM_MINUTES 100 // Number of minutes after which the price per minute is increased

#define BASE_PRICE 9.99 // Base cost for specific number plans
#define EXTRA_MINUTE_PRICE 0.15 // Cost for each extra minute over the allowed minutes

#define PPM_BASE 0.15 // Base cost of pay-per-minute plans per minutes, for the first 100 minutes
#define PPM_OVER 0.35 // Over cost for pay-per-minute plans per minutes, for minutes over 100

#define UNLIMITED_BASE_PRICE 34.99 // Base cost for unlimited plans

#define HST 0.13 // Harmonized Sales Tax rate

#define MAX_CUSTOMERS     100 // Maximum number of customers allowed in the system
#define MAX_CALLS	      1000 // Maximum number of monthly calls allowed in the system

// Structure representing a phone plan that a customer has
typedef struct {
	unsigned short int   minutesAllowed;  // # mins/month allowed in phone plan
	unsigned short int   minutesUsed;     // # mins used this month so far
} PlanType;


// Structure representing a customer
typedef struct {
	char           *name;        // name of customer
	unsigned int    id;          // customer ID
	char           *number;      // phone number of customer
	PlanType        plan;        // phone plan of customer
	unsigned short  numOutCalls; // number of calls made this month
	unsigned short  numInCalls;  // number of calls received this month
} CustomerType;


// Structure representing a phone call that was made
typedef struct {
	CustomerType  *madeFrom;   // customer who made the call
	CustomerType  *madeTo;     // customer who was called
	time_t         startTime;  // time that call was started
	time_t         endTime;    // time that call ended
} CallType;

typedef struct {
	CustomerType	customers[MAX_CUSTOMERS];  // data for customers registered with network
	unsigned int	numCustomers;              // number of customers registered
	CallType        calls[MAX_CALLS];       // data for all calls that took place this month
	unsigned int	numCalls;                  // number of calls that took place this month
} PhoneNetworkType;
