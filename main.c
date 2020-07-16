
//Listing 16.4 Using pointers to functions to control sort order; p. 393

//inputs a list of strings from the keyboard, sorts them in ascending or
// descending order, and then displays them on the screen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 25

int get_lines(char *lines[]);  //passing an array of pointers
void sort(char *p[], int n, int sort_type); //passing an array of pointers, int, sort type
void print_strings(char *p[], int n);   //passing an array of pointers, int
int alpha(char *p1, char *p2);      //passing two pointers
int reverse(char *p1, char *p2);    //passing two pointers

char *lines[MAXLINES];  //array of 25 pointers and global because outside of main()

int main(void)
{
    int number_of_lines, sort_type;

    //read in the lines from the keyboard ---
    //Call get_lines() passing in an array of pointers
    // ... REMEMBER: char *lines[MAXLINES] IS an array of pointers (look at
    // (get_lines prototype - it takes an array of pointers as an argument)...
    //Set return equal to number_of_lines
    number_of_lines = get_lines(lines);

    if(number_of_lines <0)
    {
        puts("\nMemory allocation error");
        exit(-1);
    }

    puts("Enter 0 for reverse order sort, 1 for alphabetical:");
    scanf("%d", &sort_type);

    sort(lines, number_of_lines, sort_type);
    print_strings(lines, number_of_lines);
    puts("\n\n");
    return 0;
}

int get_lines(char *lines[])
{
    int n = 0;
    char buffer[80];  //temporary input storage area

    puts("\nEnter one line at a time; enter a blank line when done.");

    //perform loop while < 25 lines input, and call to gets != 0, and 1st
    //  call isn't point to terminating null character (meaning no input)
    while(n<MAXLINES && gets(buffer)!=0 && buffer[0]!= '\0')
    {
        //see page 377,378,379 pink for more info...
        //    1.Call malloc() to allocate space for string just read... using length of buffer+1
        //       for allow for terminating null character on end of each string...
        //    2.(char *) is a typecase that specifies the type of the pointer to be returned by
        //     malloc() - in this case char...
        //    3.The part of the statement lines[n]=(char *)malloc(strlen(buffer+1) assigns
        //       the pointer returned from malloc() to lines[n]
        //    4.THEN, it checks to see if malloc() returned a NULL and if it did, the loop exits
        //       with a return value of -1
        //    NOTES: ALWAYS PAY ATTENTION TO PARENTHESIS BECAUSE THAT'S HOW THE ORDER
        //      OF EXECUTION FROM ABOVE WORKS HERE -- EVERYTHING ON "LEFT" IS DONE FIRST
        //      AND ***THEN*** IT'S CHECKED TO SEE IF IT'S NULL!!!!
        if((lines[n] = (char *)malloc(strlen(buffer)+1)) == NULL)
                return -1;

        strcpy(lines[n++],buffer);
    }
    return n;
} //** end of get_lines

void sort(char *p[], int n, int sort_type)
{
    int a,b;
    char *x;

    //the pointer to function
    int (*compare)(char *s1, char *s2);

    //initialize the pointer to point to the proper comparison function (that was entered by user)
    // on the argument sort_type...
    //
    //.. I think this is saying, set the pointer compare to the address of reverse()
    //   if sort_type=0 (true) or set it to alpha() if sort_type = 1 (false)
    //   --> see pg 85 for this type of assignment with '?'...
    //

    compare = (sort_type) ? reverse : alpha;
    printf("\nSort type = %d\n\n", sort_type);

    for(a=1; a<n; a++)  //why do I need a loop within a loop?
    {
        for(b=0; b<(n-1); b++)  //why is this n-1?
        {
            // calls function pointed to by compare (either reverse or alpha) with two
            // strings as input; does strcmp based on which function was called (reverse or alpha)
            // and returns a 0 or 1 (check strcmp command to be sure); if value returned is > 0,
            // then the 1st string is bigger than the 2nd... and the pointers pointing to the
            // strings that were input by the user are switched around (data stays where it is -
            // just pointers change)
            if(compare(p[b], p[b+1]) > 0)
            {
                x = p[b];
                p[b] = p[b+1];
                p[b+1] = x;
            }
        }
    }
} //**end of sort

void print_strings(char *p[], int n)
{
    int count;

    for(count=0; count<n; count++)
    {
        printf("%s\n", p[count]);
    }
}

int alpha(char *p1, char *p2)
{
    //notice order of p2,p1
    return(strcmp(p2,p1));
}
int reverse(char *p1, char *p2)
{
    //notice order of p1,p2
    return(strcmp(p1,p2));
}
