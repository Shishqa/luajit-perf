// fibonnacci number
double c_payload(double n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } 
    return c_payload(n - 1) + c_payload(n - 2);
}
