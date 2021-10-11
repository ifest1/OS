void merge(int *a, int begin, int mid, int end) {
    int l, r, i;
    int l1 = mid - begin + 1;
    int l2 = end - mid;
    int temp1[l1], temp2[l2];

    for(int p = 0; p < l1; p++) {
        temp1[p] = a[begin+p];
    }

    for(int p = 0; p < l2; p++) {
        temp2[p] = a[mid+1+p];
    }

    l = r = 0;
    i = begin;

    while(l < l1 && r < l2) {
        if (temp1[l] < temp2[r]) {
            a[i] = temp1[l];
            l++;
        }
        else {
            a[i] = temp2[r];
            r++;
        }
        i++;
    }

    while (l < l1) {
        a[i] = temp1[l];
        l++;
        i++;
    }

    while (r < l2) {
        a[i] = temp2[r];
        r++;
        i++;
    }
}

void ms(int *n, int begin, int end) {
    if (begin < end) {
        int mid = (begin + end) / 2;
        ms(n, begin, mid);
        ms(n, mid+1, end);
        merge(n, begin, mid, end);
    }
}