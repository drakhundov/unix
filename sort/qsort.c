void quick_sort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int last;
  void swap_values_of_ptr_arr(void *v[], int i, int j);
  if (left >= right) return;
  swap_values_of_ptr_arr(v, left, (left + right) / 2);
  last = left;
  for (int i = left + 1; i <= right; ++i) {
    if (comp(v[i], v[left]) < 0) {
      swap_values_of_ptr_arr(v, i, ++last);
    }
  }
  swap_values_of_ptr_arr(v, left, last);
  quick_sort(v, left, last - 1, comp);
  quick_sort(v, last + 1, right, comp);
}
