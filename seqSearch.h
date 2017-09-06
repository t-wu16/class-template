#ifndef SEQ_SEARCH_H
#define SEQ_SEARCH_H
template<class T>
int seqSearch(const T list[], int n, const &key) {
	for (int i = 0;i < n;i++)
		if (list[i] == key)
			return i;
	return -1;
}
#endif
