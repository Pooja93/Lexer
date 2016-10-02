#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
char seps[] = " \t\n,;(){}[]#\"<>";
void keyw (char *p);
char ch, ch1,arv[100];
int i = 0, id = 0, kw = 0, num = 0, op = 0,  flag1 = 0, f = 0,len=0,u=0,fp=0,flaginfi=0,k=0,pz=0;
char keys[32][10] =
  { "auto", "break", "case", "char", "const", "continue", "default",
  "do", "double", "else", "enum", "extern", "float", "for", "goto",
  "if", "int", "long", "register", "return", "short", "signed",
  "sizeof", "static", "struct", "switch", "typedef", "union",
  "unsigned", "void", "volatile", "while"
};
int line = 0;
int
main ()
{
  char str[25], oper[] = "!%^&*-+=~|<>/?", arith[]= { "+-*/^" }, bit[] =
  {
  "&|"}, log[] = "&|";
  int j;
  char fname[50];
  FILE *f1;

printf("\nEnter file name");
scanf("%s",fname);
f1 = fopen (fname, "r");

  if (f1 == NULL)
    {
      printf ("file not found");
      exit (0);
    }
  while ((ch = fgetc (f1)) != EOF)
    {
      f=0;
      if (ch == '\n')
        {
          line++;
          printf ("\tIn line %d\n", line);
          continue;
        }
      for (j = 0; j <= 14; j++)
        {
          if (ch == oper[j])
            {
              for (i = 0; i < 5; i++)
                {
                  if (ch == arith[i])
                    {
                      printf ("\tArithmetic operator\t%c\n", ch);
                      flag1 = 1;
                    }
                }
              for (k = 0; k < 2; k++)
                {
                  if (ch == log[k])
                    {
                      ch1 = fgetc (f1);
                      if (ch1 == ch)
                        {
                          printf ("\tLogical operator\t%c%c\n", ch, ch);
                          flag1 = 1;f=0;
                        }
                      else
                         {
                           printf ("\tbitwise Operator\t%c\n", ch);
                          flag1 = 1;
                          ch = ch1;
                          keyw (&ch);f=0;
                        }
                    }
                }
                 if (ch == '=')
                {
                  printf ("\tAssignment operator\t%c\n", ch);
                  flag1 = 1;f=0;
                  }
              if (ch == '<' || ch == '>')
                {
                  flag1 = 1;
                  ch1 = fgetc (f1);
                    if (ch1 == ch)
                    printf ("\tBitwise operator\t%c%c\n", ch, ch);
                  else
                     {
                    printf ("\tRelational operator\t%c\n", ch);
                    keyw(&ch1);
	         }
                }
              if (!flag1)
                printf ("\tOperator\t%c\n", ch);
              op++;
              f = 1;
              str[i] = '\0';
              keyw (str);

            }
        }
      for (j = 0; j <= 14; j++)
        {
          if (i == -1)

     break;
          if (ch == seps[j])
            {
              if (ch == '#')
                {
                  f = 1;
                  printf ("\tHeader file\t");
                  while (ch != '>')
                    {

                      printf ("%c", ch);
                      ch = fgetc (f1);
                    }
                  printf ("%c\n", ch);
                  i = -1;
                 break;
                }
              if (ch == '"')

			    {
				printf ("\tArgument\t");
                  do
                   {
                      ch = fgetc (f1);
                      if(ch!='"')
			  {
			      printf ("%c", ch);
			 }
                    }
                  while (ch != '"');
                  printf("\n");

                  i = -1;
                  break;
                  f = 1;
                }
            str[i] = '\0';
            keyw (str);
			if (ch != ' ')
            printf ("\tSpecial character\t%c\n", ch);


            }
        }
      if (i != -1)
        {
          str[i] = ch;
          i++;
        }
      else
        i = 0;
      str[i] = '\0';
    }
     printf ("Keywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\nFloatinPoint: %d", kw,
          id, op, num,fp);
}
void keyw (char *p)
{
  int k, flag = 0;
  for (k = 0; k <= 31; k++)
    {
      if (strcmp (keys[k], p) == 0)
        {
          printf ("\tkeyword\t\%12s\n", p);
          kw++;
         flag = 1;
          f = 1;
          break;

        }
    }
  if (flag == 0)
    {
      if (isdigit (p[0]))
        {
            flaginfi=0;
            len=strlen(p);pz=0;

              for(u=0;u<len;u++)
               {
                    if(!isdigit(p[u])&&(p[u]!='.'))
                      {
	              	 pz=1;
                                         break;
                      }
                if(p[u]=='.')
                {
                   flaginfi=1;
		      break;
                 }
              }
         if(pz==1)
		 {
          f=1;
           printf("\tIdentifier\t%12s\n",p);
         }
      else
         {

         if(flaginfi==1)
         {
         printf("\tFloatingPoint\t%s\n",p);
         fp++;
		 f=1;
         }
         else
		 {
		 printf ("\tIntegerNumber\t%s\n", p);
          num++; }
          f = 1;
        }
       }


else if (p[0] != '\0') //if(p[0]!=13&&p[0]!=10)
        {
          printf ("\tIdentifier\t%12s\n", p);
          f = 1;
          id++;
        }
   }

    i = -1;

}
