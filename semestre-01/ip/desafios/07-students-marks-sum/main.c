int marks_summation(int* marks, int number_of_students, char gender) {
  int start = (gender == 'b') ? 0 : 1;
    
  int gender_mark_sum = 0;
  for (int i = start; i < number_of_students; i += 2) {
    gender_mark_sum += marks[i];
  }
    
  return gender_mark_sum;
}
