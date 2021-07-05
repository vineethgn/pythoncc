/* SYMBOL TABLE RECORD*/

struct sym_tab_rec
{
	char *name;			/* name of symbol	*/
	struct sym_tab_rec *next;	/*link field		*/
};

typedef struct sym_tab_rec sym_tab_rec;

/* SYMBOL TABLE ENTRY */

sym_tab_rec *identifier;

/* SYMBOL TABLE IMPLEMENTATION */

sym_tab_rec *sym_table=(sym_tab_rec *)0;

sym_tab_rec * putsym(char *sym_name)
{
	sym_tab_rec *ptr;
	ptr = (sym_tab_rec *)malloc(sizeof(sym_tab_rec));
	ptr->name = (char *)malloc(strlen(sym_name +1));
	strcpy(ptr->name, sym_name);
	ptr->next=(struct sym_tab_rec*)sym_table;
	sym_table = ptr;
	return ptr;
}

sym_tab_rec * getsym(char *sym_name)
{
	sym_tab_rec *ptr;
	for(ptr=sym_table; ptr!=(sym_tab_rec *)0; ptr=(sym_tab_rec*)ptr->next)
	if(strcmp(ptr->name,sym_name)== 0)
	return ptr;
	return 0;
}

void display()
{
	sym_tab_rec *s_ptr;
	for(s_ptr=sym_table; s_ptr!=(sym_tab_rec *)0; s_ptr=(sym_tab_rec*)s_ptr->next)	
	printf("%s,", s_ptr->name);
}
	
	
