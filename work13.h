struct pop_entry {
  int year;
  int population;
  char boro[15];
};

void print_entry(struct pop_entry * p);

int lineCounter();

void read_csv();

void read_data();

void add_data();

void update_data();
